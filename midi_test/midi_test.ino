#include <Arduino.h>

// LEDs
#define PCA_ADDR 0x0

#include "PinMap.h"
#include "RotaryEncoder.h"
#include "SevenSegment.h"

#include "PerformState.h"
#include "EditorState.h"

RotaryEncoder encoder;
SevenSegment display;

DebouncedButton *commonBtn;

PerformState performState;
EditState editState;

unsigned long commonDownTime = 0;

// DebouncedButton b0,b1,b2,b3,b4,b5,enc_sw;

void setup()
{
  commonBtn = new DebouncedButton();
  commonBtn->begin(100, ENC_SW);
  performState.setup(commonBtn);
  editState.setup(commonBtn);
}

void loop()
{

  if (commonDownTime)

    commonDownTime += millis();
}

// Arduino-Pin verbunden mit SH_CP des 74HC595
/*int shiftPin = 13;
// Arduino-Pin verbunden mit ST_CP des 74HC595
int storePin = 10;
// Arduino-Pin verbunden mit DS des 74HC595
int dataPin = 11;
 
// Dieses Muster soll ausgegeben werden
int muster[8] = {1,1,1,1,1,1,1,1};
 
void setup() {
 
 // Pins 8,9,10 auf Ausgabe
 pinMode(storePin, OUTPUT);
 pinMode(shiftPin, OUTPUT);
 pinMode(dataPin, OUTPUT);
 pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(6,OUTPUT);
    pinMode(7,OUTPUT);
    
    digitalWrite(9,LOW);
 digitalWrite(8,LOW);
    digitalWrite(7,LOW);
  digitalWrite(6,LOW);

    // storePin sicherheitshalber auf LOW
 digitalWrite(storePin, LOW); 
 for (int i=0; i<8; i++) {
 // Zuerst immer alle 3 Pins auf LOW
 // Aktion passiert bei Wechsel von LOW auf HIGH
 digitalWrite(shiftPin, LOW);
 // Jetzt den Wert der aktuellen Stelle ans Datenpin DS anlegen 
 digitalWrite(dataPin, muster[i]);
 // Dann ShiftPin SHCP von LOW auf HIGH, damit wird der Wert
 // am Datenpin ins Register geschoben. 
 digitalWrite(shiftPin, HIGH);
 }
 // Wenn alle 8 Stellen im Register sind, jetzt das StorePin STCP
 // von LOW auf HIGH, damit wird Registerinhalt an Ausgabepins
 // kopiert und der Zustand an den LEDs sichtbar
 
 digitalWrite(storePin, HIGH);

}
 
void loop () {


}*/

/* LED test program 
  Alan Marchiori
  Bucknell University
  tested on Rev1.1 HydroSense Wireless Link board
  with PCA9634 on i2c address 0x20
  using a TeensyLC MCU on Arduino 1.0.6 (with Teensyduino installed)
  The teensy uses the library i2c_t3 for i2c communication
  instead of the usual "Wire" library. If using a standard Arduino, you will have
  to manually change the inculdes to use Wire. The libraries should be mostly
  compatible. (some calls are "enhanced" in the i2c_t3 library, these will have
  to be modified appropriately as well).
*/
/*
// set this to the hardware serial port you wish to use
//#define HWSERIAL Serial1

#include "HydroSense_pca9634.h"
#include <Wire.h>
HydroSense_pca9634 leds( 0x0 );

void setup() {
  Serial.begin( 9600 );
  Wire.begin();//begin( I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_1200 );
  leds.begin( );
}

void loop1(){
 leds.set_led ( LED_ERROR, LED_RED );
 delay(1500);  
 
 leds.set_led( LED_SIGNAL, LED_RED );
 delay(1500);  
 leds.set_led( LED_SIGNAL, LED_YELLOW );
 delay(1500);  
 leds.set_led( LED_SIGNAL, LED_GREEN );
 leds.set_led ( LED_ERROR, LED_OFF );
 
 leds.set_led( LED_GPS, LED_RED );
 delay(1500);
 leds.set_led( LED_GPS, LED_YELLOW );
 delay(1500); 
 leds.set_led( LED_GPS, LED_GREEN );
 delay(1500); 
 leds.set_led ( LED_GPS, LED_OFF );
 leds.set_led ( LED_SIGNAL, LED_OFF );
}

int16_t v = 0;
int8_t inc = 1;

void loop() {
  
  int i, r;
 // Serial.print("Set brightness: ");
  //Serial.print(v);

  for (i=0; i<8; i++){
    r = leds.set_brightness(i, v);
 //   Serial.print(", ");
//    Serial.print(i);
//    Serial.print("=");
//    Serial.print(r);
  }
  
  
//  Serial.println();
  v = v + inc;
 
  if ( inc > 0 && v >= 255){
    inc = -1;    
  } else if (inc < 0 && v <= 0){
    inc = 1;
  }    

  delay (1);
 //delayMicroseconds(100);
}*/

/*
void setup() {
  // Set MIDI baud rate:
  Serial.begin(31250);
}


void loop() {

 // Serial.write(0xB1);
//  Serial.write(0);
 
 // Serial.write(0x32);
 //   Serial.write(0xC1);
 // Serial.write(0);
  for (int slot = 6; slot <= 10; slot ++) {

  Serial.write(0xC1);
  Serial.write(slot-1);
 // Serial.write(0);
  delay(2000);
  }

}*/

/*

#include "HydroSense_pca9634.h"
#include <Wire.h>
HydroSense_pca9634 leds( PCA_ADDR );

int messungPin1 = LOW;
int messungPin1Alt = LOW;
int encoderWert = 50;

 void setup() { 
 pinMode(ENC_A, INPUT_PULLUP);
 pinMode(ENC_B, INPUT_PULLUP);
   Wire.begin();
  Serial.begin(9600);
      leds.begin( );
 } 

 void loop() {
   messungPin1 = digitalRead(ENC_A);
   if ((messungPin1 == HIGH) && (messungPin1Alt == LOW)) {
     if (digitalRead(ENC_B) == HIGH) {
      encoderWert++;
     } else {
      encoderWert--;
     }
int r;
     for (int i=0; i<8; i++){
   r = leds.set_brightness(i,encoderWert);
   Serial.print(r);
  }

  

Serial.println(encoderWert);
   }
   messungPin1Alt = messungPin1;
 }*/
