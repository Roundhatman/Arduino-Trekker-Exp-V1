/*
  Promētheus v1.0 - OPERATING_SYS_PEGASUS.INO
  Main program.
  Written by L.Swarnajith January 11, 2020.
  Local time 1528, Alubomulla, Sri Lanka.

  Upgraded to v1.1
  On January 24, 2020/ Local time 2208/ Alubomulla, Sri Lanka.
  Added 84x48 B&W PCD8544 display
  
  ==Personal use only==
*/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_PCD8544.h>

Adafruit_BMP280 bmp;
Adafruit_PCD8544 display = Adafruit_PCD8544(2,10,11,12,13);

double localOffset = 1014.75, BMPtemp = 0.0, BMPprs = 0.0, BMPalt = 0.0;


void boot(){
  delay(500);
  Wire.begin();
  display.begin();
  display.setContrast(57);
  display.clearDisplay();
  display.setTextSize(0.5);
  display.setTextColor(BLACK);
  display.setRotation(90);
  display.setCursor(0,0);
  Serial.begin(115200);
  
  Serial.println("Promētheus v1.1");
  Serial.println("Written by L.Swarnajith Jan, 2020");
  display.println("Prometheus");
  display.println("v1.1");
  display.println("--------------");
  display.println("Written by");
  display.println("L.Swarnajith");
  display.println("Jan, 2020");
  display.display();
  delay(7000);
  Serial.println("--------------------");

  locI2C();
  pinMode(9,INPUT);
}

void locI2C()
{
  byte error, address;
  int nDevices;

  display.clearDisplay();
  Serial.println("Scanning for I2C devices...");
  display.println("Scanning for");
  display.println("I2C devices...");
  display.display();
  delay(1500);

  display.clearDisplay();
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      display.print("I2C found at: 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
      display.print("0");
      display.print(address,HEX);
      display.println(" !");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      display.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
      display.print("0");
      display.println(address,HEX);
    }    
  }
  if (nDevices == 0){
    Serial.println("No I2C devices found\n");
    display.println("No I2C devices found\n");
  }
  else
    Serial.println("done\n");
    display.println("done\n");

  display.display();
  delay(2000);           // wait 2 seconds for next scan
}

void setup(){
  boot();
  if(!bmp.begin()){
    Serial.println("BMP280 not found or device error !!");
    Serial.println("Main programe function 'GetAltitude()' fail !!");
    while(1);
  }
}

void GetAltitude(){

  display.clearDisplay();

  BMPtemp = bmp.readTemperature();
  BMPprs = bmp.readPressure();
  BMPalt = bmp.readAltitude(localOffset);

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
  
  display.print(F("T="));
  display.print(bmp.readTemperature());
  display.println(" *C");

  display.print(F("P="));
  display.print(bmp.readPressure());
  display.println(" Pa");
  //display.println();

  display.println("--------------");
  
  display.println(F("Apprx.Altitude"));
  display.print("= ");
  display.print(bmp.readAltitude(localOffset));
  display.print(" m");

  display.display();

  delay(500);
}

void loop(){
  GetAltitude();
}
