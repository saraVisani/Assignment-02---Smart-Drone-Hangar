#include "./Util/Test/TestInclude.h"
#include <unity.h>

// ============================================================
// Test Task Landing
// ============================================================

static Landing* land = nullptr;
static bool TTL = false; // Test Task Landing flag


// ============================================================
// SETUP / TEARDOWN
// ============================================================

void mySetUpLanding()
{
    if (!TTL) {
        std::cout << "Test Task Landing\n" << std::endl;
        TTL = true;
    }

    // Stato iniziale del sistema
    State::setSystemState(OK);
    State::setDroneState(OPERATING);
    State::setDistanceToGround(0);

    // Reset del tempo
    resetMillis();

    // Inizializzazione hardware fake
    hw->initAllHardware();

    // Reset dei fake
    ledOnInstance.reset();

    sensorPirInstance.setDroneDetected(false);

    sensorDddInstance.setDistance(LANDING_DISTANCE + 20);
    sensorDddInstance.resetSamples();

    // Se hai aggiunto questa funzione al FakeSddd
    // per simulare letture non disponibili
    sensorDddInstance.setMeasurementAvailable(true);

    // Nuova istanza del task Landing per ogni test
    if (land != nullptr) {
        delete land;
    }

    land = new Landing();
    land->init(10);

    /*
     * Importante:
     * Landing usa 0 come valore speciale per droneLandStartTime.
     * Evitiamo quindi di iniziare i test esattamente a millis() == 0.
     */
    advanceMillis(1);
}


void myTearDownLanding()
{
    std::cout << "End of test Task Landing\n" << std::endl;
}


// ============================================================
// HELPER
// ============================================================

/*
 * Simula il rilevamento del drone tramite PIR
 * e avvia il processo di landing.
 */
void startLanding()
{
    sensorPirInstance.setDroneDetected(true);

    land->tick();

    TEST_ASSERT_TRUE(servoMotor->isOpening());
    TEST_ASSERT_EQUAL_STRING(
        "LANDING",
        lcdDisplayInstance.getLine1().c_str()
    );
}


/*
 * Il FakeDDD restituisce una misura valida ogni 5 letture.
 *
 * Questa funzione esegue quindi 5 tick.
 */
void readValidDistance()
{
    for (int i = 0; i < 5; i++) {
        land->tick();
    }
}


/*
 * Porta il servo fino a 180°.
 */
void openDoorCompletely()
{
    for (int i = 0;
         i < 100 && !servoMotor->isOpened();
         i++)
    {
        advanceMillis(20);
        land->tick();
    }

    TEST_ASSERT_TRUE(servoMotor->isOpened());
}


/*
 * Porta il servo fino a 0°.
 *
 * Dopo il completamento del landing il PIR viene normalmente
 * disattivato, altrimenti Landing potrebbe immediatamente
 * iniziare una nuova apertura.
 */
void closeDoorCompletely()
{
    sensorPirInstance.setDroneDetected(false);

    for (int i = 0;
         i < 100 && !servoMotor->isClosed();
         i++)
    {
        advanceMillis(20);
        land->tick();
    }

    TEST_ASSERT_TRUE(servoMotor->isClosed());
}


// ============================================================
// TEST 1
// PIR LOW -> nessun landing
// ============================================================

void test_landing_no_drone_detected()
{
    mySetUpLanding();

    sensorPirInstance.setDroneDetected(false);

    land->tick();

    TEST_ASSERT_TRUE(servoMotor->isClosed());
    TEST_ASSERT_FALSE(servoMotor->isOpening());
    TEST_ASSERT_FALSE(ledOnInstance.isOn());

    TEST_ASSERT_FALSE(
        lcdDisplayInstance.getLine1() == "LANDING"
    );

    myTearDownLanding();
}


// ============================================================
// TEST 2
// PIR HIGH -> inizia il landing
// ============================================================

void test_landing_drone_detected()
{
    mySetUpLanding();

    startLanding();

    TEST_ASSERT_TRUE(servoMotor->isOpening());

    myTearDownLanding();
}


// ============================================================
// TEST 3
// PIR HIGH -> LCD LANDING
// ============================================================

void test_landing_lcd_message()
{
    mySetUpLanding();

    startLanding();

    TEST_ASSERT_EQUAL_STRING(
        "LANDING",
        lcdDisplayInstance.getLine1().c_str()
    );

    myTearDownLanding();
}


// ============================================================
// TEST 4
// La porta comincia effettivamente ad aprirsi
// ============================================================

void test_landing_servo_opens()
{
    mySetUpLanding();

    startLanding();

    // Primo aggiornamento dopo il tempo necessario
    advanceMillis(20);
    land->tick();

    TEST_ASSERT_EQUAL(2, servoMotor->getAngle());
    TEST_ASSERT_TRUE(servoMotor->isOpening());
    TEST_ASSERT_FALSE(servoMotor->isClosed());

    myTearDownLanding();
}


