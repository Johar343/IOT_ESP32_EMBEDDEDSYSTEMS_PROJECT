# 🌡️ ESP32 IoT Monitor & Control System

A simple ESP32-based IoT project that monitors **temperature using an LM35 sensor** and provides remote control of a **light and buzzer** through a **Blynk dashboard**.

The ESP32 connects to Wi-Fi and sends the temperature to Blynk while allowing the user to control the light and buzzer remotely.

---

## ✨ Features

- 🌡️ Real-time temperature monitoring using **LM35**
- 📱 Blynk dashboard for monitoring and control
- 💡 Remote light ON/OFF control
- 🔔 Remote buzzer ON/OFF control
- 📲 Blynk notifications for temperature alerts
- 📶 Wi-Fi connectivity through ESP32
- 🖥️ Temperature output through Serial Monitor
- 🔴 ESP32 status LED indication while connecting to Wi-Fi

---

## 🧰 Components Required

| Component | Quantity |
|---|---:|
| ESP32 Dev Module | 1 |
| LM35 Temperature Sensor | 1 |
| LED / Light | 1 |
| Buzzer | 1 |
| Jumper Wires | As required |
| Breadboard | 1 |

---

## 🔌 Connections

### 🌡️ LM35 → ESP32

The LM35 has **3 pins**:

| LM35 Pin | ESP32 |
|---|---|
| **VCC** | **3.3V** |
| **GND** | **GND** |
| **VOUT** | **GPIO 36 (VP)** |

> ⚠️ Check the orientation of your LM35 before connecting it. With the flat/front side facing you, the usual pin order is **VCC → VOUT → GND**. Check your specific LM35 module/datasheet if yours is packaged differently.

💡 Light / LED → ESP32
Light/LED Connection	ESP32
Positive (+)	GPIO 13
Negative (-)	GND

The light is controlled from Blynk using Virtual Pin V1.

🔔 Buzzer → ESP32
Buzzer Connection	ESP32
Positive (+)	GPIO 17
Negative (-)	GND

The buzzer is controlled from Blynk using Virtual Pin V2.

🔴 ESP32 Status LED

The program uses:

pinMode(2, OUTPUT);

GPIO 2 is used as a Wi-Fi connection status indicator.

While the ESP32 is trying to connect to Wi-Fi:

LED → ON/OFF → ON/OFF → ON/OFF

After Wi-Fi connection:

LED → ON
📌 Pin Mapping
Function	ESP32 Pin	Direction
LM35 Temperature	GPIO 36	INPUT
Light / LED	GPIO 13	OUTPUT
Buzzer	GPIO 17	OUTPUT
Wi-Fi Status LED	GPIO 2	OUTPUT
📱 Blynk Dashboard

The project uses Blynk IoT for remote monitoring and control.

Virtual Pins
Virtual Pin	Purpose	Direction
V0	Temperature	ESP32 → Blynk
V1	Light Control	Blynk → ESP32
V2	Buzzer Control	Blynk → ESP32
Dashboard

The Blynk dashboard can contain:

🌡️ Temperature display connected to V0
💡 Light switch connected to V1
🔔 Buzzer switch connected to V2

Example:

┌─────────────────────────────┐
│       ESP32 IoT Monitor     │
├─────────────────────────────┤
│                             │
│ 🌡️ Temperature: 28.5 °C     │
│                             │
│ 💡 Light       [ ON / OFF ] │
│                             │
│ 🔔 Buzzer      [ ON / OFF ] │
│                             │
└─────────────────────────────┘
📲 Notifications

Temperature alerts can be configured through Blynk Events.

For example:

Temperature > 35°C
        ↓
Blynk Event Triggered
        ↓
📲 Notification sent

The current Arduino code sends the temperature to V0. The actual notification threshold/event is configured inside the Blynk dashboard/console.

Example notification:

⚠️ High Temperature Alert!
Temperature has exceeded the safe threshold.
🔄 How the System Works
             🌡️ LM35
                │
                │ Temperature
                ▼
          ┌─────────────┐
          │    ESP32    │
          └──────┬──────┘
                 │
        ┌────────┴─────────┐
        │                  │
        ▼                  ▼
     📶 Wi-Fi          💡 Light
        │
        ▼
     ☁️ Blynk
        │
   ┌────┴─────┐
   │          │
   ▼          ▼
 💡 Light   🔔 Buzzer
 Control    Control

