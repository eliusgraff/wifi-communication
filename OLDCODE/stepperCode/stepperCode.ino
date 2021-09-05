
#include <ESP8266WiFi.h>
#include <espnow.h>
#define BLUE D5
#define PINK D6
#define YELLOW D7
#define ORANGE D8

int currentStep = 0;

void Step (int dir){
  
  currentStep += 2*dir;
  
  if (currentStep > 8)
    currentStep = 2;
  else if(currentStep < 2)
    currentStep = 8;

  Serial.println(currentStep);
  
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

void DriveMotor (int currentPos){

  if(currentPos > 850)
    Step(1);

  else if(currentPos < 700)
    Step(-1);
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

int sensorValue;

void loop() {  

  sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  DriveMotor(sensorValue);
  delay(3);
  
}
