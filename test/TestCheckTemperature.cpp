#include "./Util/test/TestInclude.h"
#include <unity.h>

static Task* temp = new CheckInsideTemperature();
static bool TCT = false; // Test Task Motor flag

void mySetUpCheckTemperature() {

    if(!TCT) {
        std::cout << "Test Task CheckInsideTemperature\n"<< std::endl;
        TCT = true;
    }
    resetMillis();
    hw->initAllHardware();
    temp->init(10);
}

void myTearDownCheckTemperature() {
    std::cout<<"End of test Task CheckInsideTemperature\n"<< std::endl;
}

// --- TEST CASES ---

void test_temperature_ok_stays_ok() {
    mySetUpCheckTemperature();

    auto fakeTemp = (FakeStemp*)sensorTemp;

    State::setSystemState(OK);
    fakeTemp->temp = TEMP_THRESHOLD - 5;

    temp->tick();

    TEST_ASSERT_TRUE(State::matchSystemState(OK));

    myTearDownCheckTemperature();
}

void test_temperature_high_goes_prealarm() {
    mySetUpCheckTemperature();
    advanceMillis(1);

    auto fakeTemp = (FakeStemp*)sensorTemp;

    State::setSystemState(OK);
    fakeTemp->temp = TEMP_THRESHOLD + 5;

    temp->tick(); // primo tick → salva lastTempCheckTime

    advanceMillis(PREALARM_TIME + 1);

    temp->tick(); // secondo tick → ora entra in PREALARM


    TEST_ASSERT_TRUE(State::matchSystemState(PREALARM));

    myTearDownCheckTemperature();
}

void test_temperature_high_goes_alarm() {
    mySetUpCheckTemperature();
    advanceMillis(1);

    auto fakeTemp = (FakeStemp*)sensorTemp;
    auto fakeLcd = (FakeLcd*)lcdDisplay;

    State::setSystemState(OK);
    fakeTemp->temp = TEMP_THRESHOLD + 10;

    temp->tick(); // inizializza timer

    advanceMillis(ALARM_TIME + 1);

    temp->tick(); // ora può diventare ALARM

    Serial.printToConsole("DEBUG: matchSystemState(ALARM) = " + String(State::matchSystemState(ALARM)));
    Serial.printToConsole("DEBUG: fakeLcd->isCleared() = " + String(fakeLcd->isCleared()));

    TEST_ASSERT_TRUE(State::matchSystemState(ALARM));
    TEST_ASSERT_FALSE(fakeLcd->isCleared());

    myTearDownCheckTemperature();
}

void test_alarm_protocol_led_on() {
    mySetUpCheckTemperature();

    auto fakeLed = (FakeLed*)ledAlarm;

    State::setSystemState(ALARM);

    temp->tick();

    TEST_ASSERT_TRUE(fakeLed->isOn());
    TEST_ASSERT_TRUE(fakeLed->getOnCount() > 0);

    myTearDownCheckTemperature();
}

void test_alarm_protocol_lcd_message() {
    mySetUpCheckTemperature();

    auto fakeLcd = (FakeLcd*)lcdDisplay;

    State::setSystemState(ALARM);

    temp->tick();

    TEST_ASSERT_EQUAL_STRING("ALARM TEMP", fakeLcd->getLine1().c_str());
    TEST_ASSERT_EQUAL_STRING("TOO HIGH", fakeLcd->getLine2().c_str());

    myTearDownCheckTemperature();
}

void test_alarm_protocol_closes_door() {
    mySetUpCheckTemperature();

    auto fakeServo = (FakeServoMotor*)servoMotor;

    State::setSystemState(ALARM);

    temp->tick();

    TEST_ASSERT_TRUE(fakeServo->isClosing() || fakeServo->isClosed());

    myTearDownCheckTemperature();
}

void test_reset_from_alarm() {
    mySetUpCheckTemperature();

    auto fakeLed = (FakeLed*)ledAlarm;
    auto fakeLcd = (FakeLcd*)lcdDisplay;

    State::setSystemState(ALARM);

    // Simula reset
    resetAllarm = true;

    temp->tick();

    TEST_ASSERT_TRUE(State::matchSystemState(OK));
    TEST_ASSERT_FALSE(fakeLed->isOn());
    TEST_ASSERT_TRUE(fakeLcd->isCleared());

    myTearDownCheckTemperature();
}

void test_prealarm_back_to_ok_when_temp_normal() {
    mySetUpCheckTemperature();

    auto fakeTemp = (FakeStemp*)sensorTemp;

    State::setSystemState(PREALARM);

    fakeTemp->temp = TEMP_THRESHOLD - 5;

    temp->tick();

    TEST_ASSERT_TRUE(State::matchSystemState(OK));

    myTearDownCheckTemperature();
}

void test_alarm_not_reentered_if_already_alarm() {
    mySetUpCheckTemperature();

    auto fakeTemp = (FakeStemp*)sensorTemp;

    State::setSystemState(ALARM);

    fakeTemp->temp = TEMP_THRESHOLD - 5;

    temp->tick();

    // Deve rimanere in ALARM finché non resetti
    TEST_ASSERT_TRUE(State::matchSystemState(ALARM));

    myTearDownCheckTemperature();
}