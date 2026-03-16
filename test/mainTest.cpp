#include <unity.h>

// Include tutti i tuoi test
void test_alarm_blocks_movement_and_led();
void test_temperature_disabled_in_operating();
void test_takeoff_only_in_takeoff_state();
void test_landing_only_in_landing_state();
void test_led_runs_every_tick_while_takeoff_active();
void test_door_runs_only_while_moving();
void test_inputoutput_always_runs();

void test_servo_opens_gradually();
void test_servo_reaches_open_position();
void test_servo_closes();
void test_servo_waits_step_delay();

void setUp() {}
void tearDown() {}

int main() {
    UNITY_BEGIN();

    // Scheduler tests
    RUN_TEST(test_alarm_blocks_movement_and_led);
    RUN_TEST(test_temperature_disabled_in_operating);
    RUN_TEST(test_takeoff_only_in_takeoff_state);
    RUN_TEST(test_landing_only_in_landing_state);
    RUN_TEST(test_led_runs_every_tick_while_takeoff_active);
    RUN_TEST(test_door_runs_only_while_moving);
    RUN_TEST(test_inputoutput_always_runs);

    // Door tests
    RUN_TEST(test_servo_opens_gradually);
    RUN_TEST(test_servo_reaches_open_position);
    RUN_TEST(test_servo_closes);
    RUN_TEST(test_servo_waits_step_delay);

    return UNITY_END();
}