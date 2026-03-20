//#include <WiFi.h>
//#include <WebServer.h>
//
//const char* ssid = "ESP32C6_AP";
//const char* password = "";  // leave empty for open network
//
//IPAddress local_IP(192, 168, 1, 1);
//IPAddress gateway(192, 168, 1, 1);
//IPAddress subnet(255, 255, 255, 0);
//
//WebServer server(80);
//bool ledState = false;
//
//void handleOn() {
//  ledState = true;
//  digitalWrite(LED_BUILTIN, HIGH);
//  Serial.println("LED is now: ON");
//  server.send(200, "text/plain", "ON");
//}
//
//void handleOff() {
//  ledState = false;
//  digitalWrite(LED_BUILTIN, LOW);
//  Serial.println("LED is now: OFF");
//  server.send(200, "text/plain", "OFF");
//}
//
//void handleState() {
//  server.send(200, "text/plain", ledState ? "ON" : "OFF");
//}
//
////void handleRoot() {
////  String html = "<html><body>";
////  html += "<h1>ESP32-C6 LED Control</h1>";
////  html += "<p>LED Status: " + String(ledState ? "ON" : "OFF") + "</p>";
////  html += "<button onclick=\"fetch('/on').then(()=>location.reload())\">ON</button>";
////  html += "<button onclick=\"fetch('/off').then(()=>location.reload())\">OFF</button>";
////  html += "</body></html>";
////  server.send(200, "text/html", html);
////}
//
//void setup() {
//  Serial.begin(115200);
//  
//  pinMode(LED_BUILTIN, OUTPUT);
//  digitalWrite(LED_BUILTIN, LOW);
//
//  WiFi.softAPConfig(local_IP, gateway, subnet);
//  WiFi.softAP(ssid, password);
//
//  Serial.println("ESP32-C6 Access Point started");
//  Serial.print("AP IP address: ");
//  Serial.println(WiFi.softAPIP());
//
//  
//  //server.on("/", HTTP_GET, handleRoot);
//  server.on("/on", HTTP_GET, handleOn);
//  server.on("/off", HTTP_GET, handleOff);
//  server.on("/state", HTTP_GET, handleState);
//
//  server.begin();
//  Serial.println("HTTP server started");
//}
//
//void loop() {
//  server.handleClient();
//}


#include <WiFi.h>
#include <WebServer.h>

#define LED_PIN LED_BUILTIN

// WiFi AP settings
const char* ssid = "ESP32C6_AP";
const char* password = "";  // leave empty for open network

IPAddress local_IP(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80);
bool ledState = false;

// Toggle LED state
void handleToggle() {
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState ? HIGH : LOW);
  Serial.print("LED is now: ");
  Serial.println(ledState ? "ON" : "OFF");
  server.send(200, "text/plain", ledState ? "ON" : "OFF");
}

// Return LED state
void handleState() {
  server.send(200, "text/plain", ledState ? "ON" : "OFF");
}

// Optional: simple web page for browser control
//void handleRoot() {
//  String html = "<html><body>";
//  html += "<h1>ESP32-C6 LED Control</h1>";
//  html += "<p>LED Status: " + String(ledState ? "ON" : "OFF") + "</p>";
//  html += "<button onclick=\"fetch('/toggle').then(()=>location.reload())\">Toggle LED</button>";
//  html += "</body></html>";
//  server.send(200, "text/html", html);
//}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Configure AP
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(ssid, password);

  Serial.println("ESP32-C6 Access Point started");
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  // Define server routes
  //server.on("/", HTTP_GET, handleRoot);
  server.on("/toggle", HTTP_GET, handleToggle);
  server.on("/toggle", HTTP_POST, handleToggle);
  server.on("/state", HTTP_GET, handleState);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