// ============================================================
// TEST 5
// La porta arriva completamente aperta
// ============================================================

void test_landing_servo_opens_completely()
{
    mySetUpLanding();

    startLanding();

    openDoorCompletely();

    TEST_ASSERT_EQUAL(180, servoMotor->getAngle());
    TEST_ASSERT_TRUE(servoMotor->isOpened());
    TEST_ASSERT_FALSE(servoMotor->isClosed());

    myTearDownLanding();
}


// ============================================================
// TEST 6
// Distanza sopra la soglia -> non atterra
// ============================================================

void test_landing_distance_above_threshold()
{
    mySetUpLanding();

    startLanding();

    sensorDddInstance.setDistance(LANDING_DISTANCE + 1);
    sensorDddInstance.resetSamples();

    readValidDistance();

    advanceMillis(LANDING_TIME);
    readValidDistance();

    TEST_ASSERT_TRUE(
        State::matchDroneState(OPERATING)
    );

    TEST_ASSERT_FALSE(ledOnInstance.isOn());

    myTearDownLanding();
}


// ============================================================
// TEST 7
// Distanza uguale alla soglia -> non atterra
//
// Il codice usa:
//     distance < LANDING_DISTANCE
//
// quindi 50 NON è sufficiente se LANDING_DISTANCE = 50.
// ============================================================

void test_landing_distance_equal_threshold()
{
    mySetUpLanding();

    startLanding();

    sensorDddInstance.setDistance(LANDING_DISTANCE);
    sensorDddInstance.resetSamples();

    readValidDistance();

    advanceMillis(LANDING_TIME);
    readValidDistance();

    TEST_ASSERT_TRUE(
        State::matchDroneState(OPERATING)
    );

    TEST_ASSERT_FALSE(ledOnInstance.isOn());

    myTearDownLanding();
}


// ============================================================
// TEST 8
// Distanza sotto la soglia -> inizia il timer
// ============================================================

void test_landing_distance_below_threshold()
{
    mySetUpLanding();

    startLanding();

    sensorDddInstance.setDistance(LANDING_DISTANCE - 1);
    sensorDddInstance.resetSamples();

    readValidDistance();

    /*
     * Non sono ancora trascorsi 5 secondi.
     * Il landing quindi non deve essere completato.
     */
    TEST_ASSERT_TRUE(
        State::matchDroneState(OPERATING)
    );

    TEST_ASSERT_FALSE(ledOnInstance.isOn());

    myTearDownLanding();
}


// ============================================================
// TEST 9
// Drone sotto soglia per meno di LANDING_TIME
// ============================================================

void test_landing_not_complete_before_time()
{
    mySetUpLanding();

    startLanding();

    sensorDddInstance.setDistance(LANDING_DISTANCE - 10);
    sensorDddInstance.resetSamples();

    // Prima misura valida -> parte il timer
    readValidDistance();

    // Trascorrono 4999 ms, non ancora 5000
    advanceMillis(LANDING_TIME - 1);

    readValidDistance();

    TEST_ASSERT_TRUE(
        State::matchDroneState(OPERATING)
    );

    TEST_ASSERT_FALSE(ledOnInstance.isOn());

    myTearDownLanding();
}


// ============================================================
// TEST 10
// Esattamente LANDING_TIME -> landing completato
//
// Il codice usa >= LANDING_TIME.
// ============================================================

void test_landing_complete_at_required_time()
{
    mySetUpLanding();

    startLanding();

    openDoorCompletely();

    sensorDddInstance.setDistance(LANDING_DISTANCE - 10);
    sensorDddInstance.resetSamples();

    // Prima misura valida -> start timer
    readValidDistance();

    // Passano esattamente 5 secondi
    advanceMillis(LANDING_TIME);

    readValidDistance();

    TEST_ASSERT_TRUE(
        State::matchDroneState(IDLE)
    );

    myTearDownLanding();
}


// ============================================================
// TEST 11
// Drone si allontana -> timer reset
// ============================================================

void test_landing_timer_resets_if_drone_moves_away()
{
    mySetUpLanding();

    startLanding();

    openDoorCompletely();

    // Drone sotto soglia
    sensorDddInstance.setDistance(LANDING_DISTANCE - 10);
    sensorDddInstance.resetSamples();

    // Parte il timer
    readValidDistance();

    // Passano 2 secondi
    advanceMillis(2000);

    // Drone torna sopra la soglia
    sensorDddInstance.setDistance(LANDING_DISTANCE + 10);
    sensorDddInstance.resetSamples();

    // Misura valida -> reset timer
    readValidDistance();

    /*
     * Ora il timer deve essere ripartito da zero.
     */
    sensorDddInstance.setDistance(LANDING_DISTANCE - 10);
    sensorDddInstance.resetSamples();

    readValidDistance();

    // Solo 3 secondi dal nuovo start
    advanceMillis(3000);
    readValidDistance();

    TEST_ASSERT_TRUE(
        State::matchDroneState(OPERATING)
    );

    TEST_ASSERT_FALSE(ledOnInstance.isOn());

    myTearDownLanding();
}


