int IN1A = D3; //M1INA
int IN1B = D4; //M1INB
int ENA = D9;
int PWM1 = A6;
int IN2A = D5;   //M2INA
int IN2B = D6;   //M2INB
int PWM2 = A2;

int LIN1 = D2; //Fatastanga
int LIN2 = D10; //Fatadreapta
int LIN3 = D11; //Spatestanga
int LIN4 = D12; //Spatedreapta
int VLIN1 = 1;
int VLIN2 = 1;
int VLIN3 = 1;
int VLIN4 = 1;

int STARTSTOP = A3;
int VSTART = 0;

float US_C = 0.034/2;

void setup() {
 Serial.begin(9600);

 pinMode(STARTSTOP,INPUT);
 pinMode(IN1A,OUTPUT);
 pinMode(IN1B,OUTPUT);
 pinMode(ENA,OUTPUT);
 pinMode(PWM1,OUTPUT);
 pinMode(IN2A,OUTPUT);
 pinMode(IN2B,OUTPUT);
 pinMode(PWM2,OUTPUT);
 pinMode(LIN1,INPUT);
 pinMode(LIN2,INPUT);
 pinMode(LIN3,INPUT);
 pinMode(LIN4,INPUT);

}


void loop() {
   VSTART = digitalRead(STARTSTOP);
    while(VSTART) {
    StartUp();
    //Forward(255,255);
    Line();
   VSTART = digitalRead(STARTSTOP);
    while(VSTART == 0)
    {
     ShutDown();
    }
    }
}

void StartUp () 
{
  digitalWrite(ENA,HIGH);
}

void ShutDown ()
{
  digitalWrite(ENA,LOW);
}

void Backward(int a,int b)
{
digitalWrite(IN1A,LOW);
digitalWrite(IN1B,HIGH);
digitalWrite(PWM1,a);
digitalWrite(IN2A,LOW);
digitalWrite(IN2B,HIGH);
digitalWrite(PWM2,b);
}

void Forward(int a,int b)
{
digitalWrite(IN1A,HIGH);
digitalWrite(IN1B,LOW);
digitalWrite(PWM1,a);
digitalWrite(IN2A,HIGH);
digitalWrite(IN2B,LOW);
digitalWrite(PWM2,b);
}

void RotateLeft(int a,int b)
{
digitalWrite(IN1A,LOW);
digitalWrite(IN1B,HIGH);
digitalWrite(PWM1,a);
digitalWrite(IN2A,HIGH);
digitalWrite(IN2B,LOW);
digitalWrite(PWM2,b);

}
void RotateRight(int a,int b)
{
digitalWrite(IN1A,HIGH);
digitalWrite(IN1B,LOW);
digitalWrite(PWM1,a);
digitalWrite(IN2A,LOW);
digitalWrite(IN2B,HIGH);
digitalWrite(PWM2,b); 
}

void ReadSensorsLine()
{
VLIN1 = digitalRead(LIN1);
VLIN2 = digitalRead(LIN2);
VLIN3 = digitalRead(LIN3);
VLIN4 = digitalRead(LIN4);
}

void Line()
{
ReadSensorsLine();
Forward(255,255);
if(VLIN1 == 1 && VLIN3 == 1 && VLIN4 == 1) {Forward(255,255);}
if(VLIN1 == 0) {Backward(255,255); VLIN1=1; VLIN3=1; VLIN4=1;  delay(300); RotateRight(255,255); delay(200);}
if(VLIN3 == 0) {Backward(255,255); VLIN1=1; VLIN3=1; VLIN4=1;  delay(300); RotateRight(255,255); delay(200);}
if(VLIN4 == 0) {Backward(255,255); VLIN1=1; VLIN3=1; VLIN4=1;  delay(300); RotateLeft(255,255); delay(200);}
if (VLIN1 == 1 && VLIN3 == 1 && VLIN4 == 1) {Forward(255,255);}
ReadSensorsLine();
}
