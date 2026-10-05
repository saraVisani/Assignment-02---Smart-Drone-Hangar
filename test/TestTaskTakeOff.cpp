#include "./Util/test/TestInclude.h"
#include <unity.h>

static TakeOff* takeoff = nullptr;
static bool TTT = false; // Test Task Takeoff flag

void mySetUpTakeoff()
{
    if (!TTT) {
        std::cout << "Test Task Takeoff\n" << std::endl;
        TTT = true;
    }

    // Stato iniziale del sistema
    State::setSystemState(OK);
    State::setDroneState(IDLE);
    State::setDistanceFromHangar(0);

    // Reset del tempo
    resetMillis();

    // Inizializzazione hardware fake
    hw->initAllHardware();

    // Reset dei fake
    ledOnInstance.reset();
    sensorPirInstance.setDroneDetected(false);
    sensorDddInstance.setDistance(TAKEOFF_DISTANCE - 10);
    sensorDddInstance.resetSamples();
    sensorDddInstance.setMeasurementAvailable(true);

    if (takeoff != nullptr) {
        delete takeoff;
    }

    takeoff = new TakeOff();
    takeoff->init(10);

    advanceMillis(1);
}

void myTearDownTakeoff()
{
    std::cout << "End of test Task Takeoff\n" << std::endl;
}

void readValidDistanceTakeoff()
{
    for (int i = 0; i < 5; i++) {
        takeoff->tick();
    }
}

void openDoorCompletelyTakeoff()
{
    for (int i = 0;i < 100 && !servoMotor->isOpened();i++) {
        advanceMillis(20);
        takeoff->tick();
    }

    TEST_ASSERT_TRUE(servoMotor->isOpened());
}

void closeDoorCompletelyTakeoff()
{
    for (int i = 0;i < 100 && !servoMotor->isClosed();i++) {
        advanceMillis(20);

        takeoff->tick();
    }

    TEST_ASSERT_TRUE(servoMotor->isClosed());
}

void startTakeoff()
{
    State::setDroneState(TAKEOFF);
    takeoff->tick();
}

void startTakeoffAndOpenDoor()
{
    startTakeoff();
    openDoorCompletelyTakeoff();
}

void completeTakeoff()
{
    sensorDddInstance.setDistance(TAKEOFF_DISTANCE + 10);
    sensorDddInstance.resetSamples();

    /*Prima misura valida: parte il timer.*/
    readValidDistanceTakeoff();

    /*Passano i 5 secondi richiesti.*/
    advanceMillis(TAKEOFF_TIME);

    /*Nuova misura valida:il TakeOff deve completare.*/
    readValidDistanceTakeoff();
}


// ============================================================
// TEST
// ============================================================

// ============================================================
// 1. STATO INIZIALE
// ============================================================
void test_takeoff_initial_state_is_idle()
{
    mySetUpTakeoff();

    TEST_ASSERT_TRUE(State::matchDroneState(IDLE));
    TEST_ASSERT_TRUE(servoMotor->isClosed());

    myTearDownTakeoff();
}

// ============================================================
// 2. TAKEOFF PARTE SOLO NELLO STATO TAKEOFF
// ============================================================
void test_takeoff_does_not_start_from_idle()
{
    mySetUpTakeoff();

    State::setDroneState(IDLE);
    takeoff->tick();

    TEST_ASSERT_TRUE(servoMotor->isClosed());
    TEST_ASSERT_FALSE(servoMotor->isOpening());

    myTearDownTakeoff();
}

void test_takeoff_does_not_start_from_operating()
{
    mySetUpTakeoff();

    State::setDroneState(OPERATING);
    takeoff->tick();

    TEST_ASSERT_TRUE(servoMotor->isClosed());
    TEST_ASSERT_FALSE(servoMotor->isOpening());

    myTearDownTakeoff();
}

