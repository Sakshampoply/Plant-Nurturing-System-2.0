include <SoftwareSerial.h>

const int soilMoisturePin = A0;
const int waterPumpPin = 3;
const int bluetoothTxPin = 10;
const int bluetoothRxPin = 11;

int soilMoistureValue = 0;
int wateringTime = 0;

SoftwareSerial bluetoothSerial(bluetoothRxPin, bluetoothTxPin);

void setup() {
  // Set pin modes
  pinMode(soilMoisturePin, INPUT);
  pinMode(waterPumpPin, OUTPUT);
  
  // Start serial communication
  Serial.begin(9600);
  bluetoothSerial.begin(9600);
}

void loop() {
  soilMoistureValue = analogRead(soilMoisturePin);

  Serial.print("Soil moisture value: ");
  Serial.println(soilMoistureValue);

  if (bluetoothSerial.available()) {
    char command = bluetoothSerial.read();

    switch (command) {
      case 'W':
        digitalWrite(waterPumpPin, HIGH);
        delay(wateringTime);
        digitalWrite(waterPumpPin, LOW);
        break;

      case 'M':
        bluetoothSerial.print("Soil moisture value: ");
        bluetoothSerial.println(soilMoistureValue);
        break;

      case 'T':
        wateringTime = bluetoothSerial.parseInt();
        bluetoothSerial.print("Watering time set to ");
        bluetoothSerial.print(wateringTime);
        bluetoothSerial.println(" ms");
        break;
    }
  }
}
