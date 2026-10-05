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

void test_landing_no_drone_detected();
void test_landing_drone_detected();
void test_landing_lcd_message();
void test_landing_servo_opens();
void test_landing_servo_opens_completely();
void test_landing_distance_above_threshold();
void test_landing_distance_equal_threshold();
void test_landing_distance_below_threshold();
void test_landing_not_complete_before_time();
void test_landing_complete_at_required_time();
void test_landing_timer_resets_if_drone_moves_away();
void test_landing_updates_distance_state();
void test_landing_complete_turns_on_led();
void test_landing_complete_lcd();
void test_landing_complete_sets_idle();
void test_landing_complete_starts_closing_door();
void test_landing_complete_closes_door();
void test_landing_can_start_again_after_completion();
void test_landing_does_not_need_pir_after_start();
void test_landing_ignores_unavailable_distance();
void test_landing_distance_must_remain_below_threshold();

void test_takeoff_initial_state_is_idle();
void test_takeoff_does_not_start_from_idle();
void test_takeoff_does_not_start_from_operating();
void test_takeoff_starts_when_state_is_takeoff();
void test_takeoff_opens_door();
void test_takeoff_servo_moves_2_degrees_after_20ms();
void test_takeoff_servo_reaches_180_degrees();
void test_takeoff_servo_does_not_exceed_180_degrees();
void test_takeoff_lcd_message();
void test_takeoff_distance_below_threshold();
void test_takeoff_distance_equal_threshold();
void test_takeoff_distance_above_threshold();
void test_takeoff_not_complete_before_time();
void test_takeoff_complete_at_required_time();
void test_takeoff_complete_after_required_time();
void test_takeoff_timer_resets_if_drone_comes_back();
void test_takeoff_timer_restarts_after_reset();
void test_takeoff_completes_after_full_second_interval();
void test_takeoff_updates_distance_state();
void test_takeoff_ignores_unavailable_distance();
void test_takeoff_resumes_after_ddd_becomes_available();
void test_takeoff_first_four_ddd_reads_are_not_valid();
void test_takeoff_fifth_ddd_read_is_valid();
void test_takeoff_works_with_pir_low();
void test_takeoff_works_with_pir_high();
void test_takeoff_completion_turns_off_led();
void test_takeoff_completion_prints_drone_out();
void test_takeoff_completion_sets_operating();
void test_takeoff_completion_starts_closing_door();
void test_takeoff_completion_closes_door();
void test_takeoff_does_not_complete_twice();
void test_takeoff_can_start_again();
void test_takeoff_new_cycle_requires_new_time();
void test_takeoff_zero_distance_does_not_complete();
void test_takeoff_large_distance_completes();
void test_takeoff_distance_oscillation_resets_timer();

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

    // Landing fase tests
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

    //takingOff fase testing
    RUN_TEST(test_takeoff_initial_state_is_idle);
    RUN_TEST(test_takeoff_does_not_start_from_idle);
    RUN_TEST(test_takeoff_does_not_start_from_operating);
    RUN_TEST(test_takeoff_starts_when_state_is_takeoff);
    RUN_TEST(test_takeoff_opens_door);
    RUN_TEST(test_takeoff_servo_moves_2_degrees_after_20ms);
    RUN_TEST(test_takeoff_servo_reaches_180_degrees);
    RUN_TEST(test_takeoff_servo_does_not_exceed_180_degrees);
    RUN_TEST(test_takeoff_lcd_message);
    RUN_TEST(test_takeoff_distance_below_threshold);
    RUN_TEST(test_takeoff_distance_equal_threshold);
    RUN_TEST(test_takeoff_distance_above_threshold);
    RUN_TEST(test_takeoff_not_complete_before_time);
    RUN_TEST(test_takeoff_complete_at_required_time);
    RUN_TEST(test_takeoff_complete_after_required_time);
    RUN_TEST(test_takeoff_timer_resets_if_drone_comes_back);
    RUN_TEST(test_takeoff_timer_restarts_after_reset);
    RUN_TEST(test_takeoff_completes_after_full_second_interval);
    RUN_TEST(test_takeoff_updates_distance_state);
    RUN_TEST(test_takeoff_ignores_unavailable_distance);
    RUN_TEST(test_takeoff_resumes_after_ddd_becomes_available);
    RUN_TEST(test_takeoff_first_four_ddd_reads_are_not_valid);
    RUN_TEST(test_takeoff_fifth_ddd_read_is_valid);
    RUN_TEST(test_takeoff_works_with_pir_low);
    RUN_TEST(test_takeoff_works_with_pir_high);
    RUN_TEST(test_takeoff_completion_turns_off_led);
    RUN_TEST(test_takeoff_completion_prints_drone_out);
    RUN_TEST(test_takeoff_completion_sets_operating);
    RUN_TEST(test_takeoff_completion_starts_closing_door);
    RUN_TEST(test_takeoff_completion_closes_door);
    RUN_TEST(test_takeoff_does_not_complete_twice);
    RUN_TEST(test_takeoff_can_start_again);
    RUN_TEST(test_takeoff_new_cycle_requires_new_time);
    RUN_TEST(test_takeoff_zero_distance_does_not_complete);
    RUN_TEST(test_takeoff_large_distance_completes);
    RUN_TEST(test_takeoff_distance_oscillation_resets_timer);

    return UNITY_END();
}