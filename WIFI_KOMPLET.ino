#include <WiFi.h>

#define RELAY_PIN    13 // ESP32 pin GPIO17 that connects to relay
#define MOISTURE_PIN 34 // ESP32 pin GPIO36 (ADC0) that connects to AOUT pin of moisture sensor
#define DRY_VALUE 4095 // Suchá pôda
#define WET_VALUE 1500 // Vlhká pôda
#define MEASUREMENT_INTERVAL 20000 // 20 sekúnd
#define RELAY_DURATION 1000 // 1 sekunda
#define THRESHOLD_PERCENTAGE 50 // percentuálna hodnota vlhkosti pre aktiváciu relé

unsigned long lastMeasurementTime = 0; // čas posledného merania

const char* ssid = "Petkooo"; 
const char* password = "peto12345"; 
WiFiServer server(80); 

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  connectToWiFi();
  server.begin();
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - lastMeasurementTime >= MEASUREMENT_INTERVAL) {
    checkMoisture();
    lastMeasurementTime = currentTime;
  }

  WiFiClient client = server.available();
  if (client) {
    if (client.connected()) {
      String currentLine = "";
      while (client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println();
            int moistureValue = analogRead(MOISTURE_PIN);
            int moisturePercentage = map(moistureValue, DRY_VALUE, WET_VALUE, 0, 100);
            moisturePercentage = constrain(moisturePercentage, 0, 100); // Ensure the value is between 0 and 100
            client.print("<h1 style=\"text-align: center; font-size: 62px;\">NAMERANA VLHKOST V %: ");
            client.print(moisturePercentage);
            client.println("%</h1>");
            client.println("<button style=\"font-size: 32px; width: 400px; display: block; margin: 0 auto;\" onclick=\"window.location.reload();\">RESTART</button>");
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
  }
}

void checkMoisture() {
  int value = analogRead(MOISTURE_PIN); // read the analog value from soild moisture sensor
  int moisturePercentage = map(value, DRY_VALUE, WET_VALUE, 0, 100);

  if (moisturePercentage > THRESHOLD_PERCENTAGE) {
    Serial.println("Pôda je dostatočne vlhká => neaktivujem pumpu");
    digitalWrite(RELAY_PIN, LOW);
  } else {
    Serial.println("Pôda je suchá => aktivujem pumpu");
    digitalWrite(RELAY_PIN, HIGH);
    delay(RELAY_DURATION);
    digitalWrite(RELAY_PIN, LOW);
  }
}

void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
