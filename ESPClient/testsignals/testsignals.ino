#include <ESP8266WiFi.h>

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  delay(1000);
  Serial.print("starting");
  pinMode(12,OUTPUT);
  pinMode(3,OUTPUT);
  analogWriteFreq(100);
}

void SendControlSignal( int pos )
{

//orienting position
  pos -= 520;

//'dead' area where nothing should happen
  if( abs(pos) < 30 ){
    analogWrite(12, 0);
    Serial.println( "dead area ");
    return;
  }

//Setting direction signal
  if ( pos <  0 ){
    Serial.println( "negative");
    digitalWrite(3,1);
  }

  else{
    Serial.println( "positive");
    digitalWrite(3,0);
  }

  analogWrite(12, 2*abs(pos));
  
}


int randnum;

void loop() {
  // put your main code here, to run repeatedly:
  randnum = random(1023);
  Serial.println( randnum );
  Serial.println( "processing signal now" );
  SendControlSignal ( randnum );
  Serial.println( "signal Processed" );
  delay(500);  
}
