#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);
const byte address[6] = "00001";
boolean state = 0;


void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

}

void loop() {
   if (radio.available()) {
    radio.read(&state, sizeof(state));
    Serial.println(state);
    if(state){
      digitalWrite(5, HIGH);
    } else if(!state) {
      digitalWrite(5, LOW);
    }
  }
}
