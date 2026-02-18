#include "./Util/test/TestInclude.h"
#include <unity.h>

// --- Hardware e scheduler fake ---
FakeTimer fakeTimer;
Scheduler scheduler(fakeTimer);

// Task fake
FakeTask* io      = new FakeTask(T_INPUTOUTPUT);
FakeTask* temp    = new FakeTask(T_CHECK_INSIDE_TEMPERATURE);
FakeTask* takeoff = new FakeTask(T_TAKEOFF);
FakeTask* landing = new FakeTask(T_LANDING);
FakeTask* led     = new FakeTask(T_LEDINACTION);
FakeTask* door    = new FakeTask(T_DOOR);

FakeTask* tasks[] = { io, temp, takeoff, landing, led, door };

void initScheduler();

// --- Funzione di setup per ogni test ---
extern "C" void setUp() {
    // Inizializza scheduler
    initScheduler();  // Inizializza scheduler e resetta tutte le task
}

// --- TearDown se necessario ---
extern "C" void tearDown() {
    // Pulizia post-test (spesso nulla nei fake)
}

// --- Helper per resettare scheduler e task ---
void initScheduler() {
    scheduler.reset();
    for (auto t : tasks) {
        t->reset();
        scheduler.addTask(t);
    }
}

// --- TEST CASES ---
void test_alarm_blocks_movement_and_led() {
    State::setSystemState(ALARM);
    State::setDroneState(IDLE);

    scheduler.schedule();

    TEST_ASSERT_EQUAL(0, takeoff->getCount());
    TEST_ASSERT_EQUAL(0, landing->getCount());
    TEST_ASSERT_EQUAL(0, led->getCount());
}

void test_temperature_disabled_in_operating() {
    State::setSystemState(OK);
    State::setDroneState(OPERATING);

    scheduler.schedule();

    TEST_ASSERT_EQUAL(0, temp->getCount());
}

void test_takeoff_only_in_takeoff_state() {
    State::setDroneState(IDLE);
    scheduler.schedule();
    TEST_ASSERT_EQUAL(0, takeoff->getCount());

    State::setDroneState(TAKEOFF);
    scheduler.schedule();
    TEST_ASSERT_EQUAL(1, takeoff->getCount());
}

void test_landing_only_in_landing_state() {
    State::setDroneState(OPERATING);
    scheduler.schedule();
    TEST_ASSERT_EQUAL(0, landing->getCount());

    State::setDroneState(LANDING);
    scheduler.schedule();
    TEST_ASSERT_EQUAL(1, landing->getCount());
}

void test_led_runs_every_tick_while_takeoff_active() {
    State::setDroneState(OPERATING);
    scheduler.schedule();
    TEST_ASSERT_EQUAL(0, led->getCount());

    State::setDroneState(TAKEOFF);
    scheduler.schedule();
    TEST_ASSERT_EQUAL(1, led->getCount());

    scheduler.schedule();
    TEST_ASSERT_EQUAL(2, led->getCount());
}

void test_door_runs_only_while_moving() {
    scheduler.schedule();
    TEST_ASSERT_EQUAL(0, door->getCount());

    servoMotor->open();
    scheduler.schedule();
    TEST_ASSERT_EQUAL(1, door->getCount());
}

void test_inputoutput_always_runs() {
    State::setSystemState(ALARM);
    State::setDroneState(LANDING);

    scheduler.schedule();

    TEST_ASSERT_EQUAL(1, io->getCount());
}

// --- MAIN per Unity ---
int main() {
    hw->initAllHardware();

    UNITY_BEGIN();

    RUN_TEST(test_alarm_blocks_movement_and_led);
    RUN_TEST(test_temperature_disabled_in_operating);
    RUN_TEST(test_takeoff_only_in_takeoff_state);
    RUN_TEST(test_landing_only_in_landing_state);
    RUN_TEST(test_led_runs_every_tick_while_takeoff_active);
    RUN_TEST(test_door_runs_only_while_moving);
    RUN_TEST(test_inputoutput_always_runs);

    return UNITY_END();
}
