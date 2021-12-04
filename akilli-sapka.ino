/*
 * Elbistan Proje IHL, 2021
 * TUBITAK 4006 Proje Ekibi
 * 
 * Ramazan Emre Osmanoglu, Duha Emre Coskun, Yunus Emre Cimentor, Recep Tanriverdi
 * 
 * This project is licensed under GPL 3.0, see LICENSE for more information.
 */

#include <Wire.h>
#include <Adafruit_Sensor.h> 
#include <Adafruit_ADXL345_U.h>

#define BUZZER_1 8
#define BUZZER_2 7
#define MEASURE_DELAY 1000
#define BEEP_DELAY 2000

const int X_LIMIT = 4;
const int Y_LIMIT = 4;

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

void setup(void) 
{
   pinMode(BUZZER_1, OUTPUT);
   pinMode(BUZZER_2, OUTPUT);
   
   Serial.begin(9600);  
   if(!accel.begin())
   {
      Serial.println("ADXL345 tanimlanamadi.");
      while(1);
   }
}

void beep_buzzers() {
  digitalWrite(BUZZER_1, HIGH);
  digitalWrite(BUZZER_2, HIGH);
  delay(BEEP_DELAY);
  digitalWrite(BUZZER_1, LOW);
  digitalWrite(BUZZER_2, LOW);
}


boolean is_tilting = false;

void loop(void) 
{
   sensors_event_t event; 
   accel.getEvent(&event);

   Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
   Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
   Serial.println("");

   if((event.acceleration.x >= X_LIMIT || event.acceleration.x <= -X_LIMIT) || (event.acceleration.y >= Y_LIMIT || event.acceleration.y <= -Y_LIMIT)) {
    if(is_tilting == true) {
      beep_buzzers();
      is_tilting = false;
    } else {
      Serial.println("TILT DETECTED, WAITING...");
      is_tilting = true; // Set tilting true
    }
   } else {
    is_tilting = false;
   }

   delay(MEASURE_DELAY);
}
