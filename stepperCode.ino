
/*
 Stepper Motor Control - one step at a time

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor will step one step at a time, very slowly.  You can use this to
 test that you've got the four wires of your stepper wired to the correct
 pins. If wired correctly, all steps should be in the same direction.

 Use this also to count the number of steps per revolution of your motor,
 if you don't know it.  Then plug that number into the oneRevolution
 example to see if you got it right.

 Created 30 Nov. 2009
 by Tom Igoe

 */

#include <Stepper.h>


#define BLUE D5
#define PINK D6
#define YELLOW D7
#define ORANGE D8

const int stepsPerRevolution = 64;  // change this to fit the number of steps per revolution
// for your motor

int stepCount = 0;         // number of steps the motor has taken

int currentStep = 0;

void Step (int dir)
{
  
  currentStep += 2*dir;
  
  if (currentStep == 9)
    currentStep = 1;
  else if (currentStep == 10)
    currentStep = 2;
  else if(currentStep == 0)
    currentStep = 8;
  else if(currentStep == -1)
    currentStep = 7;

  Serial.println(currentStep);
  
  switch (currentStep)
  {
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

void StopMotor ()
{
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


  int dir = -1;

  // step one step:

  if (stepCount == 1000){
    stepCount = 0;
    Serial.println("STOP!!");
    StopMotor();
    delay(5000);
    Serial.print("reverse direction: ");
    dir = dir*(-1);
    Serial.println(dir);
  }
    
    
  Step(dir);
  Serial.print("steps:");
  //Serial.println(stepCount);
  stepCount++;
  delay(3);
}