// ============================================================
// TEST 12
// Il valore DDD viene salvato nello State
// ============================================================

void test_landing_updates_distance_state()
{
    mySetUpLanding();

    startLanding();

    const float testDistance = LANDING_DISTANCE - 15;

    sensorDddInstance.setDistance(testDistance);
    sensorDddInstance.resetSamples();

    readValidDistance();

    TEST_ASSERT_EQUAL_FLOAT(
        testDistance,
        State::getDistanceToGround()
    );

    myTearDownLanding();
}


// ============================================================
// TEST 13
// Completamento -> LED L1 acceso
// ============================================================

void test_landing_complete_turns_on_led()
{
    mySetUpLanding();

    startLanding();

    openDoorCompletely();

    sensorDddInstance.setDistance(LANDING_DISTANCE - 10);
    sensorDddInstance.resetSamples();

    readValidDistance();

    advanceMillis(LANDING_TIME);
    readValidDistance();

    TEST_ASSERT_TRUE(ledOnInstance.isOn());

    myTearDownLanding();
}


// ============================================================
// TEST 14
// Completamento -> LCD DRONE INSIDE
// ============================================================

void test_landing_complete_lcd()
{
    mySetUpLanding();

    startLanding();

    openDoorCompletely();

    sensorDddInstance.setDistance(LANDING_DISTANCE - 10);
    sensorDddInstance.resetSamples();

    readValidDistance();

    advanceMillis(LANDING_TIME);
    readValidDistance();

    TEST_ASSERT_EQUAL_STRING(
        "DRONE INSIDE",
        lcdDisplayInstance.getLine1().c_str()
    );

    myTearDownLanding();
}


// ============================================================
// TEST 15
// Completamento -> DroneState IDLE
// ============================================================

void test_landing_complete_sets_idle()
{
    mySetUpLanding();

    startLanding();

    openDoorCompletely();

    sensorDddInstance.setDistance(LANDING_DISTANCE - 10);
    sensorDddInstance.resetSamples();

    readValidDistance();

    advanceMillis(LANDING_TIME);
    readValidDistance();

    TEST_ASSERT_TRUE(
        State::matchDroneState(IDLE)
    );

    myTearDownLanding();
}


// ============================================================
// TEST 16
// Completamento -> servo inizia la chiusura
// ============================================================

void test_landing_complete_starts_closing_door()
{
    mySetUpLanding();

    startLanding();

    openDoorCompletely();

    sensorDddInstance.setDistance(LANDING_DISTANCE - 10);
    sensorDddInstance.resetSamples();

    readValidDistance();

    advanceMillis(LANDING_TIME);
    readValidDistance();

    /*
     * completeLanding() chiama servoMotor->close()
     * e poi hw->updateClosingDoor().
     */
    TEST_ASSERT_TRUE(
        servoMotor->isClosing() ||
        servoMotor->isClosed()
    );

    myTearDownLanding();
}


// ============================================================
// TEST 17
// Dopo il landing la porta arriva completamente chiusa
// ============================================================

void test_landing_complete_closes_door()
{
    mySetUpLanding();

    startLanding();

    openDoorCompletely();

    sensorDddInstance.setDistance(LANDING_DISTANCE - 10);
    sensorDddInstance.resetSamples();

    readValidDistance();

    advanceMillis(LANDING_TIME);
    readValidDistance();

    // Evitiamo che il PIR faccia ripartire immediatamente il landing
    sensorPirInstance.setDroneDetected(false);

    closeDoorCompletely();

    TEST_ASSERT_TRUE(servoMotor->isClosed());
    TEST_ASSERT_EQUAL(0, servoMotor->getAngle());

    myTearDownLanding();
}


// ============================================================
// TEST 18
// Dopo un landing completato è possibile iniziarne un altro
// ============================================================

void test_landing_can_start_again_after_completion()
{
    mySetUpLanding();

    // Primo landing
    startLanding();

    openDoorCompletely();

    sensorDddInstance.setDistance(LANDING_DISTANCE - 10);
    sensorDddInstance.resetSamples();

    readValidDistance();

    advanceMillis(LANDING_TIME);
    readValidDistance();

    TEST_ASSERT_TRUE(
        State::matchDroneState(IDLE)
    );

    // Completiamo la chiusura
    sensorPirInstance.setDroneDetected(false);
    closeDoorCompletely();

    // Nuovo drone
    sensorPirInstance.setDroneDetected(true);

    land->tick();

    TEST_ASSERT_TRUE(servoMotor->isOpening());

    TEST_ASSERT_EQUAL_STRING(
        "LANDING",
        lcdDisplayInstance.getLine1().c_str()
    );

    myTearDownLanding();
}


