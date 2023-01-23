/**
 * @file msp2_example_utility.hpp
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
#include "msp2.h"

void print_msp2_data(MSP2 &msp2)
{
    Serial.print("Distance Quality: ");
    Serial.print(msp2.get_rangefinder().quality);
    Serial.print(", Distance(mm): ");
    Serial.print(msp2.get_rangefinder().distance_mm);
    Serial.print(", Optical flow Quality: ");
    Serial.print(msp2.get_optic_flow().quality);
    Serial.print(", motionX: ");
    Serial.print(msp2.get_optic_flow().motionX);
    Serial.print(", motionY: ");
    Serial.print(msp2.get_optic_flow().motionY);
    Serial.println();
    Serial.flush();
}