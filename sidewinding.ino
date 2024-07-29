#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Create the PWM driver object
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

float pi = 3.14159;
int TotalNumberofServos = 8; // change as required
int ServosPerSide = TotalNumberofServos / 2;
float shift = 2 * pi / ServosPerSide; // Phase lag between segments
int amplitude = 50;
int offset = 0;
float rads;
float Speed = 2;
float Wavelengths = 1.5;

// These values are specific to the Adafruit PWM driver
#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
}

// Function to convert degrees to PWM pulse length
int degreeToPulse(int degree) {
  return map(degree, 0, 180, SERVOMIN, SERVOMAX);
}

void forwardMotion(){
  for(int i = 0; i < 360; i++){
    rads = i * pi / 180.0;  // convert from degrees to radians
    for(int j = 0; j < 4; j++){  
//      int verticalServoAngle = 90 + offset + amplitude * sin(Speed * rads + j * Wavelengths * shift);
//      int horizontalServoAngle = 90 + offset + amplitude * sin(Speed * rads + j * Wavelengths * shift + pi / 2);

      int verticalServoAngle = 90 + offset + amplitude * sin(Speed * rads + j * Wavelengths * shift);
      int horizontalServoAngle = 90 + offset + amplitude * cos(Speed * rads + j * Wavelengths * shift);


      pwm.setPWM(2 * j, 0, degreeToPulse(verticalServoAngle));   // moves servos in vertical plane
      pwm.setPWM(2 * j + 1, 0, degreeToPulse(horizontalServoAngle)); // moves servos in horizontal plane
    }
    delay(10);
  }
}

void loop() {
  // comment and uncomment for the movement you want
  // as mentioned in the instructable, this code is skeletal in that there is no remote control function, stay tuned for version 2

  forwardMotion();
  // strike();
}
