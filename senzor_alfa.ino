#define RELAY_PIN    13 
#define MOISTURE_PIN 34 
#define THRESHOLD 2800   

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  int value = analogRead(MOISTURE_PIN); 

  if (value > THRESHOLD) {
    Serial.print("Pôda je suchá  => aktivujem pumpu");
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    Serial.print("Pôda je mokrá => Vypínam pumpu ");
    digitalWrite(RELAY_PIN, LOW);
  }

  Serial.print(" (");
  Serial.print(value);
  Serial.println(")");

  delay(10000);
}

//sucha hodnota: 4095
//mokra hodnota: 1500
