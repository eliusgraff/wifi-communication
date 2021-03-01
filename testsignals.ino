#include <ESP8266WiFi.h>
#define FORWARD 12
#define BACK 14

void setup() {

  Serial.begin(9600);
  //delay(1000);
  Serial.print("starting");

  pinMode(FORWARD,OUTPUT);
  pinMode(BACK,OUTPUT);
  
  analogWriteFreq(100);
}

void SendControlSignal( int pos )
{

//orienting position
  pos -= 520;

//'dead' area where nothing should happen
  if( abs(pos) < 30 ){
    analogWrite(FORWARD, 0);
    analogWrite(BACK, 0);
    Serial.println( "dead area ");
    return;
  }

//Sending control signals
  if ( pos <  0 ){
    Serial.println( "negative");
    analogWrite(FORWARD,0);
    analogWrite(BACK,2*abs(pos));
  }

  else{
    Serial.println( "positive");
    analogWrite(BACK,0);
    analogWrite(FORWARD, 2*pos);
  }
 
}


int randnum;

void loop() {
  // put your main code here, to run repeatedly:
  randnum = random(1023);
  Serial.println( randnum );
  //Serial.println( "processing signal now" );
  SendControlSignal ( randnum );
  //Serial.println( "signal Processed" );
  delay(100);  // max speed tested at is 10 data points/sec
}