// Ocolire intuitiva a obstacolului, merge pe traseu

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
unsigned int sensors[5];



#include <avr/pgmspace.h> //store in program space 16kb

OrangutanMotors ms;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);

  unsigned int counter;
  robot.init(2000);

   while(!OrangutanPushbuttons::isPressed(BUTTON_B)) 
  {};
 OrangutanPushbuttons::waitForRelease(BUTTON_B);
  delay(1000);

   for (counter=0; counter<80; counter++)
  {
    if (counter < 20 || counter >= 60)
      OrangutanMotors::setSpeeds(40, -40);
    else
      OrangutanMotors::setSpeeds(-40, 40);
      
    robot.calibrateLineSensors(IR_EMITTERS_ON);
    
    delay(20);
  }
 //Serial.begin(9600);
  OrangutanMotors::setSpeeds(0, 0);
   while(!OrangutanPushbuttons::isPressed(BUTTON_B)) 
  {};
  OrangutanPushbuttons::waitForRelease(BUTTON_B);

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
  delay(105);
  OrangutanMotors::setSpeeds(0,0);
  delay(100);
}
void corner_left(){
  OrangutanMotors::setSpeeds(100,-100);
  delay(105);
  OrangutanMotors::setSpeeds(0,0);
  delay(100);
}
void ahead(int time){
  OrangutanMotors::setSpeeds(-105,-100);
  delay(time);
  OrangutanMotors::setSpeeds(0,0);
  delay(100);
}

void avoid_obstacle(){
  corner_right();
  //corner_left();
  ahead(300);
  corner_left();
  ahead(750);
  corner_left();
  ahead(300);
  corner_right();
}

void follow_segment()
{
  int last_proportional = 0;
  long integral=0;
  int timer=0;

  for(timer=0;timer<100;timer++)
  {
    unsigned int position = robot.readLine(sensors, IR_EMITTERS_ON);

    
    int proportional = ((int)position) - 2000;

    
    int derivative = proportional - last_proportional;
    integral += proportional;

   
    last_proportional = proportional;

   
    int power_difference = proportional/20 + integral/10000 + derivative*3/2;

    
    const int maximum = 60; 
    if (power_difference > maximum)
      power_difference = maximum;
    if (power_difference < -maximum)
      power_difference = -maximum;

    if (power_difference < 0)
      OrangutanMotors::setSpeeds(-(maximum + power_difference), -maximum);
    else
      OrangutanMotors::setSpeeds(-maximum, -(maximum - power_difference));

      }
}

void loop() {
  follow_segment();
 detect_distance();
  if (cm<11)
  avoid_obstacle();
  
  //else OrangutanMotors::setSpeeds(-50,-50);
 
}
