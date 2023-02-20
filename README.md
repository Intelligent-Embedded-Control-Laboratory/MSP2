# MSP2

Since 2023-01-23

## How to use

main.cpp

```cpp
#include <Arduino.h>
#include <msp2.h>
#include <msp2_example_utility.hpp>

#define HW_SERIAL_INTERFACE_MSP2_SENSOR Serial3
#define HW_SERIAL_BAUD_RATE_MSP2_SENSOR 115200

MSP2 msp2;

void setup()
{
    Serial.begin(115200);

    static uint8_t msp2_sensors_buffer[1024];
    HW_SERIAL_INTERFACE_MSP2_SENSOR.addMemoryForRead(msp2_sensors_buffer, 1024);
    msp2.begin(HW_SERIAL_INTERFACE_MSP2_SENSOR, HW_SERIAL_BAUD_RATE_MSP2_SENSOR);
}

void loop()
{
    static unsigned long t_enter[2], t_duration[2];

    if (msp2.read() == 0x0001)
    {
        if (msp2.is_update_rangefinder())
        {
            t_duration[0] = micros() - t_enter[0];
            t_enter[0] = micros();
        }
        if (msp2.is_update_optic_flow())
        {
            t_duration[1] = micros() - t_enter[1];
            t_enter[1] = micros();
        }

        // msp2_print_all_data(msp2);
        // Serial.print(t_duration[0]);
        // Serial.print(" ");
        // Serial.print(msp2.get_rangefinder().distance_mm);
        // Serial.print(" ");
        // Serial.print(t_duration[1]);
        // Serial.print(" ");
        // Serial.print(msp2.get_optic_flow().motionDX);
        // Serial.print(" ");
        // Serial.print(msp2.get_optic_flow().motionDY);
        // Serial.println();
        // Serial.flush();
    }
}
```

platformIO.ini

```clike
lib_deps =
    https://github.com/Intelligent-Embedded-Control-Laboratory/MSP2.git
```
