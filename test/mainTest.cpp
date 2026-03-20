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

void test_takeoff_command();
void test_landing_command();
void test_takeoff_not_from_idle();
void test_landing_not_from_operating();
void test_takeoff_case_insensitive();
void test_takeoff_with_spaces();
void test_unknown_command();
void test_command_ignored_when_not_ok();
void test_logs_command();
void test_logs_priority_over_commands();
void test_multiple_commands();
void test_send_idle_format();
void test_send_takeoff_format();
void test_send_landing_format();

void test_temperature_ok_stays_ok();
void test_temperature_high_goes_prealarm();
void test_temperature_high_goes_alarm();
void test_alarm_protocol_led_on();
void test_alarm_protocol_lcd_message();
void test_alarm_protocol_closes_door();
void test_reset_from_alarm();
void test_prealarm_back_to_ok_when_temp_normal();
void test_alarm_not_reentered_if_already_alarm();

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

    // InputOutput tests
    RUN_TEST(test_takeoff_command);
    RUN_TEST(test_landing_command);
    RUN_TEST(test_takeoff_not_from_idle);
    RUN_TEST(test_landing_not_from_operating);
    RUN_TEST(test_takeoff_case_insensitive);
    RUN_TEST(test_takeoff_with_spaces);
    RUN_TEST(test_unknown_command);
    RUN_TEST(test_command_ignored_when_not_ok);
    RUN_TEST(test_logs_command);
    RUN_TEST(test_logs_priority_over_commands);
    RUN_TEST(test_multiple_commands);
    RUN_TEST(test_send_idle_format);
    RUN_TEST(test_send_takeoff_format);
    RUN_TEST(test_send_landing_format);

    // CheckInsideTemperature tests
    RUN_TEST(test_temperature_ok_stays_ok);
    RUN_TEST(test_temperature_high_goes_prealarm);
    RUN_TEST(test_temperature_high_goes_alarm);
    RUN_TEST(test_alarm_protocol_led_on);
    RUN_TEST(test_alarm_protocol_lcd_message);
    RUN_TEST(test_alarm_protocol_closes_door);
    RUN_TEST(test_reset_from_alarm);
    RUN_TEST(test_prealarm_back_to_ok_when_temp_normal);
    RUN_TEST(test_alarm_not_reentered_if_already_alarm);

    return UNITY_END();
}