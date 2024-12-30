// Copyright 2024 Lukas Hrazky
//
// This file is part of the Refloat VESC package.
//
// Refloat VESC package is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
//
// Refloat VESC package is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include "conf/datatypes.h"
#include "footpad_sensor.h"
#include "led_driver.h"
#include "state.h"

#define LEDS_REFRESH_RATE 25

#define LEDS_FRONT_AND_REAR_COUNT_MAX 60

typedef struct {
    uint8_t map[LEDS_FRONT_AND_REAR_COUNT_MAX];
} CipherData;

typedef union {
    CipherData cipher;
} TransitionData;

typedef struct {
    LedTransition transition;
    float split;
} TransitionState;

typedef struct {
    uint8_t start;
    uint8_t length;
    bool reverse;
    float brightness;
    TransitionData trans_data;
} LedStrip;

typedef struct {
    LedStrip status_strip;
    LedStrip front_strip;
    LedStrip rear_strip;

    const CfgLeds *cfg;

    float last_updated;
    State state;
    float pitch;

    float left_sensor;
    float right_sensor;

    float on_off_fade;

    float duty_threshold;
    float status_duty_blend;
    float status_idle_blend;
    float status_idle_time;
    float status_animation_start;

    float status_on_front_blend;
    float status_on_front_idle_blend;
    float status_on_front_idle_time;
    bool board_is_upright;

    float split_distance;
    bool headlights_on;
    bool direction_forward;
    float headlights_time;
    float animation_start;

    TransitionState headlights_trans;
    TransitionState dir_trans;

    const LedBar *front_bar;
    const LedBar *front_dir_target;
    const LedBar *front_time_target;

    const LedBar *rear_bar;
    const LedBar *rear_dir_target;
    const LedBar *rear_time_target;

    uint32_t *led_data;
    uint8_t led_count;
    LedDriver led_driver;

    uint8_t *led_comms_buffer;
    uint8_t led_comms_buffer_size;
} Leds;

bool leds_init(Leds *leds, CfgHwLeds *hw_cfg, const CfgLeds *cfg, FootpadSensorState fs_state);

void leds_configure(Leds *leds, const CfgLeds *cfg);

void leds_update(Leds *leds, const State *state, FootpadSensorState fs_state);

void leds_destroy(Leds *leds);
