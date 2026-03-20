#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
//#include "SparkFunCCS811.h"

//#define CCS811_ADDR 0x5A // Alternate I2C Address (replace if different)
//#define HIGH_RISK_FACTOR 1500 
//#define MEDIUM_RISK_FACTOR 800 
//#define LOW_RISK_FACTOR 400 

//const int relay = D4;
//int thresholdValue = 0;
const char* ssid = "CARBOFREE";
const char* password = "";

String page = "";
//String co2Data = "UNKNOWN"; // Initialize CO2 data as unknown

//CCS811 mySensor(CCS811_ADDR);
WebServer server(80); // Instantiate server at port 80 (http port)

void setup() {
//  pinMode(relay , OUTPUT);

  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  IPAddress apIP = WiFi.softAPIP(); // Get IP address of the AP
  delay(1000);
  Serial.print("AP IP address: ");
  Serial.println(apIP);

  // Initialize I2C communication (assuming SCL on D1 and SDA on D2)
 // Wire.begin(D6, D7);

//  if (!mySensor.begin()) { // Simplified check for sensor errors
//    Serial.println("CCS811 error. Please check wiring.");
//    while (1);
//  }

  server.on("/", []() {
    // Display HTML page with CO2 data
    page = "<h1 style='text-align: center;'>GENERAL PROFILE </h1>";
//    page += "<div id='data-container' style='text-align: center'>";
//    page += "<h1>" + co2Data + "</h1>";
//     
//     if (atoi(co2Data.c_str()) >= LOW_RISK_FACTOR && atoi(co2Data.c_str()) < MEDIUM_RISK_FACTOR) { // Use atoi for conversion
//      page += "<p style='color: green;'><b>CO2 Level UNDER CONTROL! GREAT JOB </b></p>";
//     }
//
//    if (atoi(co2Data.c_str()) >= MEDIUM_RISK_FACTOR && atoi(co2Data.c_str()) < HIGH_RISK_FACTOR ) { // Use atoi for conversion
//      page += "<p style='color: yellow;'><b>CO2 Level INCREASING Please CONTROL Emissions</b></p>";
//    }
//    if (atoi(co2Data.c_str()) >= HIGH_RISK_FACTOR ) { // Use atoi for conversion
//      page += "<p style='color: red;'><b>CO2 Level High! Please Check Emissions</b></p>";
//      thresholdValue++ ;
//      page += "<div id='data-container' 'text-align: center'><h2> Threshold Count : " + String(thresholdValue) + "</h2></div>";
//
//    }
//
//    else {
//      thresholdValue = 0;
//    }
//
//    if(thresholdValue >= 4 && thresholdValue < 9){
//
//      page += "<p style='color: red;'><b> Warninig :- Fine Of 3000 rs. is charged.</b></p>";
//
//    }
//
//    if(thresholdValue >= 9 && thresholdValue < 12){
//
//      page += "<p style='color: red;'><b> Warninig :- Fine Of 6000 rs. is charged.</b></p>";
//
//    }
//
//    if(thresholdValue >= 12 && thresholdValue < 15){
//
//      page += "<p style='color: red;'><b> Warninig :- Fine Of 10000 rs. is charged.</b></p>";
//
//    }
//
//
//
//    if (thresholdValue >= 15 ){
//
//      digitalWrite(relay,HIGH);
//      page += "<p style='color: red;'><b>CO2 Level High! Shuting Down FUEL Supply</b></p>";
//
//    }
//
//    else{
//      digitalWrite(relay,LOW);
//    }
//
//    page += "</div>";
//
//    page += "<script>setTimeout(function() { location.reload(); }, 1500);</script>"; // Reload page every 1.5 seconds
//
//    server.send(200, "text/html", page);
  });

  server.begin();
  Serial.println("Web server started!");
}

void loop() {
  server.handleClient();

  // Read CO2 data periodically (modify delay as needed)
//  if (millis() % 1000 == 0) { // Read every 5 seconds
//    if (mySensor.dataAvailable()) {
//      mySensor.readAlgorithmResults();
//      co2Data = String(mySensor.getCO2());
//      Serial.println("CO2: " + co2Data);
//    }
//  }
}
