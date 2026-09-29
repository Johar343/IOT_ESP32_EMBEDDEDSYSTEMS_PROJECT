#define BLYNK_TEMPLATE_ID "TMPL3TfPPpo5U"
#define BLYNK_TEMPLATE_NAME "ESP32IOT"
#define BLYNK_AUTH_TOKEN "vBKcjkhXOIMqxOQKYn9i74fzqc3xpTiO"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP_LM35.h>
ESP_LM35 temp(36);
float t;
char ssid[] = "SKULLFACE";
char pass[] = "123456789345678";

//light
BLYNK_WRITE(V1)
{
  int value = param.asInt();
  digitalWrite(13, value);
}

//buzzer
BLYNK_WRITE(V2)
{
  int value = param.asInt();
  digitalWrite(17, value);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(17, OUTPUT);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
    delay(500);

  }
    digitalWrite(2, HIGH);
    Serial.println("Connecting to the WiFi Network...");
    Serial.println(ssid);
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  t= temp.tempC();
  Serial.print("Temperature-C:");
  Serial.println(t);
  Blynk.virtualWrite(V0, t);
  delay(1000);
}