void test_takeoff_starts_when_state_is_takeoff()
{
    mySetUpTakeoff();
    startTakeoff();

    TEST_ASSERT_TRUE(servoMotor->isOpening());

    myTearDownTakeoff();
}

// ============================================================
// 3. APERTURA PORTA
// ============================================================
void test_takeoff_opens_door()
{
    mySetUpTakeoff();
    startTakeoff();

    TEST_ASSERT_TRUE(servoMotor->isOpening());
    TEST_ASSERT_FALSE(servoMotor->isClosed());

    myTearDownTakeoff();
}

void test_takeoff_servo_moves_2_degrees_after_20ms()
{
    mySetUpTakeoff();
    startTakeoff();
    advanceMillis(20);

    takeoff->tick();

    TEST_ASSERT_EQUAL(2,servoMotor->getAngle());

    myTearDownTakeoff();
}

void test_takeoff_servo_reaches_180_degrees()
{
    mySetUpTakeoff();
    startTakeoff();
    openDoorCompletelyTakeoff();

    TEST_ASSERT_EQUAL(180,servoMotor->getAngle());
    TEST_ASSERT_TRUE(servoMotor->isOpened());
    TEST_ASSERT_FALSE(servoMotor->isClosed());

    myTearDownTakeoff();
}

void test_takeoff_servo_does_not_exceed_180_degrees()
{
    mySetUpTakeoff();
    startTakeoff();

    for (int i = 0; i < 120; i++) {
        advanceMillis(20);
        takeoff->tick();
    }

    TEST_ASSERT_EQUAL(180,servoMotor->getAngle());
    TEST_ASSERT_TRUE(servoMotor->isOpened());

    myTearDownTakeoff();
}

// ============================================================
// 4. LCD TAKE OFF
// ============================================================
void test_takeoff_lcd_message()
{
    mySetUpTakeoff();
    startTakeoff();

    TEST_ASSERT_EQUAL_STRING("TAKE OFF",lcdDisplayInstance.getLine1().c_str());

    myTearDownTakeoff();
}

// ============================================================
// 5. DISTANZA SOTTO SOGLIA
// ============================================================
void test_takeoff_distance_below_threshold()
{
    mySetUpTakeoff();
    startTakeoffAndOpenDoor();

    sensorDddInstance.setDistance(TAKEOFF_DISTANCE - 1);
    sensorDddInstance.resetSamples();

    readValidDistanceTakeoff();
    advanceMillis(TAKEOFF_TIME);
    readValidDistanceTakeoff();

    TEST_ASSERT_TRUE(State::matchDroneState(TAKEOFF));

    myTearDownTakeoff();
}

// ============================================================
// 6. DISTANZA ESATTAMENTE ALLA SOGLIA
// ============================================================
void test_takeoff_distance_equal_threshold()
{
    mySetUpTakeoff();
    startTakeoffAndOpenDoor();

    sensorDddInstance.setDistance(TAKEOFF_DISTANCE);
    sensorDddInstance.resetSamples();

    readValidDistanceTakeoff();
    advanceMillis(TAKEOFF_TIME);
    readValidDistanceTakeoff();

    TEST_ASSERT_TRUE(State::matchDroneState(TAKEOFF));

    myTearDownTakeoff();
}

// ============================================================
// 7. DISTANZA SOPRA SOGLIA
// ============================================================
void test_takeoff_distance_above_threshold()
{
    mySetUpTakeoff();
    startTakeoffAndOpenDoor();

    sensorDddInstance.setDistance(TAKEOFF_DISTANCE + 1);
    sensorDddInstance.resetSamples();

    readValidDistanceTakeoff();

    /* Il timer è appena partito. Non deve ancora essere OPERATING.*/
    TEST_ASSERT_TRUE(State::matchDroneState(TAKEOFF));

    myTearDownTakeoff();
}

