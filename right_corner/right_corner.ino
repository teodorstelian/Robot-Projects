#include <Pololu3pi.h>
#include <PololuQTRSensors.h>
#include <OrangutanMotors.h>
#include <OrangutanAnalog.h>
#include <OrangutanLEDs.h>
#include <OrangutanLCD.h>
#include <OrangutanPushbuttons.h>
#include <OrangutanBuzzer.h>

Pololu3pi robot;
const int TRIG_PIN = 7;
const int ECHO_PIN = 8;
const unsigned int MAX_DIST = 23200; //max range
float cm=500;


#include <avr/pgmspace.h> //store in program space 16kb

OrangutanMotors ms;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);

   while(!OrangutanPushbuttons::isPressed(BUTTON_B)) 
  {};
 OrangutanPushbuttons::waitForRelease(BUTTON_B);
  delay(1000);

}

void detect_distance(){
  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;

  // Hold the trigger pin high for at least 10 us
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Wait for pulse on echo pin
  while ( digitalRead(ECHO_PIN) == 0 );

  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while ( digitalRead(ECHO_PIN) == 1);
  t2 = micros();
  pulse_width = t2 - t1;

  // Calculate distance in centimeters and inches. The constants
  // are found in the datasheet, and calculated from the assumed speed 
  //of sound in air at sea level (~340 m/s).
  cm = pulse_width / 58.0;
  
    // Print out results
  if ( pulse_width > MAX_DIST ) {
    cm=500;
  } 
  
}

void corner_right(){
  OrangutanMotors::setSpeeds(-100,100);
  delay(120);
  OrangutanMotors::setSpeeds(0,0);
  delay(100);
}
void corner_left(){
  OrangutanMotors::setSpeeds(100,-100);
  delay(120);
  OrangutanMotors::setSpeeds(0,0);
  delay(100);
}
void ahead(int time){
  OrangutanMotors::setSpeeds(-100,-100);
  delay(time);
  OrangutanMotors::setSpeeds(0,0);
  delay(100);
}

void avoid_obstacle(){
  corner_right();
  //corner_left();
  ahead(300);
  corner_left();
  ahead(1000);
  corner_left();
  ahead(300);
  corner_right();
}

void loop() {
 detect_distance();
  if (cm<11)
  avoid_obstacle();
  else OrangutanMotors::setSpeeds(-50,-50);
 
}
