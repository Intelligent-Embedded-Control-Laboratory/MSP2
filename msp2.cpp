#include "msp2.h"

#define MSP2_DEBUG_ENABLE 0

void MSP2::begin(HardwareSerial& _MSPSerial, uint32_t baud)
{
    MSPSerial = &_MSPSerial;
    MSPSerial->begin(baud);

    event_flag = MSP2_WAIT_START_BYTES;
}

uint16_t MSP2::read()
{
    while (event_flag == MSP2_WAIT_START_BYTES && MSPSerial->available() >= 8)
    {
        header.start_bytes[0] = (uint8_t)MSPSerial->read();

        if (header.start_bytes[0] == 0x24)
        {
            header.start_bytes[1] = (uint8_t)MSPSerial->read();

            if (header.start_bytes[1] == 0x58)
            {
                MSPSerial->readBytes(&header.type, 6U);

                event_flag = MSP2_WAIT_PACKET;
            }
        }
    }

#if MSP2_DEBUG_ENABLE
    Serial.print("Start byte[0] = ");
    Serial.print(header.start_bytes[0], HEX);
    Serial.print(" ");

    Serial.print("Start byte[1] = ");
    Serial.print(header.start_bytes[1], HEX);
    Serial.printf(" Size: %d", header.payload_size);
    Serial.printf(" Flag: %d", event_flag);
    Serial.printf(" Buffer %d bytes available ", MSPSerial->available());
    Serial.println();
#endif

    if (event_flag == MSP2_WAIT_PACKET && MSPSerial->available() >= (int)(header.payload_size) + 1)
    {
#if MSP2_DEBUG_ENABLE
        Serial.print("Payload Size: ");
        Serial.println((int)header.payload_size);
#endif
        // Parse data
        switch (header.function)
        {
        case MSP2_SENSOR_RANGEFINDER:
            _is_update_rangefinder = true;
            rangefinder.quality = (uint8_t)MSPSerial->read();
            MSPSerial->readBytes((uint8_t*)&rangefinder.distance_mm, header.payload_size - 1);
#if MSP2_DEBUG_ENABLE
            Serial.println("RANGEFINDER!");
#endif
            break;
        case MSP2_SENSOR_OPTIC_FLOW:
            _is_update_optic_flow = true;
            optical_flow.quality = (uint8_t)(MSPSerial->read());
            MSPSerial->readBytes((uint8_t*)(&optical_flow.motionDX), header.payload_size - 1);
#if MSP2_DEBUG_ENABLE
            Serial.println("OPTICAL FLOW!");
#endif
            break;
        default:
            Serial.println("No matched ID!");
            Serial.println(header.function);
        }
        event_flag = MSP2_WAIT_START_BYTES;
        checksum = (uint8_t)(MSPSerial->read());

        // return header.function; // return data id
        return 0x0001;
    }
    return 0x0000; // mean data not yet ready
}