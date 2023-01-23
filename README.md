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
    msp2.begin(HW_SERIAL_INTERFACE_MSP2_SENSOR, HW_SERIAL_BAUD_RATE_MSP2_SENSOR);
}

void loop()
{
    if (msp2.read() == 0x0001)
    {
        print_msp2_data(msp2);
    }
}
```

platformIO.ini

```clike
lib_deps =
    https://github.com/Intelligent-Embedded-Control-Laboratory/MSP2.git
```
