#include "./Util/test/TestInclude.h"
#include <unity.h>

static Task* door = new Door();
static bool TTM = false; // Test Task Motor flag

void mySetUpMotor() {

    if(!TTM) {
        std::cout << "Test Task Motor\n"<< std::endl;
        TTM = true;
    }
    State::setSystemState(OK);
    State::setDroneState(OPERATING);

    std::cout << "Current drone state: " << State::currentDroneStateString() << std::endl;
    resetMillis();
    hw->initAllHardware();
    door->init(10);
    std::cout << "Init: "
        << "isOpening=" << servoMotor->isOpening()
        << ", isOpened=" << servoMotor->isOpened()
        << ", isClosed=" << servoMotor->isClosed()
        << ", isClosing=" << servoMotor->isClosing()
        <<"\n"<< std::endl;
    std::cout.flush();
}

void myTearDownMotor() {
    std::cout<<"End of test Task Motor\n"<< std::endl;
}

// --- TEST CASES ---
void test_servo_opens_gradually() {
    mySetUpMotor();
    hw->openDoor();
    std::cout << "Open: "
            << "isOpening=" << servoMotor->isOpening()
            << ", isOpened=" << servoMotor->isOpened()
            << ", isClosed=" << servoMotor->isClosed()
            << ", isClosing=" << servoMotor->isClosing()
            <<"\n"<< std::endl;

    // step 1
    advanceMillis(20);
    door->tick();
    TEST_ASSERT_EQUAL(2, servoMotor->getAngle());
    std::cout << "IsOpening: "
            << "isOpening=" << servoMotor->isOpening()
            << ", isOpened=" << servoMotor->isOpened()
            << ", isClosed=" << servoMotor->isClosed()
            << ", isClosing=" << servoMotor->isClosing()
            <<"\n"<< std::endl;

    // step 2
    advanceMillis(20);
    door->tick();
    TEST_ASSERT_EQUAL(4, servoMotor->getAngle());

    // step 3
    advanceMillis(20);
    door->tick();
    TEST_ASSERT_EQUAL(6, servoMotor->getAngle());
    myTearDownMotor();
}

void test_servo_reaches_open_position() {
    mySetUpMotor();
    hw->openDoor();
    std::cout << "Open: "
            << "isOpening=" << servoMotor->isOpening()
            << ", isOpened=" << servoMotor->isOpened()
            << ", isClosed=" << servoMotor->isClosed()
            << ", isClosing=" << servoMotor->isClosing()
            <<"\n"<< std::endl;

    while(!servoMotor->isOpened()) {
        advanceMillis(20);
        door->tick();
    }

    TEST_ASSERT_TRUE(servoMotor->isOpened());
    TEST_ASSERT_EQUAL(180, servoMotor->getAngle());
    myTearDownMotor();
}

void test_servo_closes() {
    mySetUpMotor();
    servoMotor->setPosition(180);
    hw->closeDoor();
    std::cout << "Close: "
            << "isOpening=" << servoMotor->isOpening()
            << ", isOpened=" << servoMotor->isOpened()
            << ", isClosed=" << servoMotor->isClosed()
            << ", isClosing=" << servoMotor->isClosing()
            <<"\n"<< std::endl;

    advanceMillis(20);
    door->tick();

    TEST_ASSERT_EQUAL(178, servoMotor->getAngle());
    myTearDownMotor();
}

void test_servo_waits_step_delay() {
    mySetUpMotor();
    hw->openDoor();
    std::cout << "Open: "
            << "isOpening=" << servoMotor->isOpening()
            << ", isOpened=" << servoMotor->isOpened()
            << ", isClosed=" << servoMotor->isClosed()
            << ", isClosing=" << servoMotor->isClosing()
            <<"\n"<< std::endl;

    advanceMillis(10);
    door->tick();

    TEST_ASSERT_EQUAL(0, servoMotor->getAngle());
    myTearDownMotor();
}

