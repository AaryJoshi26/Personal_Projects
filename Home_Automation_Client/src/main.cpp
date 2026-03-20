#include <Arduino.h>

#include <HTTPClient.h>
#include <WiFi.h>

const char* ssid = "Automation_server";
const char* password = "12345678";

#define RELAY_PIN 2 // your relay pin

void setup()
{
    Serial.begin(115200);

    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW); // initial OFF

    WiFi.begin(ssid, password);

    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConnected!");
}

void loop()
{
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        http.begin("http://192.168.4.1/getCommand");
        int httpResponseCode = http.GET();

        if (httpResponseCode > 0) {
            String command = http.getString();
            Serial.println("Command: " + command);

            if (command == "ON") {
                digitalWrite(RELAY_PIN, HIGH); // change if relay is active LOW
            } else if (command == "OFF") {
                digitalWrite(RELAY_PIN, LOW);
            }
        } else {
            Serial.println("Error in HTTP request");
        }

        http.end();
    }

    delay(2000); // polling delay
}