// ============================================================
// 8. TIMER - PRIMA DEL TEMPO
// ============================================================
void test_takeoff_not_complete_before_time()
{
    mySetUpTakeoff();
    startTakeoffAndOpenDoor();

    sensorDddInstance.setDistance(TAKEOFF_DISTANCE + 10);
    sensorDddInstance.resetSamples();

    readValidDistanceTakeoff();

    /*Un millisecondo prima del limite*/
    advanceMillis(TAKEOFF_TIME - 1);
    readValidDistanceTakeoff();

    TEST_ASSERT_TRUE(State::matchDroneState(TAKEOFF));

    myTearDownTakeoff();
}

// ============================================================
// 9. TIMER - ESATTAMENTE 5 SECONDI
// ============================================================
void test_takeoff_complete_at_required_time()
{
    mySetUpTakeoff();
    startTakeoffAndOpenDoor();

    sensorDddInstance.setDistance(TAKEOFF_DISTANCE + 10);
    sensorDddInstance.resetSamples();

    readValidDistanceTakeoff();

    /* Passano esattamente 5 secondi.*/
    advanceMillis(TAKEOFF_TIME);
    readValidDistanceTakeoff();

    TEST_ASSERT_TRUE(State::matchDroneState(OPERATING));

    myTearDownTakeoff();
}

// ============================================================
// 10. TIMER - OLTRE IL TEMPO
// ============================================================
void test_takeoff_complete_after_required_time()
{
    mySetUpTakeoff();
    startTakeoffAndOpenDoor();

    sensorDddInstance.setDistance(TAKEOFF_DISTANCE + 10);
    sensorDddInstance.resetSamples();

    readValidDistanceTakeoff();
    advanceMillis( TAKEOFF_TIME + 1000);
    readValidDistanceTakeoff();

    TEST_ASSERT_TRUE(State::matchDroneState(OPERATING));

    myTearDownTakeoff();
}

// ============================================================
// 11. RESET TIMER
// ============================================================
void test_takeoff_timer_resets_if_drone_comes_back()
{
    mySetUpTakeoff();
    startTakeoffAndOpenDoor();

    sensorDddInstance.setDistance(TAKEOFF_DISTANCE + 10);
    sensorDddInstance.resetSamples();

    readValidDistanceTakeoff();
    advanceMillis(2000);

    /*Drone torna dentro.*/
    sensorDddInstance.setDistance(TAKEOFF_DISTANCE - 10);
    sensorDddInstance.resetSamples();

    readValidDistanceTakeoff();

    /* Il timer deve essere stato azzerato.*/
    advanceMillis(3000);

    /*Il drone torna fuori.Riparte un NUOVO timer.*/
    sensorDddInstance.setDistance(TAKEOFF_DISTANCE + 10);
    sensorDddInstance.resetSamples();

    readValidDistanceTakeoff();

    TEST_ASSERT_TRUE(State::matchDroneState(TAKEOFF));

    myTearDownTakeoff();
}

// ============================================================
// 12. TIMER RIPARTE DOPO IL RESET
// ============================================================
void test_takeoff_timer_restarts_after_reset()
{
    mySetUpTakeoff();
    startTakeoffAndOpenDoor();

    sensorDddInstance.setDistance(TAKEOFF_DISTANCE + 10);
    sensorDddInstance.resetSamples();

    readValidDistanceTakeoff();
    advanceMillis(2000);

    sensorDddInstance.setDistance(TAKEOFF_DISTANCE - 10);
    sensorDddInstance.resetSamples();

    readValidDistanceTakeoff();

    sensorDddInstance.setDistance(TAKEOFF_DISTANCE + 10);
    sensorDddInstance.resetSamples();

    readValidDistanceTakeoff();
    advanceMillis( TAKEOFF_TIME - 1);
    readValidDistanceTakeoff();

    TEST_ASSERT_TRUE(State::matchDroneState(TAKEOFF));

    myTearDownTakeoff();
}

