#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// nRF24L01 pin config
#define CE_PIN 7
#define CSN_PIN 8

RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "00001";

// Received data
unsigned char Rx_Array[2];
unsigned char Direction = 0;
unsigned char Speed_index = 0;

// L298N Motor Driver Pins
#define ENA 3    // PWM
#define IN1 4
#define IN2 5

#define ENB 6    // PWM
#define IN3 9
#define IN4 10

int SpeedLookup[6] = {0, 80, 120, 150, 180, 220}; // Map index to PWM

void setup() {
  Serial.begin(115200);

  // Motor pin setup
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  stopMotors();

  // nRF24 setup
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS); // optional, more stable
  radio.openReadingPipe(0, address);
  radio.startListening();

  Serial.println("Nano Receiver Ready");
}

void loop() {
  if (radio.available()) {
    radio.read(&Rx_Array, 2);
    Direction = Rx_Array[0];
    Speed_index = Rx_Array[1];

    Serial.print("Dir: "); Serial.print(Direction);
    Serial.print(" | Speed Index: "); Serial.println(Speed_index);

    controlMotors(Direction, Speed_index);
  }
}

void controlMotors(uint8_t dir, uint8_t speedIndex) {
  int pwm = SpeedLookup[constrain(speedIndex, 0, 5)];

  switch (dir) {
    case 1: // Forward
      digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
      analogWrite(ENA, pwm); analogWrite(ENB, pwm);
      break;

    case 2: // Backward
      digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
      analogWrite(ENA, pwm); analogWrite(ENB, pwm);
      break;

    case 3: // Left
      digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
      analogWrite(ENA, pwm); analogWrite(ENB, pwm);
      break;

    case 4: // Right
      digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
      analogWrite(ENA, pwm); analogWrite(ENB, pwm);
      break;

    default: // Stop
      stopMotors();
      break;
  }
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); analogWrite(ENB, 0);
}
