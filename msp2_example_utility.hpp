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

void msp2_print_all_data(MSP2 &msp2)
{
    Serial.print("Distance Quality: ");
    Serial.print(msp2.get_rangefinder().quality);
    Serial.print(", Distance(mm): ");
    Serial.print(msp2.get_rangefinder().distance_mm);
    Serial.print(", Optical flow Quality: ");
    Serial.print(msp2.get_optic_flow().quality);
    Serial.print(", motionDX: ");
    Serial.print(msp2.get_optic_flow().motionDX);
    Serial.print(", motionDY: ");
    Serial.print(msp2.get_optic_flow().motionDY);
    Serial.println();
    Serial.flush();
}