// ============================================================
// 13. COMPLETAMENTO DOPO RESET
// ============================================================
void test_takeoff_completes_after_full_second_interval()
{
    mySetUpTakeoff();
    startTakeoffAndOpenDoor();

    sensorDddInstance.setDistance(TAKEOFF_DISTANCE + 10);
    sensorDddInstance.resetSamples();

    readValidDistanceTakeoff();
    advanceMillis(2000);

    sensorDddInstance.setDistance(TAKEOFF_DISTANCE - 10);
    sensorDddInstance.resetSamples();

    readValidDistanceTakeoff();

    sensorDddInstance.setDistance( TAKEOFF_DISTANCE + 10);
    sensorDddInstance.resetSamples();

    readValidDistanceTakeoff();
    advanceMillis(TAKEOFF_TIME);
    readValidDistanceTakeoff();

    TEST_ASSERT_TRUE(State::matchDroneState(OPERATING));

    myTearDownTakeoff();
}

// ============================================================
// 14. DISTANZA SALVATA NELLO STATE
// ============================================================
void test_takeoff_updates_distance_state()
{
    mySetUpTakeoff();
    startTakeoffAndOpenDoor();

    const float testDistance =TAKEOFF_DISTANCE + 15;

    sensorDddInstance.setDistance(testDistance);
    sensorDddInstance.resetSamples();

    readValidDistanceTakeoff();

    TEST_ASSERT_EQUAL_FLOAT(testDistance,State::getDistanceFromHangar());

    myTearDownTakeoff();
}

// ============================================================
// 15. DDD NON DISPONIBILE
// ============================================================
void test_takeoff_ignores_unavailable_distance()
{
    mySetUpTakeoff();
    startTakeoffAndOpenDoor();

    sensorDddInstance.setDistance(TAKEOFF_DISTANCE + 10);
    sensorDddInstance.resetSamples();
    sensorDddInstance.setMeasurementAvailable(false);

    advanceMillis(TAKEOFF_TIME + 2000);

    for (int i = 0; i < 10; i++) {
        takeoff->tick();
    }

    /*Senza una misura valida il timer non deve partire.*/
    TEST_ASSERT_TRUE( State::matchDroneState(TAKEOFF));

    myTearDownTakeoff();
}

// ============================================================
// 16. DDD TORNA DISPONIBILE
// ============================================================
void test_takeoff_resumes_after_ddd_becomes_available()
{
    mySetUpTakeoff();
    startTakeoffAndOpenDoor();

    sensorDddInstance.setDistance(TAKEOFF_DISTANCE + 10);
    sensorDddInstance.setMeasurementAvailable(false);

    advanceMillis(2000);

    for (int i = 0; i < 5; i++) {
        takeoff->tick();
    }

    TEST_ASSERT_TRUE(State::matchDroneState(TAKEOFF));

    sensorDddInstance.setMeasurementAvailable(true);
    sensorDddInstance.resetSamples();

    readValidDistanceTakeoff();
    advanceMillis(TAKEOFF_TIME);
    readValidDistanceTakeoff();

    TEST_ASSERT_TRUE(State::matchDroneState(OPERATING));

    myTearDownTakeoff();
}

// ============================================================
// 17. PRIME 4 LETTURE DDD
// ============================================================
void test_takeoff_first_four_ddd_reads_are_not_valid()
{
    mySetUpTakeoff();
    startTakeoffAndOpenDoor();

    sensorDddInstance.setDistance(TAKEOFF_DISTANCE + 10);
    sensorDddInstance.resetSamples();

    for (int i = 0; i < 4; i++) {
        takeoff->tick();
    }

    advanceMillis(TAKEOFF_TIME);

    TEST_ASSERT_TRUE(State::matchDroneState(TAKEOFF));

    myTearDownTakeoff();
}

