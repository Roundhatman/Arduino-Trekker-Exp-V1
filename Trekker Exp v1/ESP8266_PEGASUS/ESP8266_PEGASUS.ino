/*
  The Trekker's Expansion - ESP8266_PEGASUS.INO
  Program for transfer data between ATmega328p and web server.
  Written by L.Swarnajith January 11, 2020.
  Local time 1503, Alubomulla, Sri Lanka.
  ==Personal use only==
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

#define APSSID "SPETSGRUPPA_PEGASUS"
#define APPSK  "AlphaOne"

String msg = "";
String html = "<!DOCTYPE html> <html> <head> <meta http-equiv='refresh' content='5'>  <title>Trekker Expansion - SWARNAJITH</title>  <style> body { background-color: #535A74; color: white; } </style> </head> <body> ";

ESP8266WebServer server(80);
SoftwareSerial internalComm(3,1);

void hData(){
  server.send(200, "text/html", html + msg);
}

void setup(){
  delay(1000);
  WiFi.softAP(APSSID, APPSK);
  IPAddress myIP = WiFi.softAPIP();
  server.on("/", hData);
  server.begin();
  internalComm.begin(115200);
}

void loop(){
  msg = internalComm.readString();
  server.handleClient();
}
