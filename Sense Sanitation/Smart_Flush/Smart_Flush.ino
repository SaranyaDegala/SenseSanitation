// Pin definitions
const int irSensorPinTap = 5;      // IR sensor for tap
const int tapPin = 13;             // Pin for tap control
const int irSensorPinSoap = 18;    // IR sensor for soap dispenser
const int soapPumpPin = 19;        // Pin for soap pump motor

// Timing variables for sensors and motors
unsigned long tapLastDetection = 0;
unsigned long soapLastDetection = 0;

void setup() {
  Serial.begin(9600);
  
  // Initialize IR sensors and output pins
  pinMode(irSensorPinTap, INPUT);
  pinMode(tapPin, OUTPUT);
  pinMode(irSensorPinSoap, INPUT);
  pinMode(soapPumpPin, OUTPUT);
  
  // Start with tap and soap pump OFF
  digitalWrite(tapPin, LOW);
  digitalWrite(soapPumpPin, LOW);
}

void loop() 
{
  // IR Sensor for Tap
  if (digitalRead(irSensorPinTap) == HIGH) {
    if (millis() - tapLastDetection > 2000) {
      digitalWrite(tapPin, HIGH);  // Turn ON tap after 2 seconds of detection
      Serial.println("Tap ON");
    }
  } else {
    digitalWrite(tapPin, LOW);     // Turn OFF tap when no detection
    tapLastDetection = millis();
    Serial.println("Tap OFF");
  }

  // IR Sensor for Soap Dispenser
  if (digitalRead(irSensorPinSoap) == HIGH) {
    if (millis() - soapLastDetection > 1000) {
      digitalWrite(soapPumpPin, HIGH);  // Turn ON soap pump for 2 seconds
      delay(2000);
      digitalWrite(soapPumpPin, LOW);
      Serial.println("Soap Dispensed");
      soapLastDetection = millis();
    }
  }

  delay(100);  // Small delay for stability
}