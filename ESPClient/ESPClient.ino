#include <ESP8266WiFi.h>
#include <espnow.h>
#define FORWARD 14
#define BACK 12


// Structure example to receive data
// Must match the sender structure
typedef struct user_input {
    int x;
    int y;
} user_input;

// Create a struct_message called myData
user_input pos;

//// Callback function that will be executed when data is received
//void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
//  memcpy(&pos, incomingData, sizeof(pos));
//  Serial.print("Bytes received: ");
//  Serial.println(len);
//  Serial.print("x: ");
//  Serial.println(pos.x);
//  Serial.print("y: ");
//  Serial.println(pos.y);
//  Serial.println();
//}



void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&pos, incomingData, sizeof(pos));
  //Serial.print("Bytes received: ");
  //Serial.println(len);            leave in for debugging if necessary
  Serial.print("x: ");
  Serial.println(pos.x);
  Serial.print("y: ");
  Serial.println(pos.y);
  Serial.println();


//orienting position
   int myPos = pos.x - 520;

//'dead' area where nothing should happen
  if( abs(myPos) < 100 ){
    analogWrite(FORWARD, 0);
    analogWrite(BACK, 0);
    Serial.println( "dead area ");
    return;
  }

//Sending control signals
  if ( myPos <  0 ){
    Serial.println( "negative");
    analogWrite(FORWARD,0);
    analogWrite(BACK,2*abs(myPos));
  }

  else{
    Serial.println( "positive");
    analogWrite(BACK,0);
    analogWrite(FORWARD, 2*myPos);
  }
  
}



 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  Serial.println(WiFi.macAddress());
  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("ready for wifi");

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second

}
