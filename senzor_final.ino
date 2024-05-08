#define RELAY_PIN    13 // ESP32 pin GPIO17 that connects to relay
#define MOISTURE_PIN 34 // ESP32 pin GPIO36 (ADC0) that connects to AOUT pin of moisture sensor
#define THRESHOLD 2800   // => CHANGE YOUR THRESHOLD HERE

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  
  int value = analogRead(MOISTURE_PIN); // read the analog value from soild moisture sensor

  if (value > THRESHOLD) {
    Serial.print("Pôda je suchá  => aktivujem pumpu");
    int s=0;
    while (s<10){
      digitalWrite(RELAY_PIN, HIGH);
      delay(100);
      s=s+1;
    }
    digitalWrite(RELAY_PIN, LOW);
  } else {
    Serial.print("Pôda je mokrá => Vypínam pumpu ");
    digitalWrite(RELAY_PIN, LOW);
    
    
  }

  Serial.print(" (");
  Serial.print(value);
  Serial.println(")");

  delay(20000);
}

//sucha hodnota: 4095
//mokra hodnota: 1500