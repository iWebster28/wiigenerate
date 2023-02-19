#include <dummy.h>
#include "BluetoothSerial.h"
#include <Arduino.h>
#include <DFRobot_Heartrate.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define LED 25
#define sensorPin 32

//https://techtutorialsx.com/2021/10/06/esp32-heart-rate-sensor/
//https://randomnerdtutorials.com/installing-esp32-arduino-ide-2-0/
//https://forum.arduino.cc/t/using-millis-for-timing-a-beginners-guide/483573/4

BluetoothSerial SerialBT;
DFRobot_Heartrate heartrate(DIGITAL_MODE); 
unsigned long hrMillis;
unsigned long ledMillis;
unsigned long currentMillis;
int rateValue;
int oldRateValue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(LED, OUTPUT);
  hrMillis = millis();
  ledMillis = millis();
  oldRateValue = 0;
}

void loop() {
  currentMillis = millis();
  // put your main code here, to run repeatedly:
  /*
  heartrate.getValue(sensorPin);
  rateValue = heartrate.getRate();
     
  if(rateValue>0){
    Serial.println(rateValue);
  }
   
  //delay(20);
  
  
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  */
  hrMeasure();
  //delay(20);
  /*
  if(rateValue>0){
    digitalWrite(LED, HIGH);
    //Serial.println("LED is on");
    delay(30000/rateValue);
    digitalWrite(LED, LOW);
    //Serial.println("LED is off");
    delay(30000/rateValue);
  }
  else{
    digitalWrite(LED, HIGH);
    delay(20);
  }
  */
  ledBlink();
  
}

void ledBlink(){
  if(oldRateValue <= 0 || oldRateValue >= 220){
    digitalWrite(LED, LOW);
    //ledMillis = currentMillis;
  }
  else if(currentMillis - ledMillis >= 30000/oldRateValue && oldRateValue < 220){
    digitalWrite(LED, !digitalRead(LED));
    ledMillis = currentMillis;
  }
}

void hrMeasure(){
  if(currentMillis - hrMillis >= 20){
    heartrate.getValue(sensorPin);
    rateValue = heartrate.getRate();
      
    if(rateValue > 0 && rateValue < 220){
      oldRateValue = rateValue;
      Serial.println(oldRateValue);
    }
    else if(rateValue >= 220){
      //Serial.println("Impossible heart rate");
    }

    if (Serial.available()) {
      SerialBT.write(Serial.read());
    }
    if (SerialBT.available()) {
      Serial.write(SerialBT.read());
    }

    hrMillis = currentMillis;
  }

}