// ============================================================
// TEST 19
// PIR non è più necessario dopo l'apertura
// ============================================================

void test_landing_does_not_need_pir_after_start()
{
    mySetUpLanding();

    startLanding();

    /*
     * Una volta entrati nello stato WAIT_DRONE_LAND,
     * il completamento dipende dal DDD, non dal PIR.
     */
    sensorPirInstance.setDroneDetected(false);

    openDoorCompletely();

    sensorDddInstance.setDistance(LANDING_DISTANCE - 10);
    sensorDddInstance.resetSamples();

    readValidDistance();

    advanceMillis(LANDING_TIME);
    readValidDistance();

    TEST_ASSERT_TRUE(
        State::matchDroneState(IDLE)
    );

    TEST_ASSERT_TRUE(ledOnInstance.isOn());

    myTearDownLanding();
}


// ============================================================
// TEST 20
// DDD non disponibile -> nessun atterraggio
//
// Questo test richiede:
// FakeSddd::setMeasurementAvailable(bool)
// ============================================================

void test_landing_ignores_unavailable_distance()
{
    mySetUpLanding();

    startLanding();

    sensorDddInstance.setDistance(LANDING_DISTANCE - 10);
    sensorDddInstance.resetSamples();

    // Simuliamo un sensore che non fornisce misure
    sensorDddInstance.setMeasurementAvailable(false);

    advanceMillis(LANDING_TIME);

    readValidDistance();

    TEST_ASSERT_TRUE(
        State::matchDroneState(OPERATING)
    );

    TEST_ASSERT_FALSE(ledOnInstance.isOn());

    /*
     * Riabilitiamo il sensore.
     * La prima misura valida deve solamente
     * far partire il timer.
     */
    sensorDddInstance.setMeasurementAvailable(true);
    sensorDddInstance.resetSamples();

    readValidDistance();

    TEST_ASSERT_TRUE(
        State::matchDroneState(OPERATING)
    );

    myTearDownLanding();
}


// ============================================================
// TEST 21
// La distanza viene controllata continuamente
// ============================================================

void test_landing_distance_must_remain_below_threshold()
{
    mySetUpLanding();

    startLanding();

    openDoorCompletely();

    // Prima sotto soglia
    sensorDddInstance.setDistance(LANDING_DISTANCE - 10);
    sensorDddInstance.resetSamples();

    readValidDistance();

    advanceMillis(3000);

    // Poi esattamente sulla soglia
    sensorDddInstance.setDistance(LANDING_DISTANCE);
    sensorDddInstance.resetSamples();

    readValidDistance();

    /*
     * Il timer deve essere stato azzerato.
     */
    advanceMillis(3000);

    sensorDddInstance.setDistance(LANDING_DISTANCE - 10);
    sensorDddInstance.resetSamples();

    readValidDistance();

    TEST_ASSERT_TRUE(
        State::matchDroneState(OPERATING)
    );

    myTearDownLanding();
}


// ============================================================
// UNITY
// ============================================================

void setup()
{

    UNITY_BEGIN();

    RUN_TEST(test_landing_no_drone_detected);
    RUN_TEST(test_landing_drone_detected);
    RUN_TEST(test_landing_lcd_message);

    RUN_TEST(test_landing_servo_opens);
    RUN_TEST(test_landing_servo_opens_completely);

    RUN_TEST(test_landing_distance_above_threshold);
    RUN_TEST(test_landing_distance_equal_threshold);
    RUN_TEST(test_landing_distance_below_threshold);

    RUN_TEST(test_landing_not_complete_before_time);
    RUN_TEST(test_landing_complete_at_required_time);

    RUN_TEST(test_landing_timer_resets_if_drone_moves_away);

    RUN_TEST(test_landing_updates_distance_state);

    RUN_TEST(test_landing_complete_turns_on_led);
    RUN_TEST(test_landing_complete_lcd);
    RUN_TEST(test_landing_complete_sets_idle);
    RUN_TEST(test_landing_complete_starts_closing_door);
    RUN_TEST(test_landing_complete_closes_door);

    RUN_TEST(test_landing_can_start_again_after_completion);

    RUN_TEST(test_landing_does_not_need_pir_after_start);

    RUN_TEST(test_landing_ignores_unavailable_distance);

    RUN_TEST(test_landing_distance_must_remain_below_threshold);

    UNITY_END();
}


void loop()
{
}