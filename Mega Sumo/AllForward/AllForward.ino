int IN1A = D3; //M1INA
int IN1B = D4; //M1INB
int ENA = D9;
int PWM1 = A6;
int IN2A = D5;   //M2INA
int IN2B = D6;   //M2INB
int PWM2 = A2;
// SCL = A5 && SDA = A4

int STARTSTOP = A3;
int VSTART = 0;

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

}

void loop() {
    VSTART = digitalRead(STARTSTOP);
    while(VSTART) {
    StartUp();
    Forward(255,255);
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
