#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>
#include <WiFi.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>

#define CLIENT_ID "ESP32-001"  // CHANGE IT AS YOU DESIRE
#define SDA 13 // Define SDA pins
#define SCL 14 // Define SCL pins

// The MQTT topics that this device should publish/subscribe
#define PUBLISH_TOPIC "esp32-001/send"
#define SUBSCRIBE_TOPIC "esp32-001/receive"

#define PUBLISH_INTERVAL 5000  // 4 second

WiFiClient network;
MQTTClient mqtt = MQTTClient(256);

unsigned long lastPublishTime = 0;
// define lcd wowie go
LiquidCrystal_I2C lcd(0x27,16,2);
// define the symbols on the buttons of the keypad
char keys[4][4] = {
 {'1', '2', '3', 'A'},
 {'4', '5', '6', 'B'},
 {'7', '8', '9', 'C'},
 {'*', '0', '#', 'D'}
};
byte rowPins[4] = {14, 27, 26, 25}; // connect to the row pinouts of the keypad
byte colPins[4] = {13, 21, 22, 23}; // connect to the column pinouts of the keypad
// initialize an instance of class NewKeypad
Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

const char WIFI_SSID[] = "Blue beach";              // CHANGE TO YOUR WIFI SSID
const char WIFI_PASSWORD[] = "stop4321";           // CHANGE TO YOUR WIFI PASSWORD
const char MQTT_BROKER_ADRRESS[] = "ethanphamxd.duckdns.org";  // CHANGE TO MQTT BROKER'S IP ADDRESS
const int MQTT_PORT = 1883;
const char MQTT_USERNAME[] = "";  // CHANGE IT IF REQUIRED
const char MQTT_PASSWORD[] = "";  // CHANGE IT IF REQUIRED
// Initialize Tic-tac-toe 2D array & other variables
int intsquare[9];
int truesquare[9];

