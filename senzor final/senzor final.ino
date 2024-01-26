#define MOISTURE_PIN 4
int WET_VALUE = 2400;  // Hodnota úplne mokrého senzora
int DRY_VALUE = 4095; // Hodnota úplne suchého senzora
int ledNum = 5; // Počet LEDiek
int step = (DRY_VALUE - WET_VALUE)/ledNum; //Vypočítanie jedného kroku (podľa počtu LEDiek)
int myPins[5] = {13, 26, 32, 23, 19}; //Pole s pinami čo sa používajú


void setup() {
  Serial.begin(9600);
  for (int i = 0; i < ledNum; i++){ //Zapíname všetky potrebné piny
    pinMode(myPins[i], OUTPUT);
  }
}

void loop() {
  int timesContains = 0; // Ideme od -1 kvôli cyklu ktorý zapína LEDky. Ak by sme išli od 0, prvá LEDka by sa zapla, aj keď by sa nemala, lebo je 0-tá v poli (išli by sme od 0 do 0, t.j. vrátane nuly)
  int value = analogRead(MOISTURE_PIN);
  value = DRY_VALUE - value;

  for(int i = 1; ; i++) // ideme od 1 kvôli tomu, že step * 0 bude stále väčšie ako akékoľvek kladné číslo.
  {
    if(value - (step * i) >= 0) // Dokiaľ je nameraná hodnota - (krok * i [premenná v cykle]) väčšia alebo rovná ako 0, pripočítava sa k
    {
      timesContains++;
    }
    else
    {
      break; //Vyjde sa z cyklu keď by nameraná hodnota bola menšia ako krok
    }
  }
  
  for (int i = 0; i < timesContains; i++){
    digitalWrite(myPins[i], HIGH); //Zapneme toľko pinov z poľa deklarovaného vyššie, koľko sme napočítali vyššie
  }
  for(int i = timesContains; i < ledNum; i++)
  {
    digitalWrite(myPins[i], LOW); //Všetky ostatné piny musíme vypnúť, aby stále nesvietili
  }

  Serial.print(" (");
  Serial.print(value);
  Serial.println(")");
}