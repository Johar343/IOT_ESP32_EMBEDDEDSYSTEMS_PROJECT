# ESP32 IoT Monitor & Control System

A simple ESP32-based IoT project that monitors **temperature using an LM35 sensor** and provides remote control of a **light and buzzer** through a **Blynk dashboard**.

The ESP32 connects to Wi-Fi, sends live temperature data to Blynk, and receives commands from the dashboard to control the connected devices.

---

## Features

- Real-time temperature monitoring using **LM35**
- Blynk dashboard for monitoring and control
- Remote **Light ON/OFF** control
- Remote **Buzzer ON/OFF** control
- Temperature-based **Blynk notifications**
- Wi-Fi connectivity
- Temperature display through **Serial Monitor**
- Wi-Fi connection status using ESP32 LED

---

## Components Required

| Component | Quantity |
|---|---:|
| ESP32 Dev Module | 1 |
| LM35 Temperature Sensor | 1 |
| LED / Light | 1 |
| Buzzer | 1 |
| Breadboard | 1 |
| Jumper Wires | As required |

---

## Connections

### LM35 → ESP32

| LM35 Pin | ESP32 |
|---|---|
| VCC | 3.3V |
| VOUT | GPIO 36 (VP) |
| GND | GND |

> Check the pin orientation of your LM35 before connecting it.

### Light / LED → ESP32

| Light / LED | ESP32 |
|---|---|
| Positive (+) | GPIO 13 |
| Negative (-) | GND |

The light is controlled using **Blynk Virtual Pin V1**.

### Buzzer → ESP32

| Buzzer | ESP32 |
|---|---|
| Positive (+) | GPIO 17 |
| Negative (-) | GND |

The buzzer is controlled using **Blynk Virtual Pin V2**.

### Pin Summary

| Function | ESP32 Pin |
|---|---|
| LM35 Temperature | GPIO 36 |
| Light / LED | GPIO 13 |
| Buzzer | GPIO 17 |
| Wi-Fi Status LED | GPIO 2 |

---

## Blynk Dashboard

The project uses **Blynk IoT** for remote monitoring and device control.

### Virtual Pins

| Virtual Pin | Purpose | Direction |
|---|---|---|
| V0 | Temperature | ESP32 → Blynk |
| V1 | Light Control | Blynk → ESP32 |
| V2 | Buzzer Control | Blynk → ESP32 |

### Dashboard Widgets

| Widget | Virtual Pin | Purpose |
|---|---|---|
| Temperature Display / Gauge | V0 | Display temperature |
| Switch | V1 | Control light |
| Switch | V2 | Control buzzer |

---

## Notifications

Temperature alerts can be configured using **Blynk Events**.

For example:

Temperature > 35°C
→ Blynk Event
→ Push Notification

The Arduino code continuously sends the temperature to V0. The temperature threshold and notification settings are configured separately in the Blynk Console.

## Libraries Used

### WiFi.h	Connects ESP32 to Wi-Fi
### BlynkSimpleEsp32.h	Connects ESP32 to Blynk
### ESP_LM35.h	Reads temperature from LM35
Include in Code
```cpp
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP_LM35.h>
Blynk Configuration
```
### 1. Create Template
Create a Blynk template with:
Template Name: ESP32IOT

### 2. Create Datastreams
Datastream	Data
V0	Temperature
V1	Light
V2	Buzzer

### 3. Add Dashboard Widgets
V0 → Temperature Display / Gauge
V1 → Switch
V2 → Switch

### 4. Configure Notifications
Create a Blynk Event for the required temperature condition and enable push notifications.

## Arduino IDE Setup
### 1. Install ESP32 Board Support
Add the ESP32 board package URL under:
Additional Boards Manager URLs & install the ESP32 board package.
Select ESP32 Dev Module

### 2. Select ESP32 Port
Connect the ESP32 through USB and select COM5 

### 3. Install Required Libraries
ESP_LM35
Blynk
WiFi.h is included with the ESP32 board package.

## Wi-Fi & Blynk Credentials
Add your credentials in the Arduino code:

```cpp
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";
```

Code Logic
Temperature Monitoring
The LM35 is connected to GPIO 36:
```cpp
ESP_LM35 temp(36);
```
The temperature is read using:
```cpp
t = temp.tempC();
```
It is displayed on the Serial Monitor:
```cpp
Serial.print("Temperature-C:");
Serial.println(t);
```
and sent to Blynk through V0:
```cpp
Blynk.virtualWrite(V0, t);
```
### Light Control
Blynk V1 controls GPIO 13:
```cpp
BLYNK_WRITE(V1)
{
  int value = param.asInt();
  digitalWrite(13, value);
}
```
Blynk V1	GPIO 13	Light
0	LOW	OFF
1	HIGH	ON

### Buzzer Control
Blynk V2 controls GPIO 17:
```cpp
BLYNK_WRITE(V2)
{
  int value = param.asInt();
  digitalWrite(17, value);
}
```
Blynk V2	GPIO 17	Buzzer
0	LOW	OFF
1	HIGH	ON

### Wi-Fi Status LED
GPIO 2 is used as the Wi-Fi connection status indicator:
```cpp
pinMode(2, OUTPUT);
```
While connecting to Wi-Fi, the LED continuously turns ON and OFF. After a successful connection, it remains ON.

## Running the Project
1. Connect the LM35 to the ESP32.
2. Connect the Light/LED to GPIO 13.
3. Connect the Buzzer to GPIO 17.
4. Connect the ESP32 to your computer.
5. Select ESP32 Dev Module in Arduino IDE.
6. Select the correct COM port.
7. Add your Wi-Fi and Blynk credentials.
8. Upload the code.
9. Open Serial Monitor at 9600 baud.
10. Open the Blynk dashboard.
11. Monitor temperature through V0.
12. Control the light through V1.
13. Control the buzzer through V2.
14. Configure Blynk Events for temperature notifications.

## Project Structure
ESPIOT_day2/
│
├── ESPIOT_day2.ino
├── README.md
└── .gitignore

## Future Improvements
1. Automatic temperature-based buzzer alerts
2. Automatic light control based on temperature
3. Temperature history and graphs

## Additional sensors
1. More advanced notification conditions
2. Replace delay() with BlynkTimer
3. Secure credential management

## Technologies Used
Technology	Purpose
ESP32	Main microcontroller
LM35	Temperature sensing
Arduino IDE	Development environment
Blynk IoT	Dashboard and remote control
Wi-Fi	Wireless communication

# License
This project is created for educational and IoT experimentation purposes.
