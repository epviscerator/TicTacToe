/*
  THIS CODE WAS BROUGHT TO YOU BY BALLFART INDUSTRIES
  BORN TO FART
  WORLD IS A TOILET
  CRAP EM ALL 1989
  I AM THOMAS CRAPPER
  793849237 DEAD RATS
*/


#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <Keypad.h>

//#define SDA 4 //Define SDA pins
//#define SCL 2 //Define SCL pins


char keys[4][4] = {
  {'0', '1', '2', 'X'},
  {'3', '4', '5', 'X'},
  {'6', '7', '8', 'X'},
  {'X', 'X', 'X', 'X'}
};
// byte rowPins[4] = {14, 27, 26, 25}; // connect to the row pinouts of the keypad
// byte colPins[4] = {13, 15, 4, 23}; // connect to the column pinouts of the keypad
byte rowPins[4] = {13, 12, 14, 27}; 
byte colPins[4] = {4, 25, 33, 32}; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);
LiquidCrystal_I2C lcd(0x27,16,2);

// DO NOT QUESTION MY CHOICE OF PHONE NAME AND PASSWORD NO ONE WILL EVER GUESS IT
const char* ssid = "20,000 gallons of lard";
const char* password = "BallsJuice42069";
const char* mqtt_server = "ethanphamxd.duckdns.org";

WiFiClient espClient;
PubSubClient client(espClient);

bool gameActive = false;
String currentStatus = "Waiting for Laptop...";

/*
  CRAZY? I WAS CRAZY ONCE.  THEY LOCKED ME IN A ROOM.  A RUBBER ROOM.  A RUBBER ROOM WITH Project 5(Tic-Tac-Toe). 
  AND Project 5(Tic-Tac-Toe) MAKES ME CRAZY.  CRAZY? I WAS CRAZY ONCE.  THEY LOCKED ME IN A ROOM.  A RUBBER ROOM.  A RUBBER ROOM WITH Project 5(Tic-Tac-Toe). 
  AND Project 5(Tic-Tac-Toe) MAKES ME CRAZY.  CRAZY? I WAS CRAZY ONCE.  THEY LOCKED ME IN A ROOM.  A RUBBER ROOM.  A RUBBER ROOM WITH Project 5(Tic-Tac-Toe). 
  AND Project 5(Tic-Tac-Toe) MAKES ME CRAZY.  CRAZY? I WAS CRAZY ONCE.  THEY LOCKED ME IN A ROOM.  A RUBBER ROOM.  A RUBBER ROOM WITH Project 5(Tic-Tac-Toe). 
  AND Project 5(Tic-Tac-Toe) MAKES ME CRAZY.  CRAZY? I WAS CRAZY ONCE.  THEY LOCKED ME IN A ROOM.  A RUBBER ROOM.  A RUBBER ROOM WITH Project 5(Tic-Tac-Toe). 
  AND Project 5(Tic-Tac-Toe) MAKES ME CRAZY.  CRAZY? I WAS CRAZY ONCE.  THEY LOCKED ME IN A ROOM.  A RUBBER ROOM.  A RUBBER ROOM WITH Project 5(Tic-Tac-Toe). 
  AND Project 5(Tic-Tac-Toe) MAKES ME CRAZY.  CRAZY? I WAS CRAZY ONCE.  THEY LOCKED ME IN A ROOM.  A RUBBER ROOM.  A RUBBER ROOM WITH Project 5(Tic-Tac-Toe). 
  AND Project 5(Tic-Tac-Toe) MAKES ME CRAZY.  CRAZY? I WAS CRAZY ONCE.  THEY LOCKED ME IN A ROOM.  A RUBBER ROOM.  A RUBBER ROOM WITH Project 5(Tic-Tac-Toe). 
  AND Project 5(Tic-Tac-Toe) MAKES ME CRAZY.
*/

void setup_wifi(){
  delay(10);
  Serial.print("KONECKTIGN...");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print("A");

  }
  Serial.println("Wifi connected, may god have mercy on you.");
  lcd.clear();
}

void callback(char* topic, byte* payload, unsigned int length) {
  String msg = "";
  // START DA GAME WOOOOOOOOOOO
  for (int i = 0; i < length; i++) msg += (char)payload[i];
  if (String(topic) == "tictactoe/move"){
    currentStatus = "Laptop moved: " + msg;
  }
  if (msg == "MODE:2P") {
    gameActive = true;
    currentStatus = "2P Mode Start!";
  } else if (msg == "MODE:1P") {
    gameActive = false;
    currentStatus = "Error: 2P Only";
    lcd.clear();
  } else {
    currentStatus = msg; 
  }
}
void scrollDisplay(String text) {
  //Serial.println(text);
  // EPIC LOOP WHOAAAAAAAAAAAAA
  static unsigned long lastScroll = 0;
  static int pos = 0;
  if (millis() - lastScroll > 350) {
    lcd.setCursor(0, 0);
    if (text.length() <= 16) {
      lcd.print(text + "                ");
    } else {
      String displayStr = text + "   " + text; 
      lcd.print(displayStr.substring(pos, pos + 16));
      pos++;
      if (pos > text.length() + 3) pos = 0;
    }
    lastScroll = millis();
  }
}