// ============================================================
// 18. QUINTA LETTURA DDD
// ============================================================
void test_takeoff_fifth_ddd_read_is_valid()
{
    mySetUpTakeoff();
    startTakeoffAndOpenDoor();

    sensorDddInstance.setDistance(TAKEOFF_DISTANCE + 10);
    sensorDddInstance.resetSamples();

    readValidDistanceTakeoff();

    TEST_ASSERT_TRUE(State::matchDroneState(TAKEOFF));

    myTearDownTakeoff();
}

// ============================================================
// 19. PIR NON INFLUENZA IL TAKEOFF
// ============================================================
void test_takeoff_works_with_pir_low()
{
    mySetUpTakeoff();

    sensorPirInstance.setDroneDetected(false);

    startTakeoffAndOpenDoor();

    sensorDddInstance.setDistance(TAKEOFF_DISTANCE + 10);
    sensorDddInstance.resetSamples();

    readValidDistanceTakeoff();
    advanceMillis(TAKEOFF_TIME);
    readValidDistanceTakeoff();

    TEST_ASSERT_TRUE(State::matchDroneState(OPERATING));

    myTearDownTakeoff();
}

void test_takeoff_works_with_pir_high()
{
    mySetUpTakeoff();

    sensorPirInstance.setDroneDetected(true);

    startTakeoffAndOpenDoor();

    sensorDddInstance.setDistance(TAKEOFF_DISTANCE + 10);
    sensorDddInstance.resetSamples();

    readValidDistanceTakeoff();
    advanceMillis(TAKEOFF_TIME);
    readValidDistanceTakeoff();

    TEST_ASSERT_TRUE(State::matchDroneState(OPERATING));

    myTearDownTakeoff();
}

// ============================================================
// 20. COMPLETAMENTO - LED
// ============================================================
void test_takeoff_completion_turns_off_led()
{
    mySetUpTakeoff();

    ledOnInstance.turnOn();

    TEST_ASSERT_TRUE(ledOnInstance.isOn());

    startTakeoffAndOpenDoor();
    completeTakeoff();

    TEST_ASSERT_FALSE(ledOnInstance.isOn());

    myTearDownTakeoff();
}

// ============================================================
// 21. COMPLETAMENTO - LCD
// ============================================================
void test_takeoff_completion_prints_drone_out()
{
    mySetUpTakeoff();
    startTakeoffAndOpenDoor();
    completeTakeoff();

    TEST_ASSERT_EQUAL_STRING("DRONE OUT",lcdDisplayInstance.getLine1().c_str());

    myTearDownTakeoff();
}

// ============================================================
// 22. COMPLETAMENTO - STATO
// ============================================================
void test_takeoff_completion_sets_operating()
{
    mySetUpTakeoff();
    startTakeoffAndOpenDoor();
    completeTakeoff();

    TEST_ASSERT_TRUE(State::matchDroneState(OPERATING));
    TEST_ASSERT_FALSE(State::matchDroneState(TAKEOFF));

    myTearDownTakeoff();
}

// ============================================================
// 23. COMPLETAMENTO - PORTA INIZIA A CHIUDERSI
// ============================================================
void test_takeoff_completion_starts_closing_door()
{
    mySetUpTakeoff();
    startTakeoffAndOpenDoor();
    completeTakeoff();

    TEST_ASSERT_TRUE(servoMotor->isClosing());

    myTearDownTakeoff();
}

// ============================================================
// 24. COMPLETAMENTO - PORTA COMPLETAMENTE CHIUSA
// ============================================================
void test_takeoff_completion_closes_door()
{
    mySetUpTakeoff();
    startTakeoffAndOpenDoor();
    completeTakeoff();
    closeDoorCompletelyTakeoff();

    TEST_ASSERT_TRUE(servoMotor->isClosed());
    TEST_ASSERT_EQUAL(0,servoMotor->getAngle());

    myTearDownTakeoff();
}

