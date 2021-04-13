
#include <ESP8266WiFi.h>
#include <espnow.h>
#define BLUE D5
#define PINK D6
#define YELLOW D7
#define ORANGE D8

typedef struct user_input {
    int x;
    int y;
} user_input;

user_input pos;

int currentStep = 0;

int totalStep = 0;

int dir = 1;

void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&pos, incomingData, sizeof(pos));
  //Serial.print("Bytes received: ");
  //Serial.println(len);            leave in for debugging if necessary
  Serial.print("x: ");
  Serial.println(pos.x);
  Serial.print("y: ");
  Serial.println(pos.y);
  Serial.println();  

  DriveMotor(&pos);
  
}

void DriveMotor (user_input *currentPos){

  int mag = abs(currentPos.x);
  int currentDir = currentPos.x / mag;

  for (int i = 0 ; i < mag ; i++){
    Step(currentDir);
    delay(3);
  }
}

void Step (int dir){
  
  currentStep += 2*dir;
  
  if (currentStep == 9)
    currentStep = 1;
  else if (currentStep == 10)
    currentStep = 2;
  else if(currentStep == 0)
    currentStep = 8;
  else if(currentStep == -1)
    currentStep = 7;

  //Serial.println(currentStep);
  
  switch (currentStep){
    case 1:
      digitalWrite(ORANGE, LOW);
      digitalWrite(YELLOW, LOW);
      digitalWrite(PINK, HIGH);
      digitalWrite(BLUE, HIGH) ;                   
      break;
      
    case 2:
      digitalWrite(ORANGE, LOW);
      digitalWrite(YELLOW, LOW);
      digitalWrite(PINK, HIGH);
      digitalWrite(BLUE, HIGH);
      break;
      
    case 3:
      digitalWrite(ORANGE, HIGH);
      digitalWrite(YELLOW, LOW);
      digitalWrite(PINK, HIGH);
      digitalWrite(BLUE, HIGH);
      break;
      
    case 4:
      digitalWrite(ORANGE, HIGH);
      digitalWrite(YELLOW, LOW);
      digitalWrite(PINK, LOW);
      digitalWrite(BLUE, HIGH);
      break;
      
    case 5:
      digitalWrite(ORANGE, HIGH);
      digitalWrite(YELLOW, HIGH);
      digitalWrite(PINK, LOW);
      digitalWrite(BLUE, HIGH);
      break;
      
    case 6:
      digitalWrite(ORANGE, HIGH);
      digitalWrite(YELLOW, HIGH);
      digitalWrite(PINK, LOW);
      digitalWrite(BLUE, LOW);
      break;

    case 7:
      digitalWrite(ORANGE, HIGH);
      digitalWrite(YELLOW, HIGH);
      digitalWrite(PINK, HIGH);
      digitalWrite(BLUE, LOW);
      break;
      
    case 8:
      digitalWrite(ORANGE, LOW);
      digitalWrite(YELLOW, HIGH);
      digitalWrite(PINK, HIGH);
      digitalWrite(BLUE, LOW);
      break;
      
    default:
      digitalWrite(ORANGE, LOW);
      digitalWrite(YELLOW, LOW);
      digitalWrite(PINK, LOW);
      digitalWrite(BLUE, LOW);
      Serial.println("issue here!");
      currentStep = 1;
      break;
  } 
}

void StopMotor (){
    digitalWrite(ORANGE, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(PINK, LOW);
    digitalWrite(BLUE, LOW);
}

void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  delay(3000);

  pinMode(BLUE, OUTPUT);
  pinMode(PINK, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(ORANGE, OUTPUT);
}


void loop() {  
  if(totalStep > 1050 || totalStep < 0)
    dir = -1*dir;

  totalStep += dir;
  Step(dir);
  //StopMotor(); //this can be added in case of higher-efficienccy, lower torque-applications
  Serial.println(totalStep);
  delay(3);
  
}
