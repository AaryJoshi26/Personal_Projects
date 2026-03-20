#include <WebServer.h>
#include <WiFi.h>

const char* ssid = "Automation_server";
const char* password = "12345678";

#define relayPin 33

bool relayState = false;
String command = "OFF";

WebServer server(80);

// ===== WEBPAGE =====
void handleRoot()
{
    Serial.println("Client Connected");

    String page = "<!DOCTYPE html><html><head>";
    page += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    page += "<style>body{text-align:center;font-family:Arial;} button{padding:20px;font-size:20px;margin:10px;}</style>";
    page += "</head><body>";

    page += "<h1>ESP32 Light Control</h1>";

    page += "<a href='/on'><button style='background:green;color:white;'>ON</button></a>";
    page += "<a href='/off'><button style='background:red;color:white;'>OFF</button></a>";

    page += "<h2>Status: ";
    page += relayState ? "ON" : "OFF";
    page += "</h2>";

    page += "</body></html>";

    server.send(200, "text/html", page);
}

// ===== ON =====
void handleOn()
{
    relayState = true;
    digitalWrite(relayPin, HIGH); // change if relay is active LOW
    command = "ON";

    server.sendHeader("Location", "/");
    server.send(303);
}

// ===== OFF =====
void handleOff()
{
    relayState = false;
    digitalWrite(relayPin, LOW);
    command = "OFF";

    server.sendHeader("Location", "/");
    server.send(303);
}

// ===== CLIENT WILL READ THIS =====
void handleCommand()
{
    server.send(200, "text/plain", command);
}

void setup()
{
    Serial.begin(115200);

    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, LOW);

    WiFi.softAP(ssid, password);

    Serial.println("AP Started");
    Serial.print("IP: ");
    Serial.println(WiFi.softAPIP()); // usually 192.168.4.1

    server.on("/", handleRoot);
    server.on("/on", handleOn);
    server.on("/off", handleOff);
    server.on("/getCommand", handleCommand);

    server.begin();
}

void loop()
{
    server.handleClient();
}