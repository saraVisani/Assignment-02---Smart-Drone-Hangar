#include "./Util/test/TestInclude.h"
#include <unity.h>

static Task* tIO = new InputOutput();
static bool TIO = false; // Test Task Motor flag

void mySetUpInputOutput() {

    if(!TIO) {
        std::cout << "Test Task InputOutput\n"<< std::endl;
        TIO = true;
    }
    resetMillis();
    Serial.clear();
    hw->initAllHardware();
    tIO->init(10);
}

void myTearDownInputOutput() {
    std::cout<<"End of test Task InputOutput\n"<< std::endl;
}

// --- TEST CASES ---

// --- BASIC COMMANDS ---

void test_takeoff_command() {
    mySetUpInputOutput();

    State::setSystemState(OK);
    State::setDroneState(IDLE);

    Serial.inject("take off");

    tIO->tick();

    TEST_ASSERT_TRUE(State::matchDroneState(TAKEOFF));

    myTearDownInputOutput();
}

void test_landing_command() {
    mySetUpInputOutput();

    State::setSystemState(OK);
    State::setDroneState(OPERATING);

    Serial.inject("landing");

    tIO->tick();

    TEST_ASSERT_TRUE(State::matchDroneState(LANDING));

    myTearDownInputOutput();
}

// --- INVALID TRANSITIONS ---

void test_takeoff_not_from_idle() {
    mySetUpInputOutput();

    State::setSystemState(OK);
    State::setDroneState(OPERATING);

    Serial.inject("take off");

    tIO->tick();

    TEST_ASSERT_TRUE(State::matchDroneState(OPERATING));

    myTearDownInputOutput();
}

void test_landing_not_from_operating() {
    mySetUpInputOutput();

    State::setSystemState(OK);
    State::setDroneState(IDLE);

    Serial.inject("landing");

    tIO->tick();

    TEST_ASSERT_TRUE(State::matchDroneState(IDLE));

    myTearDownInputOutput();
}

// --- INPUT ROBUSTNESS ---

void test_takeoff_case_insensitive() {
    mySetUpInputOutput();

    State::setSystemState(OK);
    State::setDroneState(IDLE);

    Serial.inject("TaKe OfF");

    tIO->tick();

    TEST_ASSERT_TRUE(State::matchDroneState(TAKEOFF));

    myTearDownInputOutput();
}

void test_takeoff_with_spaces() {
    mySetUpInputOutput();

    State::setSystemState(OK);
    State::setDroneState(IDLE);

    Serial.inject("   take off   ");

    tIO->tick();

    TEST_ASSERT_TRUE(State::matchDroneState(TAKEOFF));

    myTearDownInputOutput();
}

void test_unknown_command() {
    mySetUpInputOutput();

    State::setSystemState(OK);
    State::setDroneState(IDLE);

    Serial.inject("banana");

    tIO->tick();

    TEST_ASSERT_TRUE(State::matchDroneState(IDLE));

    myTearDownInputOutput();
}

// --- SYSTEM NOT OK ---

void test_command_ignored_when_not_ok() {
    mySetUpInputOutput();

    State::setSystemState(ALARM);
    State::setDroneState(IDLE);

    Serial.inject("take off");

    tIO->tick();

    TEST_ASSERT_TRUE(Serial.serialContains("Command ignored"));

    myTearDownInputOutput();
}

// --- LOGS PRIORITY ---

void test_logs_command() {
    mySetUpInputOutput();

    Serial.inject("logs");

    tIO->tick();

    auto msg = Serial.getLastOutput();

    std::cout << "Output message: " << msg << std::endl;

    TEST_ASSERT_TRUE(msg.find("*-") != std::string::npos);

    myTearDownInputOutput();
}

void test_logs_priority_over_commands() {
    mySetUpInputOutput();

    State::setSystemState(ALARM);
    State::setDroneState(IDLE);

    Serial.inject("logs");
    Serial.inject("take off");

    tIO->tick();

    auto output = Serial.getOutput();

    // Deve eseguire solo logs
    TEST_ASSERT_TRUE(output[0].find("*-") != std::string::npos);

    // Stato NON cambia
    TEST_ASSERT_TRUE(State::matchDroneState(IDLE));

    myTearDownInputOutput();
}

// --- MULTIPLE COMMANDS ---

void test_multiple_commands() {
    mySetUpInputOutput();

    State::setSystemState(OK);
    State::setDroneState(IDLE);

    Serial.inject("take off");
    Serial.inject("landing");

    tIO->tick();

    // landing non deve funzionare dopo takeoff
    TEST_ASSERT_TRUE(State::matchDroneState(TAKEOFF));

    myTearDownInputOutput();
}

// --- OUTPUT TESTS (SEND) ---

void test_send_idle_format() {
    mySetUpInputOutput();

    State::setSystemState(OK);
    State::setDroneState(IDLE);

    tIO->tick();

    auto msg = Serial.getLastOutput();

    std::cout << "Output message: " << msg << std::endl;

    TEST_ASSERT_TRUE(msg.find("OK-Idle") != std::string::npos);
    TEST_ASSERT_TRUE(msg.find("N/A") != std::string::npos);

    myTearDownInputOutput();
}

void test_send_takeoff_format() {
    mySetUpInputOutput();

    State::setSystemState(OK);
    State::setDroneState(TAKEOFF);

    tIO->tick();

    auto msg = Serial.getLastOutput();

    std::cout << "Output message: " << msg << std::endl;

    TEST_ASSERT_TRUE(msg.find("Take off") != std::string::npos);
    TEST_ASSERT_TRUE(msg.find("N/A") == std::string::npos);

    myTearDownInputOutput();
}

void test_send_landing_format() {
    mySetUpInputOutput();

    State::setSystemState(OK);
    State::setDroneState(LANDING);

    tIO->tick();

    auto msg = Serial.getLastOutput();

    TEST_ASSERT_TRUE(msg.find("-*-") != std::string::npos);

    myTearDownInputOutput();
}