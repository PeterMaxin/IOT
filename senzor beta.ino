nt _moisture,sensor_analog;
const int sensor_pin = A0;  

void setup(void){
  Serial.begin(115200);    
}

void loop(void){
  sensor_analog = analogRead(sensor_pin);
  _moisture = ( 100 - ( (sensor_analog/4095.00) * 100 ) );
  Serial.print("Moisture = ");
  Serial.print(_moisture); 
  Serial.println("%");
  delay(1000);              
}