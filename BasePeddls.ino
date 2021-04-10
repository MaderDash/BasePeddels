/*
  made by: Maderdash
  www.twitch.tv/maderdash

  Base pedel controlled servos for musical keyboard.
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
uint8_t servonum = 0; // all 16 servos acessable
int set_low = 188;
int set_norm = 270;
int set_high = 350;
int test_array[] = {set_low, set_norm, set_high};
int button = 6;
int button_two = 5;
int button_read = 0;
int x = 0;
int button_1[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int Servo_s[] = {188, 350, 188, 350, 188, 350, 188, 350, 188, 350, 188, 350};
int Array[12] = {};


void setup() {
  Serial.begin(9600);
  Serial.println("Base Peddel Alpha test");
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);
  for (int i = 0; i < 12; i++) {
    pinMode(button_1[i] , INPUT_PULLUP);
  }
  Selph_test();
}
//System test for each servo, high,low, then middle.
void Selph_test() {
  Serial.println("Starting self test please wait.");
  Serial.println("");
  for (int i = 0; i < 12; i++) {
    int x = i / 2;
    pwm.setPWM(x, 0, Servo_s[i]);
    Serial.print("Servo");
    Serial.print(i);
    delay(1000);
    Serial.println("");
  }
  for (int i = 0; i < 12; i++) {
    pwm.setPWM(x, 0, 270);
  }
  Serial.print("Selph test all done.");
}

void loop() {
  // Drive each servo one at a time using setPWM()

  for (int i = 0; i < 12; i++) {
    
    Array[i] = digitalRead(button_1[i]);
  }
  for (int i = 0; i < 12; i++) {
    int x = i / 2;
    if (Array[i] == LOW) {
      pwm.setPWM(x, 0, Servo_s[i]);
    }
    else
    {
      pwm.setPWM(i, 0, 270);
    }
  }

}

/* Arduino pins 2-13 switch pins, normaly high from inturnal pullups.
Pins A5 SCL, pin A4 SDA.
Possable LED strip on pins A0, A1.

 Servo0= button 0 1
 Servo1= button 2 3
 Servo2= button 4 5
 Servo3= button 6 7
 Servo4= button 8 9
 Servo5= button 10 11
*/
