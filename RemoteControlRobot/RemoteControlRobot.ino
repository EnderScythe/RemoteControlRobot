
//Left motor is input 1 and 2, right motor is input 3 and 4
//defining motor pins
#define ENABLE_LM 5
#define ENABLE_RM 6
#define INPUT_LM_1 2
#define INPUT_LM_2 3
#define INPUT_RM_3 8
#define INPUT_RM_4 7
#define BUTTON 4

//change voltage with input pins to control direction
//change analog write values to enable pins to control speed

bool on = false;

void setup() {
  for(int i = 2; i < 8; i++){
    pinMode(i, OUTPUT);
  }
  analogWrite(ENABLE_LM, 150);
  analogWrite(ENABLE_RM, 150);
  delay(1000);
}

void loop() {
  if(on){
  goForward();
  delay(1000);
  stop();
  goBackward();
  delay(1000);
  stop();
  } else {
    stop();
  }
  int buttonState = digitalRead(BUTTON);
  if(buttonState == HIGH){
    on = !on;
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
  digitalWrite(INPUT_LM_1, LOW);
  digitalWrite(INPUT_LM_2, LOW);
  digitalWrite(INPUT_RM_3, LOW);
  digitalWrite(INPUT_RM_4, LOW);
}
