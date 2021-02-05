/*
  The Trekker's Expansion - OPERATING_SYS_PEGASUS.INO
  Main program.
  Written by L.Swarnajith January 11, 2020.
  Local time 1528, Alubomulla, Sri Lanka.
  ==Personal use only==
*/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <SoftwareSerial.h>

Adafruit_BMP280 bmp;
SoftwareSerial internalComm(2,3);

double localOffset = 1013.25;
double BMPtemp = 0.0;
double BMPprs = 0.0;
double BMPalt = 0.0;

void boot(){
  delay(500);
  Serial.begin(115200);
  internalComm.begin(115200);
  internalComm.print("<h1>Pegasus v1.0</h1> <h2>Written by L.Swarnajith Jan, 2020</h2> </body> </html>");
  Serial.println("Pegasus v1.0");
  Serial.println("Written by L.Swarnajith Jan, 2020");
  delay(7000);
  Serial.println("--------------------");
}

void setup(){
  boot();
  if(!bmp.begin()){
    internalComm.print("<h1>BMP280 Reading error !!");
    Serial.println("BMP280 Reading error !!");
    while(1);
  }
}

void loop(){
  BMPtemp = bmp.readTemperature();
  BMPprs = bmp.readPressure();
  BMPalt = bmp.readAltitude(localOffset);

  internalComm.print("<h1>Temperature</h1> <p> " + String(BMPtemp) + "*C </p> <h1>Atmospheric pressure</h1> <p>" + String(BMPprs) + "Pa </p> <h1>Aprox. Altitude</h1> <p>" + String(BMPalt) + "m </p> </body> </html>");

  Serial.print(F("Temperature = "));
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");

  Serial.print(F("Pressure = "));
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");

  Serial.print(F("Approx altitude = "));
  Serial.print(bmp.readAltitude(localOffset));
  Serial.println(" m");

  Serial.println();

  delay(1000);
}