// ============================================================
// 25. NON COMPLETA DUE VOLTE
// ============================================================
void test_takeoff_does_not_complete_twice()
{
    mySetUpTakeoff();
    startTakeoffAndOpenDoor();
    completeTakeoff();

    TEST_ASSERT_TRUE(State::matchDroneState(OPERATING));

    for (int i = 0; i < 20; i++) {
        advanceMillis(100);
        takeoff->tick();
    }

    TEST_ASSERT_TRUE( State::matchDroneState(OPERATING));

    myTearDownTakeoff();
}

// ============================================================
// 26. NUOVO TAKEOFF
// ============================================================
void test_takeoff_can_start_again()
{
    mySetUpTakeoff();
    startTakeoffAndOpenDoor();
    completeTakeoff();
    closeDoorCompletelyTakeoff();

    TEST_ASSERT_TRUE(servoMotor->isClosed());
    TEST_ASSERT_TRUE(State::matchDroneState(OPERATING));

    State::setDroneState(TAKEOFF);
    takeoff->tick();

    TEST_ASSERT_TRUE(servoMotor->isOpening());

    myTearDownTakeoff();
}

// ============================================================
// 27. NUOVO TAKEOFF - TIMER RESETTATO
// ============================================================
void test_takeoff_new_cycle_requires_new_time()
{
    mySetUpTakeoff();
    startTakeoffAndOpenDoor();
    completeTakeoff();
    closeDoorCompletelyTakeoff();
    State::setDroneState(TAKEOFF);

    sensorDddInstance.resetSamples();
    sensorDddInstance.setDistance( TAKEOFF_DISTANCE + 10);

    takeoff->tick();

    readValidDistanceTakeoff();

    TEST_ASSERT_TRUE(State::matchDroneState(TAKEOFF));

    myTearDownTakeoff();
}

// ============================================================
// 28. DISTANZA MOLTO BASSA
// ============================================================
void test_takeoff_zero_distance_does_not_complete()
{
    mySetUpTakeoff();
    startTakeoffAndOpenDoor();

    sensorDddInstance.setDistance(0);
    sensorDddInstance.resetSamples();

    for (int i = 0; i < 10; i++) {
        readValidDistanceTakeoff();
        advanceMillis(1000);
    }

    TEST_ASSERT_TRUE(State::matchDroneState(TAKEOFF));

    myTearDownTakeoff();
}

// ============================================================
// 29. DISTANZA MOLTO ALTA
// ============================================================
void test_takeoff_large_distance_completes()
{
    mySetUpTakeoff();
    startTakeoffAndOpenDoor();

    sensorDddInstance.setDistance(1000);
    sensorDddInstance.resetSamples();

    readValidDistanceTakeoff();
    advanceMillis(TAKEOFF_TIME);
    readValidDistanceTakeoff();

    TEST_ASSERT_TRUE(State::matchDroneState(OPERATING));

    myTearDownTakeoff();
}

// ============================================================
// 30. OSCILLAZIONE INTORNO ALLA SOGLIA
// ============================================================
void test_takeoff_distance_oscillation_resets_timer()
{
    mySetUpTakeoff();
    startTakeoffAndOpenDoor();

    sensorDddInstance.setDistance(TAKEOFF_DISTANCE + 1);
    sensorDddInstance.resetSamples();

    readValidDistanceTakeoff();
    advanceMillis(2000);

    sensorDddInstance.setDistance(TAKEOFF_DISTANCE - 1);
    sensorDddInstance.resetSamples();

    readValidDistanceTakeoff();

    sensorDddInstance.setDistance(TAKEOFF_DISTANCE + 1);
    sensorDddInstance.resetSamples();

    readValidDistanceTakeoff();
    advanceMillis(2000);
    readValidDistanceTakeoff();

    TEST_ASSERT_TRUE(State::matchDroneState(TAKEOFF));

    myTearDownTakeoff();
}



/*void loop()
{
}*/