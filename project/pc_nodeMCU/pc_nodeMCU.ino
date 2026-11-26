
#include <ESP8266WiFi.h>
#include <espnow.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>

//REPLACE WITH THE MAC Address of your receiver
uint8_t broadcastAddress[] = {0xF4, 0xCF, 0xA2, 0x79, 0x89, 0x6D};

//Digital pin connected to the DHT sensor
#define DHTPIN D3
int a = 0;
int led = 16;
int flag = 1;
// Define variables to store incoming readings
int incomingId;
String incomingsName;
int incomingAttendance;
String incomingSub;

// Updates DHT readings every 10 seconds
const long interval = 10000;
unsigned long previousMillis = 0;    // will store last time DHT was updated

// Variable to store if sending data was successful
String success;

//Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
  int id;
  int attendance;
  String sub;
} struct_message;

// Create a struct_message called DHTReadings to hold sensor readings
struct_message fingerReadings;

struct_message incomingReadings;

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  // Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0) {
    // Serial.println("Delivery success");
  }
  else {
    // Serial.println("Delivery fail");
  }
}

// Callback when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  incomingId = incomingReadings.id;
  Serial.print(incomingId);
  incomingAttendance = incomingReadings.attendance;
  Serial.print(incomingAttendance);
  incomingSub = incomingReadings.sub;
  Serial.println(incomingSub);
  //incomingTemp = "";
}

void getReadings() {

}

void printIncomingReadings() {


}

void setup() {

  Serial.begin(115200);
  pinMode(led, OUTPUT);


  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    //Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Set ESP-NOW Role
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);

  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {

  printIncomingReadings();

}
