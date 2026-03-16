#include "./Util/test/TestInclude.h"
#include <unity.h>

// --- Hardware e scheduler fake ---
static FakeTimer fakeTimer;
static Scheduler scheduler(fakeTimer);

// Task fake
static FakeTask* io = new FakeTask(T_INPUTOUTPUT);
static FakeTask* temp = new FakeTask(T_CHECK_INSIDE_TEMPERATURE);
static FakeTask* takeoff = new FakeTask(T_TAKEOFF);
static FakeTask* landing = new FakeTask(T_LANDING);
static FakeTask* led = new FakeTask(T_LEDINACTION);
static FakeTask* door = new FakeTask(T_DOOR);

static FakeTask* tasks[] = {io, temp, takeoff, landing, led, door};

static bool TS = false; // Task Scheduler flag

void initScheduler();

void mySetUpSchedulare() {
    if(!TS) {
        std::cout << "Test Scheduler\n"<< std::endl;
        TS = true;
    }
    // Inizializza scheduler
    hw->initAllHardware();
    initScheduler();  // Inizializza scheduler e resetta tutte le task
    std::cout << "Before schedule: "
        << "isOpening=" << servoMotor->isOpening()
        << ", isOpened=" << servoMotor->isOpened()
        << ", isClosed=" << servoMotor->isClosed()
        << ", isClosing=" << servoMotor->isClosing()
        <<"\n"<< std::endl;
}

void myTearDownSchedulare() {
    std::cout<<"End of test Scheduler\n"<< std::endl;
}

// --- Helper per resettare scheduler e task ---
void initScheduler() {
    scheduler.reset();
    scheduler.init(100);
    for (auto t : tasks) {
        t->reset();
        t->init(10);
        scheduler.addTask(t);
    }
}

// --- TEST CASES ---
void test_alarm_blocks_movement_and_led() {
    mySetUpSchedulare();
    State::setSystemState(ALARM);
    State::setDroneState(IDLE);

    scheduler.schedule();

    TEST_ASSERT_EQUAL(0, takeoff->getCount());
    TEST_ASSERT_EQUAL(0, landing->getCount());
    TEST_ASSERT_EQUAL(0, led->getCount());
    myTearDownSchedulare();
}

void test_temperature_disabled_in_operating() {
    mySetUpSchedulare();
    State::setSystemState(OK);
    State::setDroneState(OPERATING);

    scheduler.schedule();

    TEST_ASSERT_EQUAL(0, temp->getCount());
    myTearDownSchedulare();
}

void test_takeoff_only_in_takeoff_state() {
    mySetUpSchedulare();
    State::setDroneState(IDLE);
    scheduler.schedule();
    TEST_ASSERT_EQUAL(0, takeoff->getCount());

    State::setDroneState(TAKEOFF);
    scheduler.schedule();
    TEST_ASSERT_EQUAL(1, takeoff->getCount());
    myTearDownSchedulare();
}

void test_landing_only_in_landing_state() {
    mySetUpSchedulare();
    State::setDroneState(OPERATING);
    scheduler.schedule();
    TEST_ASSERT_EQUAL(0, landing->getCount());

    State::setDroneState(LANDING);
    scheduler.schedule();
    TEST_ASSERT_EQUAL(1, landing->getCount());
    myTearDownSchedulare();
}

void test_led_runs_every_tick_while_takeoff_active() {
    mySetUpSchedulare();
    State::setDroneState(OPERATING);
    scheduler.schedule();
    TEST_ASSERT_EQUAL(0, led->getCount());

    State::setDroneState(TAKEOFF);
    scheduler.schedule();
    TEST_ASSERT_EQUAL(1, led->getCount());

    scheduler.schedule();
    TEST_ASSERT_EQUAL(2, led->getCount());
    myTearDownSchedulare();
}

void test_door_runs_only_while_moving() {
    mySetUpSchedulare();
    scheduler.schedule();
    TEST_ASSERT_EQUAL(0, door->getCount());

    servoMotor->open();
    scheduler.schedule();
    TEST_ASSERT_EQUAL(1, door->getCount());
    myTearDownSchedulare();
}

void test_inputoutput_always_runs() {
    mySetUpSchedulare();
    State::setSystemState(ALARM);
    State::setDroneState(LANDING);

    scheduler.schedule();

    TEST_ASSERT_EQUAL(1, io->getCount());
    myTearDownSchedulare();
}