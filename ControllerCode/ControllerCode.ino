#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "MPU.h"

RF24 radio(7, 8);
const byte address[6] = "00001";
MPU* mpu = new MPU();
unsigned long previousTime = 0, currentTime = 0;
float pitch = 0, roll = 0;

void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  
  Wire.setClock(400000);
  Wire.begin();
  delay(250);
  mpu->startMPU();
  mpu->calibrateMPU(2000);

  radio.begin();
  radio.setChannel(0);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

}

void loop() {
  // previousTime = currentTime;
  // currentTime = micros();
  //Serial.println(currentTime - previousTime);
  mpu->prepareMeasurements();
  float roll = mpu->getRoll();
  float pitch = mpu->getPitch();
  String msg = String(roll) + " " + String(pitch);
  char data[msg.length() + 1];
  msg.toCharArray(data, msg.length() + 1);
  radio.write(&data, sizeof(data));
  Serial.print(roll); Serial.print(", ");
  Serial.println(pitch);
}
