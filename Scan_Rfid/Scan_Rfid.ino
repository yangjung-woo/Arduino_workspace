
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <SPI.h>
#include <MFRC522.h>
// Set these to run example.
#define FIREBASE_HOST "example.firebaseio.com"
#define FIREBASE_AUTH "token_or_secret"
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"
#define SS_PIN D8 //SDA 연결핀
#define RST_PIN D1

MFRC522 rfid(SS_PIN, RST_PIN);
void setup() {
  Serial.begin(115200);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
    SPI.begin();           // Init SPI bus  
    rfid.PCD_Init();       // Init MFRC522
}
char str[9];
void loop() {
   if ( ! rfid.PICC_IsNewCardPresent()) {
      return;  
    }
    if ( ! rfid.PICC_ReadCardSerial()) {
      return;  
    }
    Serial.print("UID tag : ");
  String content= "";
  byte letter;
 for (byte i = 0; i < rfid.uid.size; i++) { 
     // Serial.print(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
     // Serial.println(rfid.uid.uidByte[i], HEX);
     content.concat(String(rfid.uid.uidByte[i] < 0x10 ? "0" : ""));
     content.concat(String(rfid.uid.uidByte[i], HEX));

  }
  content.toUpperCase();
  int cnt=0;
  for(int i=0; i<content.length(); i++) {
    str[i] = content[i];
    cnt++;   
  }
  for(int i=0; i<9; i++) {
    Serial.println(str[i]);
  }  
  delay(1000);
  // set string value
  Firebase.setString("rfid",str);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
}

​

​
