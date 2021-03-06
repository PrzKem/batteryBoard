#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

const int mosfets[] = {18,5,17,4,2};
const int numOfMosfets = sizeof(mosfets)/sizeof(mosfets[0]);

void setup(void) 
{
  Serial.begin(115200);

  for(int i=0;i<numOfMosfets;i++)
  {
    pinMode(mosfets[i], OUTPUT);
    digitalWrite(mosfets[i], LOW);
  }

  if (! ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }
}

void readValues()
{
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("");
}

void loop() {
  for(int i=0;i<numOfMosfets;i++)
  {
    digitalWrite(mosfets[i], HIGH);
    delay(500);
    
    Serial.println("\n");
    Serial.print("MOSFET: ");
    Serial.println(mosfets[i]);
    
    readValues();
    delay(100);
    
    digitalWrite(mosfets[i], LOW);
    delay(100);
  }
}
