# MSP2 Data Format

這份文件紀錄 MSP2 協議的開發筆記。

## MSP2 資料結構

- 開頭會有 4 個 bytes，在我們目前的應用中是固定的
- 接下來 2 個 bytes 是 data 的 ID
- 再接下來 2 個 bytes 是 payload size，也就是資料的位元長度
- 接完 payload size 長度的資料，接下來是 checksum，目前還沒讀到要怎麼解。

## 解碼範例：測距儀 (Rangefinder)

```cpp
#define MSP2_SENSOR_RANGEFINDER 0x1F01 // 測距儀的 ID

// 開頭的四個 bytes
0x24 // start
0x58 // start
0x3C // type
0x00 // flag

// 接下來兩個 bytes 是資料ID，要解成 uint16_t: 0x1F01 (記憶體順序先的在低位元)
0x01
0x1F // function

// Payload size，要解成 uint16_t: 0x0005
0x05
0x00 // payload size

// 從上面可以知道是 5 bytes，這 5 個 bytes 會對應到這 msp rangefinder 的固定資料結構，如下一個程式方框所示。所以第 1 個 byte 是對應到 quality，後面 4 個 bytes 對應到的是 int32_t 的資料：
/*
{
    uint8_t quality = 0xFF
    int32_t distance_mm = 0x00000018
}
*/
0xFF
0x18
0x00
0x00
0x00 // data bytes

0x69 // checksum
```

```cpp
/* MSP2 Sensor Rangefinder 資料結構 */
typedef struct msp_sensor_rangefinder_t
{
    uint8_t quality; // [0 ~ 255]
    int32_t distance_mm; // Negative range for out of rande
} msp_sensor_rangefinder_t; // total 5 bytes
```

## 解碼範例：光流 (Optic Flow)

```cpp
#define MSP2_SENSOR_OPTIC_FLOW 0x1F02 // 光流的 ID

// 開頭的四個 bytes
0x24 // start
0x58 // start
0x3C // type
0x00 // flag

// 接下來兩個 bytes 是資料ID，要解成 uint16_t: 0x1F02 (記憶體順序先的在低位元)
0x02
0x1F // function

// Payload size，要解成 uint16_t: 0x0009
0x09
0x00 // payload size


// 從上面可以知道是 9 bytes，這 9 個 bytes 會對應到這 msp optical flow 的固定資料結構，如下一個程式方框所示。所以第 1 個 byte 是對應到 quality，後面 8 個 bytes 對應到的是 int32_t[2] 的資料：
/*
{
    uint8_t quality = 0x68
    int32_t motionX = 0xFFFFFFFF
    int32_t motionY = 0x00000000
}
*/
0x68
0xFF
0xFF
0xFF
0xFF
0x00
0x00
0x00
0x00 // data

0xE9 // checksum
```

```cpp
/* MSP2 Sensor 光流計的資料結構 */
typedef struct msp_sensor_op_flow_t
{
    uint8_t quality; // [0 ~255]
    int32_t motionX;
    int32_t motionY;
} msp_sensor_op_flow_t; // total 9 bytes
```

## 參考資料

- [对黑羊、Elrs 等使用的 crsf 协议的简单解析](https://blog.csdn.net/m0_63043961/article/details/128309223)
