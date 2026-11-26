
#include <ESP8266WiFi.h>
#include <espnow.h>

#include <LiquidCrystal_I2C.h>
#include <Adafruit_Fingerprint.h>
#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
SoftwareSerial mySerial(D5, D6);
#else
#define mySerial Serial1
#endif
LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
uint8_t broadcastAddress[] = {0xEC, 0xFA, 0xBC, 0xD4, 0xF6, 0xD0};
String subject[5] = {"W", "C", "O", "M", "E"};

int btn = D7;
int flag = 1;

String temperature;
int fingerprintID;
int incomingTemp;
int a = 0;
int id_1 = 0;
int id_2 = 0;
int id_3 = 0;
int id_4 = 0;
int id_5 = 0;

const long interval = 10000;
unsigned long previousMillis = 0;    // will store last time DHT was updated
String success;

typedef struct struct_message {
  int id;
  int attendance;
  String sub;
} struct_message;

struct_message fingerReadings;

struct_message incomingReadings;

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  //Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0) {
    //  Serial.println("Delivery success");
  }
  else {
    Serial.println("Delivery fail");
  }
}

// Callback when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  incomingTemp = incomingReadings.id;
}

void getReadings() {

}

void printIncomingReadings() {

}

void setup() {
  lcd.init();
  lcd.backlight();
  while (!Serial);
  delay(100);

  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) {
      delay(1);
    }
  }
  finger.getParameters();
  finger.getTemplateCount();
  Serial.begin(115200);
  pinMode(btn, INPUT);
  // Init DHT sensor


  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_register_send_cb(OnDataSent);
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  esp_now_register_recv_cb(OnDataRecv);
  lcd.clear();
  lcd.print("Smart Attendance");
  lcd.setCursor(5, 1);
  lcd.print("System");
  delay(3000);
  lcd.clear();
}

void loop() {
  getFingerprintID();
  if (fingerprintID == 1)
  {
    id_1 = 1;
  }


  if (fingerprintID == 2)
  {
    id_2 = 1;
  }

  if (fingerprintID == 3)
  {
    id_3 = 1;
  }

  if (fingerprintID == 4)
  {
    id_4 = 1;
  }

  if (fingerprintID == 5)
  {
    id_5 = 1;
  }

  if (a == 5)
  {
    a = 0;
  }
  //delay(50);
  if (digitalRead(btn) == 1)
  {

    lcd.clear();
    lcd.print("Data sending for...");
    lcd.setCursor(0, 1);
    delay(300);
    lcd.print("Sub-");
    if (subject[a] == "W")
      lcd.print("EC409E");
    if (subject[a] == "C")
      lcd.print("EC503E");
    if (subject[a] == "O")
      lcd.print("EC505E");
    if (subject[a] == "M")
      lcd.print("MN101E");
    if (subject[a] == "E")
      lcd.print("EC413E");

    fingerReadings.id = 1;
    fingerReadings.attendance = id_1;
    fingerReadings.sub = subject[a];
    esp_now_send(broadcastAddress, (uint8_t *) &fingerReadings, sizeof(fingerReadings));
    delay(100);

    fingerReadings.id = 2;
    fingerReadings.attendance = id_2;
    fingerReadings.sub = subject[a];
    esp_now_send(broadcastAddress, (uint8_t *) &fingerReadings, sizeof(fingerReadings));
    delay(100);

    fingerReadings.id = 3;
    fingerReadings.attendance = id_3;
    fingerReadings.sub = subject[a];
    esp_now_send(broadcastAddress, (uint8_t *) &fingerReadings, sizeof(fingerReadings));
    delay(100);

    fingerReadings.id = 4;
    fingerReadings.attendance = id_4;
    fingerReadings.sub = subject[a];
    esp_now_send(broadcastAddress, (uint8_t *) &fingerReadings, sizeof(fingerReadings));
    delay(100);

    fingerReadings.id = 5;
    fingerReadings.attendance = id_5;
    fingerReadings.sub = subject[a];
    esp_now_send(broadcastAddress, (uint8_t *) &fingerReadings, sizeof(fingerReadings));
    delay(100);

    fingerReadings.id = 0;
    fingerReadings.attendance = 0;
    fingerReadings.sub = "N";
    esp_now_send(broadcastAddress, (uint8_t *) &fingerReadings, sizeof(fingerReadings));
    delay(1000);
    lcd.clear();
    lcd.print("Data Sent.");
    delay(1000);
    a++;

    lcd.clear();
    id_1 = 0;
    id_2 = 0;
    id_3 = 0;
    id_4 = 0;
    id_5 = 0;
    fingerprintID = 0;
  }
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      //Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      //Serial.println("No finger detected");
      lcd.setCursor(0, 0);
      lcd.print("Scan Your Finger!");
      lcd.setCursor(0, 1);
      lcd.print("Sub-");
      if (subject[a] == "W")
        lcd.print("EC409E");
      if (subject[a] == "C")
        lcd.print("EC503E");
      if (subject[a] == "O")
        lcd.print("EC505E");
      if (subject[a] == "M")
        lcd.print("MN101E");
      if (subject[a] == "E")
        lcd.print("EC413E");

    case FINGERPRINT_PACKETRECIEVEERR:
      //Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      //Serial.println("Imaging error");
      return p;
    default:
      //Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      //Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      //Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      //Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      //Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      //Serial.println("Could not find fingerprint features");
      return p;
    default:
      // Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    //Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    //Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    //Serial.println("Did not find a match");
    return p;
  } else {
    //Serial.println("Unknown error");
    return p;
  }

  fingerprintID = finger.fingerID;
  //Serial.print("Found ID #"); Serial.print(finger.fingerID);
  //Serial.print(" with confidence of "); Serial.println(finger.confidence);
  lcd.clear();
  lcd.print("Found ID- ");
  lcd.print(finger.fingerID);
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("Attendance added");
  delay(2000);
  lcd.clear();
  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  //Serial.print("Found ID #"); Serial.print(finger.fingerID);
  //Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID;
}
