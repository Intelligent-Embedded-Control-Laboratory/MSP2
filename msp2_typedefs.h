/**
 * @file msp2_typedefs.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-01-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <Arduino.h>

typedef struct msp_sensor_rangefinder_t
{
    uint8_t quality;        // [0 ~ 255]
    int32_t distance_mm;    // Negative range for out of range
} msp_sensor_rangefinder_t; // total 5 bytes

typedef struct msp_sensor_optical_flow_t
{
    uint8_t quality; // [0 ~255]
    int32_t motionX;
    int32_t motionY;
} msp_sensor_optical_flow_t;