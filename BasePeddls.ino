/*
  PCA9685-16Channel-12bit-PWM-Servo-Driver
  modified on 16 Dec 2020
  by Amir Mohammad Shojaee @ Electropeak
  https://electropeak.com/learn/

  based on Arduino - Adafruit library
*/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  110 // This is the 'minimum' pulse length count (out of 4096) [ZERO DEGREES]
#define SERVOMAX  430 // This is the 'maximum' pulse length count (out of 4096) [180 DEGREES]
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// our servo # counter
uint8_t servonum = 16; // all 16 servos acessable
int set_low = 188;
int set_norm = 270;
int set_high = 350;
int test_array[] = {set_low, set_norm, set_high};
int button = 6;
int button_two = 5;
int button_read = 0;
int x = 0;
int button_1[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int i = 0;
int Servo_s[] = {188, 350, 188, 350, 188, 350, 188, 350, 188, 350, 188, 350};
int Array[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//int  set_low = (SERVOMAX - SERVOMIN)/2;





void setup() {
  Serial.begin(9600);
  Serial.println("4 channel Servo test!");

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  Serial.begin(9600);
  delay(10);
  for (int i = 0; i < 12; i++) {
    pinMode(button_1[i] , INPUT_PULLUP);
  }

}

// You can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. It's not precise!
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;

  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= SERVO_FREQ;   // Analog servos run at ~60 Hz updates
  Serial.print(pulselength); Serial.println(" us per period");
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit");
  pulse *= 1000000;  // convert input seconds to us
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

void loop() {
  // Drive each servo one at a time using setPWM()




  for (int i = 0; i < 11; i++) {
    Array[i] = digitalRead(button_1[i]);
  }
  delay(5);
  for (int i = 0; i < 11; i++) {
    int x = i / 2;
    Serial.print("this is x:::::::.......");
    Serial.println(x);
    if (Array[i] == 0) {
      pwm.setPWM(x, 0, Servo_s[i]);
    }
    else {
      pwm.setPWM(i, 0, 270);

    }
    Serial.println("");
    
  }
delay(100);
}
  
  // Servo0= button0 1
  // Servo1= button2 3
  // Servo2= button4 5
  // Servo3= button6 7
  // Servo4= button8 9
  // Servo5= button10 11
  /*
    button_read = digitalRead(button);
    if (button_read == 1;){
    button_read = digitalRead(button_two);
    }



    if (button_read == 0) {
      x = set_low;
      Serial.println("button is pressed");
    }
    else {
      x = set_high;
      Serial.println("button is not pressed");
    }
    for (int i = 0; i < 3; i++) {
      pwm.setPWM(i, 0, x);
      delay(500);
    }

    }












    for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
      pwm.setPWM(servonum, 0, pulselen);
      Serial.println(set_low);
      delay(10);
    }

    delay(500);
    for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
      pwm.setPWM(servonum, 0, pulselen);
    }
    delay(500);

    servonum++;
    if (servonum > 2) servonum = 0; // Testing the first 4 servo channels
    }
  */
