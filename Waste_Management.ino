#include <Servo.h>
#include <NewPing.h>


#define moistureSensorPin 3
#define metalSensorPin 2


const int servo1Pin = 9;
const int servo2Pin = 5;


Servo servo1;
Servo servo2;

#define trigPin 12
#define echoPin 11
#define MAX_DISTANCE 200

int moistureValue = 1;
int metalValue = 1;

int pos;


NewPing sonar(trigPin, echoPin, MAX_DISTANCE);
float distance;


//threshold

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(moistureSensorPin, INPUT);
  pinMode(metalSensorPin, INPUT);

  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);


  servo1.write(40);
  servo2.write(95);

}


void loop() {

  distance = sonar.ping_cm();

    if(distance <= 7.5 && distance > 0.5)
  {
    Serial.println("Object detected!");
   delay(1000);
  metalValue = digitalRead(metalSensorPin);
  delay(1000);
    if(metalValue == HIGH)
    {
      servo2.write(0);
      delay(2000);
      servo1.write(0);
      delay(2000);
    }
    
    else
    { 
      
      servo1.write(80);
      delay(1000);
        moistureValue = digitalRead(moistureSensorPin);
        Serial.println(moistureValue);
      delay(1000);
      if(moistureValue == LOW)
      {
        Serial.println("WET");
        servo2.write(150);
        delay(2000);
        servo1.write(135);
        delay(2000);
           
      }
      else
      {
        Serial.println("DRY");
        servo2.write(95);
        delay(2000);
        servo1.write(125);
        delay(2000);
      }  
    }
  }
  else
  {
    Serial.println("object not detected");
  }


 
  servo1.write(40);
  servo2.write(95);
  delay(500);
}