void reconnect() {
  //Serial.println("PLEASE");
  // SUBSKRIBE TO MY YOUTUBE CHANNEL I ONLY FEEL PAIN FOR MORE EPIC CLIPS 
  while (!client.connected()) {
      if (client.connect("ESP32_TTT_Player1")) {
        Serial.println("FarTEXTURBO");
        client.subscribe("game/status");
        client.subscribe("game/config");
        client.subscribe("tictactoe/move");
        //client.subscribe("VICTORY");

      } else {
        delay(5000);
      }
  }
}


/*
  CRAZY? I WAS CRAZY ONCE.  THEY LOCKED ME IN A ROOM.  A RUBBER ROOM.  A RUBBER ROOM WITH Project 5(Tic-Tac-Toe). 
  AND Project 5(Tic-Tac-Toe) MAKES ME CRAZY.  CRAZY? I WAS CRAZY ONCE.  THEY LOCKED ME IN A ROOM.  A RUBBER ROOM.  A RUBBER ROOM WITH Project 5(Tic-Tac-Toe). 
  AND Project 5(Tic-Tac-Toe) MAKES ME CRAZY.  CRAZY? I WAS CRAZY ONCE.  THEY LOCKED ME IN A ROOM.  A RUBBER ROOM.  A RUBBER ROOM WITH Project 5(Tic-Tac-Toe). 
  AND Project 5(Tic-Tac-Toe) MAKES ME CRAZY.  CRAZY? I WAS CRAZY ONCE.  THEY LOCKED ME IN A ROOM.  A RUBBER ROOM.  A RUBBER ROOM WITH Project 5(Tic-Tac-Toe). 
  AND Project 5(Tic-Tac-Toe) MAKES ME CRAZY.  CRAZY? I WAS CRAZY ONCE.  THEY LOCKED ME IN A ROOM.  A RUBBER ROOM.  A RUBBER ROOM WITH Project 5(Tic-Tac-Toe). 
  AND Project 5(Tic-Tac-Toe) MAKES ME CRAZY.  CRAZY? I WAS CRAZY ONCE.  THEY LOCKED ME IN A ROOM.  A RUBBER ROOM.  A RUBBER ROOM WITH Project 5(Tic-Tac-Toe). 
  AND Project 5(Tic-Tac-Toe) MAKES ME CRAZY.  CRAZY? I WAS CRAZY ONCE.  THEY LOCKED ME IN A ROOM.  A RUBBER ROOM.  A RUBBER ROOM WITH Project 5(Tic-Tac-Toe). 
  AND Project 5(Tic-Tac-Toe) MAKES ME CRAZY.  CRAZY? I WAS CRAZY ONCE.  THEY LOCKED ME IN A ROOM.  A RUBBER ROOM.  A RUBBER ROOM WITH Project 5(Tic-Tac-Toe). 
  AND Project 5(Tic-Tac-Toe) MAKES ME CRAZY.
*/

void setup() {
  // INTIIALIZE EVERYCTHIGN
  Serial.begin(115200);
  //delay(333);
  lcd.init();
  lcd.backlight();
  //Wire.begin(SDA, SCL); 
  // if (!i2CAddrTest(0x27)) {
  //   lcd = LiquidCrystal_I2C(0x3F, 16, 2);
  // }
  lcd.print("CONECKTING...");
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  //Serial.println("FartEXTurbo");
}
void loop() {
  //Serial.println("Fart");
  // CONNECT TO SERVER OR SOMETHING
  if (!client.connected()) reconnect();
  client.loop();
  
  // SCROLLLLLLLLLLLLLLLLLLLLLLL COOL SCROLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL IM A GENIUSS
  scrollDisplay(currentStatus);
  //Serial.println(gameActive);
  char key = keypad.getKey();
if (gameActive && key && key != 'X') { 
    Serial.println("Fart");
    // SENDS THE INDEX 0-8 TO THE SERVER.  CRAZY? I WAS CRAZY ONCE.  THEY LOCKED ME IN A ROOM.  A RUBBER ROOM.  A RUBBER ROOM WITH Project 5(Tic-Tac-Toe). 
    // AND Project 5(Tic-Tac-Toe) MAKES ME CRAZY.
    char move[2] = {key, '\0'};
    client.publish("tictactoe/move", move);
    Serial.print("ESP32 Sent Move: "); Serial.println(move);
  }
  
}

// bool i2CAddrTest(uint8_t addr) {
//  Wire.begin();
//  Wire.beginTransmission(addr);
//  if (Wire.endTransmission() == 0) {
//   return true;
//  }
//   return false;
// }
