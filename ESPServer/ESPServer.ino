#include <ESP8266WiFi.h>
#include <espnow.h>
#include <SPI.h>
#include <Adafruit_MCP3008.h>



// REPLACE WITH RECEIVER MAC Address
uint8_t broadcastAddress1[] = {0x3C, 0x61, 0x05, 0xCF, 0xB4, 0x6B};
//uint8_t broadcastAddress2[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// Structure example to send data
// Must match the receiver structure
typedef struct user_input {
    int x;
    int y;
} user_input;

Adafruit_MCP3008 adc;

// Create a struct_message called test to store variables to be sent
user_input currentPos;

static int SIZE = sizeof(currentPos);

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  char macStr[18];
  Serial.print("Packet to:");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
         mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(9600);
  delay(1000);
  
  //Serial.print(sizeof(currentPos));
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_add_peer(broadcastAddress1, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  //esp_now_add_peer(broadcastAddress2, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  adc.begin( D5, D7, D6, D8);

  

}
 
void loop() {
  
    // Set values to send
    currentPos.x = adc.readADC(2);
    currentPos.y = adc.readADC(1);
    Serial.print("X: ");
    Serial.print(currentPos.x);
    Serial.print("Y: ");
    Serial.println(currentPos.y);
    
    // Send message via ESP-NOW
    esp_now_send(0, (uint8_t *) &currentPos, SIZE);
    delay(300);
}
