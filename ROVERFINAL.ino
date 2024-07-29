#include <BluetoothSerial.h>
#include <Arduino.h>

BluetoothSerial SerialBT;

// BTS7960 motor driver pins for four motors
const int L_PWM_A = 13; // Left PWM pin for Motor A
const int R_PWM_A = 12; // Right PWM pin for Motor A
const int L_PWM_B = 25; // Left PWM pin for Motor B
const int R_PWM_B = 26; // Right PWM pin for Motor B

const int L_PWM_C = 14; // Left PWM pin for Motor C
const int R_PWM_C = 27; // Right PWM pin for Motor C
const int L_PWM_D = 33; // Left PWM pin for Motor D
const int R_PWM_D = 32; // Right PWM pin for Motor D

const int L_EN = 34; // Common Left enable pin
const int R_EN = 35; // Common Right enable pin

int Speed = 130;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32MotorControl"); // Bluetooth device name

  // Set motor control pins as output
  pinMode(L_PWM_A, OUTPUT);
  pinMode(R_PWM_A, OUTPUT);
  pinMode(L_PWM_B, OUTPUT);
  pinMode(R_PWM_B, OUTPUT);
  pinMode(L_PWM_C, OUTPUT);
  pinMode(R_PWM_C, OUTPUT);
  pinMode(L_PWM_D, OUTPUT);
  pinMode(R_PWM_D, OUTPUT);

  pinMode(L_EN, OUTPUT);
  pinMode(R_EN, OUTPUT);

  // Initially, stop all motors
  stopMotors();
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();
    executeCommand(command);
  }
}

void executeCommand(char command) {
  switch (command) {
    case 'F': // Move forward
      moveForward();
      break;
    case 'B': // Move backward
      moveBackward();
      break;
    case 'S': // Stop
      stopMotors();
      break;
    case 'L': // Turn left
      turnLeft();
      break;
    case 'R': // Turn right
      turnRight();
      break;
    // case 'G': // Turn forward left
    //   forwardleft();
      // break;
    // case 'I': // Turn forward right
    //   forwardright();
      // break;
    case '1': 
      Speed = 150;
      break;
    case '2': 
      Speed = 160;
      break;
    case '3': 
      Speed = 170;
      break;
    case '4': 
      Speed = 190;
      break;
    case '5': 
      Speed = 200;
      break;
    case '6': 
      Speed = 210;
      break;
    case '7': 
      Speed = 220;
      break; 
    case '8': 
      Speed = 230;
      break; 
    case '9': 
      Speed = 240;
      break;
    case 'q': 
      Speed = 250;
      break;
  }
}

void moveForward() {
  digitalWrite(L_EN, HIGH);
  digitalWrite(R_EN, HIGH);
  
  analogWrite(L_PWM_A, Speed); // Full speed forward
  analogWrite(R_PWM_A, 0);
  analogWrite(L_PWM_B, Speed); // Full speed forward
  analogWrite(R_PWM_B, 0);
  analogWrite(L_PWM_C, Speed); // Full speed forward
  analogWrite(R_PWM_C, 0);
  analogWrite(L_PWM_D, Speed); // Full speed forward
  analogWrite(R_PWM_D, 0);
}

void moveBackward() {
  digitalWrite(L_EN, HIGH);
  digitalWrite(R_EN, HIGH);
  
  analogWrite(L_PWM_A, 0); // Full speed backward
  analogWrite(R_PWM_A, Speed);
  analogWrite(L_PWM_B, 0); // Full speed backward
  analogWrite(R_PWM_B, Speed);
  analogWrite(L_PWM_C, 0); // Full speed backward
  analogWrite(R_PWM_C, Speed);
  analogWrite(L_PWM_D, 0); // Full speed backward
  analogWrite(R_PWM_D, Speed);
}

void turnLeft() {
  digitalWrite(L_EN, HIGH);
  digitalWrite(R_EN, HIGH);
  
  analogWrite(L_PWM_A, Speed); // Full speed turnRight
  analogWrite(R_PWM_A, 0);
  analogWrite(L_PWM_B, 0); // Full speed turnRight
  analogWrite(R_PWM_B, Speed);
  analogWrite(L_PWM_C, Speed); // Full speed turnRight
  analogWrite(R_PWM_C, 0);
  analogWrite(L_PWM_D, 0); // Full speed turnRight
  analogWrite(R_PWM_D, Speed);
}

void turnRight() {
  digitalWrite(L_EN, HIGH);
  digitalWrite(R_EN, HIGH);
  
  analogWrite(L_PWM_A, 0); // Full speed turnRight
  analogWrite(R_PWM_A, Speed);
  analogWrite(L_PWM_B, Speed); // Full speed turnRight
  analogWrite(R_PWM_B, 0);
  analogWrite(L_PWM_C, 0); // Full speed turnRight
  analogWrite(R_PWM_C, Speed);
  analogWrite(L_PWM_D, Speed); // Full speed turnRight
  analogWrite(R_PWM_D, 0);
}

// void forwardleft() {
//   digitalWrite(L_EN, HIGH);
//   digitalWrite(R_EN, HIGH);
  
//   analogWrite(L_PWM_A, 0); // Full speed forward
//   analogWrite(R_PWM_A, 120);
//   analogWrite(L_PWM_B, 0); // Full speed forward
//   analogWrite(R_PWM_B, 120);
//   analogWrite(L_PWM_C, Speed); // Full speed forward
//   analogWrite(R_PWM_C, 0);
//   analogWrite(L_PWM_D, Speed); // Full speed forward
//   analogWrite(R_PWM_D, 0);
// }

// void forwardright() {
//   digitalWrite(L_EN, HIGH);
//   digitalWrite(R_EN, HIGH);
  
//   analogWrite(L_PWM_A, Speed); // Full speed forward
//   analogWrite(R_PWM_A, 0);
//   analogWrite(L_PWM_B, Speed); // Full speed forward
//   analogWrite(R_PWM_B, 0);
//   analogWrite(L_PWM_C, 0); // Full speed forward
//   analogWrite(R_PWM_C, 120);
//   analogWrite(L_PWM_D, 0); // Full speed forward
//   analogWrite(R_PWM_D, 120);
// }

void stopMotors() {
  digitalWrite(L_EN, LOW); // Disable motors
  digitalWrite(R_EN, LOW);

  analogWrite(L_PWM_A, 0); // Stop motor A
  analogWrite(R_PWM_A, 0);
  analogWrite(L_PWM_B, 0); // Stop motor B
  analogWrite(R_PWM_B, 0);
  analogWrite(L_PWM_C, 0); // Stop motor C
  analogWrite(R_PWM_C, 0);
  analogWrite(L_PWM_D, 0); // Stop motor D  
  analogWrite(R_PWM_D, 0);
}
