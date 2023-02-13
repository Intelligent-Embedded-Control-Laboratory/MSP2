/**
 * @file MSP2.h
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

#include "msp2_consts.h"
#include "msp2_typedefs.h"

class MSP2
{
public:
    void begin(HardwareSerial &_MSPSerial, uint32_t baud);
    uint16_t read();
    const msp_sensor_rangefinder_t &get_rangefinder() const { return rangefinder; }
    const msp_sensor_optical_flow_t &get_optic_flow() const { return optical_flow; }

// protected:
    HardwareSerial *MSPSerial;
    int8_t event_flag;
    enum MSP2_STATUS
    {
        MSP2_WAIT_START_BYTES,
        MSP2_WAIT_PACKET
    };
    struct msp2_header_t
    {
        uint8_t start_bytes[2];
        uint8_t type;
        uint8_t flag;
        uint16_t function;
        uint16_t payload_size;
    } header;
    msp_sensor_rangefinder_t rangefinder;   // total 5 bytes
    msp_sensor_optical_flow_t optical_flow; // total 9 bytes
    uint8_t checksum;
};