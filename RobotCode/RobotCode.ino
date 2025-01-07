#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


//Left motor is input 1 and 2, right motor is input 3 and 4
//defining motor pins
#define ENABLE_LM 5
#define ENABLE_RM 6
#define INPUT_LM_1 2
#define INPUT_LM_2 3
#define INPUT_RM_3 8
#define INPUT_RM_4 7


//change voltage with input pins to control direction
//change analog write values to enable pins to control speed

RF24 radio(9, 10);
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  for(int i = 2; i < 8; i++){
    if(i == 4){
      pinMode(i, OUTPUT);
    }
  }
  analogWrite(ENABLE_LM, 200);
  analogWrite(ENABLE_RM, 200);

  radio.begin();
  radio.setChannel(0);
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if(radio.available()){
    digitalWrite(4, HIGH);
    char text[32] = "";
    radio.read(&text, sizeof(text));
    //Serial.println(text);

    String data[2];
    int j = 0;
    for(int i = 0; i < 32; i++){
      if(text[i] == ' '){
        j++;
        continue;
      } else if(text[i] == NULL){
        break;
      }
      data[j] += text[i];
    }
    float roll = data[0].toFloat() - 2;
    float pitch = data[1].toFloat();
    if(abs(pitch) >= abs(roll)){
      if(pitch < -10){
        rotateCCW();
      } else if(pitch > 10){
        rotateCW();
      }
    } else {
      if(roll < -10){
        goForward();
      } else if(roll > 10){
        goBackward();
      }
    }    

    if(pitch < 10 && pitch > -10 && roll < 10 && roll > -10){
      stop();
    }

    Serial.print(roll); 
    Serial.print(", ");
    Serial.println(pitch);
     
  } else {
    digitalWrite(4, LOW);
    stop();
  }
}

void goForward(){
  digitalWrite(INPUT_LM_1, HIGH);
  digitalWrite(INPUT_LM_2, LOW);
  digitalWrite(INPUT_RM_3, LOW);
  digitalWrite(INPUT_RM_4, HIGH);
}

void goBackward(){
  digitalWrite(INPUT_LM_1, LOW);
  digitalWrite(INPUT_LM_2, HIGH);
  digitalWrite(INPUT_RM_3, HIGH);
  digitalWrite(INPUT_RM_4, LOW);
}

void rotateCW(){
  digitalWrite(INPUT_LM_1, HIGH);
  digitalWrite(INPUT_LM_2, LOW);
  digitalWrite(INPUT_RM_3, HIGH);
  digitalWrite(INPUT_RM_4, LOW);
}

void rotateCCW(){
  digitalWrite(INPUT_LM_1, LOW);
  digitalWrite(INPUT_LM_2, HIGH);
  digitalWrite(INPUT_RM_3, LOW);
  digitalWrite(INPUT_RM_4, HIGH);
}

void stop(){
  //setSpeed(0, 0);
  digitalWrite(INPUT_LM_1, LOW);
  digitalWrite(INPUT_LM_2, LOW);
  digitalWrite(INPUT_RM_3, LOW);
  digitalWrite(INPUT_RM_4, LOW);
}

void setSpeed(int left, int right){
  analogWrite(ENABLE_LM, left);
  analogWrite(ENABLE_RM, right);
}
