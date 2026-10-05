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
    scheduler.init(20);

    // Reset di tutte le task
    for (auto t : tasks) {
        t->reset();
    }

    // Configurazione periodi reali come nel main
    io->init(20);
    temp->init(20);
    door->init(20);

    takeoff->init(40);
    landing->init(40);

    led->init(500);

    // Registrazione delle task nello scheduler
    for (auto t : tasks) {
        scheduler.addTask(t);
    }
}

// Helper per avanzare di N tick dello scheduler (ciascun tick = 20ms)
void stepScheduler(int ticks) {
    for (int i = 0; i < ticks; i++) {
        fakeTimer.advanceTicks(20); // o il periodo base dello scheduler
        scheduler.schedule();
    }
}

// --- TEST CASES ---
void test_alarm_blocks_movement_and_led() {
    mySetUpSchedulare();
    State::setSystemState(ALARM);
    State::setDroneState(IDLE);

    // Avanza di 500ms per dare tempo a qualsiasi task di eseguire se non fosse bloccata
    fakeTimer.advanceTicks(500);
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

    fakeTimer.advanceTicks(20);
    scheduler.schedule();

    TEST_ASSERT_EQUAL(0, temp->getCount());
    myTearDownSchedulare();
}

void test_takeoff_only_in_takeoff_state() {
    mySetUpSchedulare();
    State::setSystemState(OK);
    State::setDroneState(IDLE);

    // Nello stato IDLE, takeoff non deve eseguire
    fakeTimer.advanceTicks(40);
    scheduler.schedule();
    TEST_ASSERT_EQUAL(0, takeoff->getCount());

    // Passiamo a TAKEOFF
    State::setDroneState(TAKEOFF);
    fakeTimer.advanceTicks(40);
    scheduler.schedule();
    TEST_ASSERT_EQUAL(1, takeoff->getCount());
    myTearDownSchedulare();
}

void test_landing_only_in_landing_state() {
    mySetUpSchedulare();
    State::setSystemState(OK);
    State::setDroneState(OPERATING);

    // In OPERATING, landing non deve eseguire
    fakeTimer.advanceTicks(40);
    scheduler.schedule();
    TEST_ASSERT_EQUAL(0, landing->getCount());

    // Passiamo a LANDING
    State::setDroneState(LANDING);
    fakeTimer.advanceTicks(40);
    scheduler.schedule();
    TEST_ASSERT_EQUAL(1, landing->getCount());
    myTearDownSchedulare();
}

void test_led_runs_every_tick_while_takeoff_active() {
    mySetUpSchedulare();
    State::setSystemState(OK);

    // 1. In OPERATING per 500ms (25 tick da 20ms) -> LED non deve scattare
    State::setDroneState(OPERATING);
    stepScheduler(25); // Avanza 500ms con schedule ad ogni tick
    TEST_ASSERT_EQUAL(0, led->getCount());

    // 2. In TAKEOFF per 500ms (25 tick da 20ms) -> LED scatta 1 volta
    State::setDroneState(TAKEOFF);
    stepScheduler(25); // Avanza altri 500ms
    TEST_ASSERT_EQUAL(1, led->getCount());

    // 3. Altri 500ms in TAKEOFF -> LED scatta la 2a volta
    stepScheduler(25);
    TEST_ASSERT_EQUAL(2, led->getCount());

    myTearDownSchedulare();
}

void test_door_runs_only_while_moving() {
    mySetUpSchedulare();
    State::setSystemState(OK);
    State::setDroneState(IDLE);

    // Porta ferma: non esegue
    fakeTimer.advanceTicks(20);
    scheduler.schedule();
    TEST_ASSERT_EQUAL(0, door->getCount());

    // Porta in movimento: deve eseguire
    servoMotor->open();
    fakeTimer.advanceTicks(20);
    scheduler.schedule();
    TEST_ASSERT_EQUAL(1, door->getCount());

    myTearDownSchedulare();
}

void test_inputoutput_always_runs() {
    mySetUpSchedulare();
    State::setSystemState(ALARM);
    State::setDroneState(LANDING);

    fakeTimer.advanceTicks(20);
    scheduler.schedule();

    TEST_ASSERT_EQUAL(1, io->getCount());
    myTearDownSchedulare();
}