void setup() {
  Serial.begin(115200); // Initialize the serial port and set the baud rate to 115200
  delay(1000);
  Serial.println("ESP32 is ready! "); // Print the string "ESP32 is ready! "
  // MQTT CODE
  // set the ADC attenuation to 11 dB (up to ~3.3V input)
  analogSetAttenuation(ADC_11db);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("ESP32 - Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  connectToMQTT();


  // LCD code
  //lcd.clear();
  Wire.begin(SDA, SCL); // attach the IIC pin
  if (!i2CAddrTest(0x27)) {
    lcd = LiquidCrystal_I2C(0x3F, 16, 2);
  }
  lcd.init(); // LCD driver initialization
  lcd.backlight(); // Open the backlight
    
  // Fill TTT arrays
  for (int i = 0; i < 9; i++) {
      intsquare[i] = i;
  }
      
  for (int i = 0; i < 9; i++) {
      truesquare[i] = 0; 
  }

  // Print TTT Array to LCD
  for (int i = 0; i < 9; i++) { 
    
    if (((i % 3) == 0) && (i != 0)) {
      lcd.print(" ");   
    }

    lcd.print(i);
  }
  
  // Print which row is which to the LCD for QoL purposes
  lcd.setCursor(0,1); // Move the cursor to column 0, row 1
  lcd.print("R1"); // The print content is displayed on the LCD
  lcd.setCursor(4, 1);
  lcd.print("R2");
  lcd.setCursor(8, 1);
  lcd.print("R3");

  lcd.setCursor(12, 1);
  lcd.print("Turn");

  // Loop until turn 10 (or 9 if you insist)
  for (int turn = 1; turn < 10; turn++) {
    // If turn is odd (x)
    if ((turn % 2) != 0) {
      //Serial.println("Fart");
      int input;

      bool check_high;
      bool check_low;
      bool check_taken;
      bool ultimate_check;

      do {
        check_high = 1;
        check_low = 1;
        check_taken = 1;
        ultimate_check = 0;

        lcd.setCursor(12, 0);
        lcd.print("P1 X");

        char inputK = myKeypad.getKey();
        input = atoi(&inputK);
        if (input) {
          Serial.println(input);
          if ((input > 9)) {
            //printf("\nInvalid input! Choose a number between 0-8! (Too high!)");
            check_high = 0;
          }
          else if ((input < 0)) {
            //printf("\nInvalid input! Choose a number from 0-8! (Too low!)");
            check_low = 0;
          }
          if ((truesquare[input] == 1) || (truesquare[input] == 2)) {
            //printf("\nThat spot's taken!");
            check_taken = 0;
          }

          if (check_high == 1 && check_low == 1 && check_taken == 1) {
          ultimate_check = 1;
          }
        }
      } while(ultimate_check != 1);

      // Plug input into method
      truesquare[input] = 1;
      char dookiesquare[9];
      for (int i = 0; i < 9; i++) {
        itoa(truesquare[i], &dookiesquare[i], 1);
      }
      mqtt.publish(PUBLISH_TOPIC, dookiesquare);
    }

    // FOR PLAYER 2 (O)
    if ((turn % 2) == 0) {
      //Serial.println("TurboFart");
      //Serial.println("Fart");
      int input;

      bool check_high;
      bool check_low;
      bool check_taken;
      bool ultimate_check;

      do {
        check_high = 1;
        check_low = 1;
        check_taken = 1;
        ultimate_check = 0;

        lcd.setCursor(12, 0);
        lcd.print("P2 O");

        char inputK = myKeypad.getKey();
        input = atoi(&inputK);
        if (input) {
          Serial.println(input);
          if ((input > 9)) {
            //printf("\nInvalid input! Choose a number between 0-8! (Too high!)");
            check_high = 0;
          }
          else if ((input < 0)) {
            //printf("\nInvalid input! Choose a number from 0-8! (Too low!)");
            check_low = 0;
          }
          if ((truesquare[input] == 1) || (truesquare[input] == 2)) {
            //printf("\nThat spot's taken!");
            check_taken = 0;
          }

          if (check_high == 1 && check_low == 1 && check_taken == 1) {
          ultimate_check = 1;
          }
        }
      } while(ultimate_check != 1);

      // Plug input into method
      truesquare[input] = 2;
      char dookiesquare[9];
      for (int i = 0; i < 9; i++) {
        itoa(truesquare[i], &dookiesquare[i], 1);
      }
      mqtt.publish(PUBLISH_TOPIC, dookiesquare);
    }

    // Print the Tic Tac Toe square   
    for (int i = 0; i < 9; i++) {
        if ((i % 3) == 0) {
            lcd.print(" ");   
        }
        if (!(truesquare[i] == 1) && !(truesquare[i] == 2)) {
            lcd.print(i);
        } else {
            if (truesquare[i] == 1) {
                lcd.print("X");
            }

            if (truesquare[i] == 2) {
                lcd.print("O");
            }
        }
    }

    lcd.setCursor(0, 1);
    // Check if there's 3 in a row
        // Top row
        if (truesquare[0] == 1 && truesquare[1] == 1 && truesquare[2] == 1) {
            lcd.print("Victory for Player 1 (X)!!!");
            mqtt.publish(PUBLISH_TOPIC, "Victory for Player 1 (X)!!!");
            break;
        }
        if (truesquare[0] == 2 && truesquare[1] == 2 && truesquare[2] == 2) {
            lcd.print("Victory for Player 2 (O)!!!");
            mqtt.publish(PUBLISH_TOPIC, "Victory for Player 2 (O)!!!");
            break;
        }
        // Middle row
        if (truesquare[3] == 1 && truesquare[4] == 1 && truesquare[5] == 1) {
            lcd.print("Victory for Player 1 (X)!!!");
            mqtt.publish(PUBLISH_TOPIC, "Victory for Player 1 (X)!!!");
            break;
        }
        if (truesquare[3] == 2 && truesquare[4] == 2 && truesquare[5] == 2) {
            lcd.print("Victory for Player 2 (O)!!!");
            mqtt.publish(PUBLISH_TOPIC, "Victory for Player 2 (O)!!!");
            break;
        }
        // Bottom row
        if (truesquare[6] == 1 && truesquare[7] == 1 && truesquare[8] == 1) {
            lcd.print("Victory for Player 1 (X)!!!");
            mqtt.publish(PUBLISH_TOPIC, "Victory for Player 1 (X)!!!");
            break;
        }
        if (truesquare[6] == 2 && truesquare[7] == 2 && truesquare[8] == 2) {
            lcd.print("Victory for Player 2 (O)!!!");
            mqtt.publish(PUBLISH_TOPIC, "Victory for Player 2 (O)!!!");
            break;
        }

        // Check if there's 3 in a column
        // Left column
        if (truesquare[0] == 1 && truesquare[3] == 1 && truesquare[6] == 1) {
            lcd.print("Victory for Player 1 (X)!!!");
            mqtt.publish(PUBLISH_TOPIC, "Victory for Player 1 (X)!!!");
            break;
        }
        if (truesquare[0] == 2 && truesquare[3] == 2 && truesquare[6] == 2) {
            lcd.print("Victory for Player 1 (O)!!!");
            mqtt.publish(PUBLISH_TOPIC, "Victory for Player 2 (O)!!!");
            break;
        }
        // Middle column
        if (truesquare[1] == 1 && truesquare[4] == 1 && truesquare[7] == 1) {
            lcd.print("Victory for Player 1 (X)!!!");
            mqtt.publish(PUBLISH_TOPIC, "Victory for Player 1 (X)!!!");
            break;
        }
        if (truesquare[1] == 2 && truesquare[4] == 2 && truesquare[7] == 2) {
            lcd.print("Victory for Player 1 (O)!!!");
            mqtt.publish(PUBLISH_TOPIC, "Victory for Player 2 (O)!!!");
            break;
        }
        // Right column
        if (truesquare[2] == 1 && truesquare[5] == 1 && truesquare[8] == 1) {
            lcd.print("Victory for Player 1 (X)!!!");
            mqtt.publish(PUBLISH_TOPIC, "Victory for Player 1 (X)!!!");
            break;
        }
        if (truesquare[2] == 2 && truesquare[5] == 2 && truesquare[8] == 2) {
            lcd.print("Victory for Player 1 (O)!!!");
            mqtt.publish(PUBLISH_TOPIC, "Victory for Player 2 (O)!!!");
            break;
        }


        // Check if there's 3 in a diagonal
        // Top left to bottom right
        if (truesquare[0] == 1 && truesquare[4] == 1 && truesquare[8] == 1) {
            lcd.print("Victory for Player 1 (X)!!!");
            mqtt.publish(PUBLISH_TOPIC, "Victory for Player 1 (X)!!!");
            break;
        }
        if (truesquare[0] == 2 && truesquare[4] == 2 && truesquare[8] == 2) {
            lcd.print("Victory for Player 1 (O)!!!");
            break;
        }
        // Top right to bottom left
        if (truesquare[2] == 1 && truesquare[4] == 1 && truesquare[6] == 1) {
            lcd.print("Victory for Player 1 (X)!!!");
            mqtt.publish(PUBLISH_TOPIC, "Victory for Player 1 (X)!!!");
            break;
        }
        if (truesquare[2] == 2 && truesquare[4] == 2 && truesquare[6] == 2) {
            lcd.print("Victory for Player 1 (O)!!!");
            break;
        }
      
    }
  
}


void loop() {
  // LCD Code..?
  lcd.setCursor(0,1); // Move the cursor somewhere
  // Keypad code
  // Get the character input
  char keyPressed = myKeypad.getKey();
  // MQTT Code
  mqtt.loop();

  if (millis() - lastPublishTime > PUBLISH_INTERVAL) {
    sendToMQTT();
    lastPublishTime = millis();
  }
  // If there is a character input, sent it to the serial port
  if (keyPressed) {
    Serial.println(keyPressed);
  }
  
}

bool i2CAddrTest(uint8_t addr) {
  Wire.begin();
  Wire.beginTransmission(addr);
  if (Wire.endTransmission() == 0) {
    return true;
  }
    return false;
}

void connectToMQTT() {
  // Connect to the MQTT broker
  mqtt.begin(MQTT_BROKER_ADRRESS, MQTT_PORT, network);

  // Create a handler for incoming messages
  mqtt.onMessage(messageHandler);

  Serial.print("ESP32 - Connecting to MQTT broker");

  while (!mqtt.connect(CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD)) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  if (!mqtt.connected()) {
    Serial.println("ESP32 - MQTT broker Timeout!");
    return;
  }

  // Subscribe to a topic, the incoming messages are processed by messageHandler() function
  if (mqtt.subscribe(SUBSCRIBE_TOPIC))
    Serial.print("ESP32 - Subscribed to the topic: ");
  else
    Serial.print("ESP32 - Failed to subscribe to the topic: ");

  Serial.println(SUBSCRIBE_TOPIC);
  Serial.println("ESP32  - MQTT broker Connected!");
}
void sendToMQTT() {
  StaticJsonDocument<200> message;
  message["timestamp"] = millis();
  message["data"] = analogRead(0);  // Or you can read data from other sensors
  char messageBuffer[512];
  serializeJson(message, messageBuffer);

  mqtt.publish(PUBLISH_TOPIC, messageBuffer);

  Serial.println("ESP32 - sent to MQTT:");
  Serial.print("- topic: ");
  Serial.println(PUBLISH_TOPIC);
  Serial.print("- payload:");
  Serial.println(messageBuffer);
}

void messageHandler(String &topic, String &payload) {
  Serial.println("ESP32 - received from MQTT:");
  Serial.println("- topic: " + topic);
  Serial.println("- payload:");
  Serial.println(payload);

  char payloadChar[512];
  payload.toCharArray(payloadChar, 512);
  /*
  if (strcmp(payloadChar, "1") == 0) {
    digitalWrite(LED_BUILTIN, HIGH);

    StaticJsonDocument<200> message;
    char messageBuffer[512];
    message["ON"] = millis();
    //strcpy(messageBuffer, "ON");
    serializeJson(message, messageBuffer);
    mqtt.publish(PUBLISH_TOPIC, messageBuffer);
  }
  if (strcmp(payloadChar, "2") == 0) {
    digitalWrite(LED_BUILTIN, LOW);

    StaticJsonDocument<200> message;
    char messageBuffer[512];
    message["OFF"] = millis();
    //strcpy(messageBuffer, "ON");
    serializeJson(message, messageBuffer);
    mqtt.publish(PUBLISH_TOPIC, messageBuffer);
  }
  if (strcmp(payloadChar, "3") == 0) {
    //abort();
    for(int i = 1; i > 0; i++) {
      // empty >:)
    }
  }
*/
  // You can process the incoming data as json object, then control something
/*
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char* message = doc["AAAAAAAAAAAA"];
  Serial.println(message);

*/

}