Temperature flow:

LM35
  ↓
ESP32 GPIO 36
  ↓
Temperature calculated
  ↓
Blynk V0
  ↓
📱 Dashboard
  ↓
📲 Alert if configured threshold is exceeded
📚 Libraries Used
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP_LM35.h>
Libraries
WiFi.h → Connects ESP32 to Wi-Fi
BlynkSimpleEsp32.h → Connects ESP32 with Blynk
ESP_LM35.h → Reads temperature from the LM35 sensor
⚙️ Blynk Configuration

Create a Blynk template and configure:

Template
Template Name: ESP32IOT
Datastreams
V0 → Temperature
V1 → Light
V2 → Buzzer
Dashboard Widgets
V0 → Temperature Display / Gauge
V1 → Switch
V2 → Switch

For notifications, create a Blynk Event with the required temperature condition and enable push notifications.

💻 Arduino IDE Setup
1. Install ESP32 Board Support

In Arduino IDE:

File
 → Preferences
 → Additional Boards Manager URLs

Add the ESP32 board package URL if it is not already installed.

Then:

Tools
 → Board
 → Boards Manager
 → Search: ESP32
 → Install

Select:

ESP32 Dev Module
2. Select the ESP32 Port

Connect the ESP32 through USB and select:

Tools
 → Port
 → COM5

3. Install Required Libraries

ESP_LM35
WiFi (included with the ESP32 board package)
BlynkSimpleEsp32 (Blynk library)

🔐 Wi-Fi & Blynk Credentials

The code requires:

#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

Do not upload your real Wi-Fi password or Blynk authentication token to GitHub.

For a public repository, replace them with placeholders or store them separately in a file such as:

secrets.h

and add that file to .gitignore.

If a real Blynk token/password has already been exposed publicly, rotate the credentials before publishing the project.

🧠 Code Logic
Temperature

The LM35 is connected to GPIO 36:

ESP_LM35 temp(36);

The temperature is read using:

t = temp.tempC();

Then it is printed to the Serial Monitor:

Serial.print("Temperature-C:");
Serial.println(t);

and sent to Blynk:

Blynk.virtualWrite(V0, t);
💡 Light Control

Blynk V1 controls GPIO 13:

BLYNK_WRITE(V1)
{
  int value = param.asInt();
  digitalWrite(13, value);
}

So:

Blynk V1 ON
     ↓
GPIO 13 HIGH
     ↓
💡 Light ON
🔔 Buzzer Control

Blynk V2 controls GPIO 17:

BLYNK_WRITE(V2)
{
  int value = param.asInt();
  digitalWrite(17, value);
}

So:

Blynk V2 ON
     ↓
GPIO 17 HIGH
     ↓
🔔 Buzzer ON
▶️ Running the Project
Connect the LM35 to the ESP32.
Connect the light/LED to GPIO 13.
Connect the buzzer to GPIO 17.
Connect the ESP32 to your computer.
Select ESP32 Dev Module in Arduino IDE.
Select the correct COM port.
Enter your Wi-Fi and Blynk credentials.
Upload the code.
Open Serial Monitor at 9600 baud.
Open the Blynk dashboard.
Monitor the temperature using V0.
Control the light using V1.
Control the buzzer using V2.
Configure Blynk Events if temperature notifications are required.
📁 Project Structure
ESPIOT_day2/
│
├── ESPIOT_day2.ino
├── README.md
└── .gitignore
🚀 Future Improvements
Add automatic temperature-based buzzer alerts
Add automatic light control
Add temperature history graphs
Add more sensors
Add better notification conditions
Replace blocking delay() calls with BlynkTimer
Store Wi-Fi and Blynk credentials securely
🛠️ Technologies Used
ESP32
LM35
Arduino IDE
Blynk IoT
Wi-Fi
📄 License

This project is created for educational and IoT experimentation purposes.
