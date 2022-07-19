#define motorA 6
#define motorB 9
int encoderPin1 = 2;
int encoderPin2 = 3;
volatile int lastEncoded = 0;
volatile long encoderValue = 0;
volatile long correctEncoderValue =0;
 
long lastencoderValue = 0;
 
int lastMSB = 0;
int lastLSB = 0;

void setup() {
   Serial.begin (9600);
   pinMode(encoderPin1, INPUT);
   pinMode(encoderPin2, INPUT);
   digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
   digitalWrite(encoderPin2, HIGH); //turn pullup resistor on
   attachInterrupt(0, updateEncoder, CHANGE);
   attachInterrupt(1, updateEncoder, CHANGE);
  
   pinMode(motorA,OUTPUT);
   pinMode(motorB,OUTPUT);
}

void loop() {
   correctEncoderValue = encoderValue/4;
  
   Serial.println(correctEncoderValue);
  
  if ( 0<=correctEncoderValue && correctEncoderValue < 3000) {
   analogWrite(motorA,127);
   digitalWrite(motorB,LOW);
  } else {
   analogWrite(motorA,0);
   digitalWrite(motorB,LOW);
  }
   delay(100);

}
void updateEncoder(){
  int MSB = digitalRead(encoderPin1); 
  int LSB = digitalRead(encoderPin2); 
  int encoded = (MSB << 1) |LSB; 
  int sum  = (lastEncoded << 2) | encoded; 
 
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;
 
  lastEncoded = encoded; 
}
