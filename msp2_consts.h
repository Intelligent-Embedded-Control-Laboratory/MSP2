/**
 * @file msp2_consts.h
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

enum MSP2_SENSOR_ID : uint16_t
{
    MSP2_SENSOR_RANGEFINDER = 0x1F01,
    MSP2_SENSOR_OPTIC_FLOW = 0x1F02
};