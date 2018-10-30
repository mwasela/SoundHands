//connection for rf receiver
//GND = GND
//DATA = 12
//VCC = 5V

#include <VirtualWire.h>
//connection for motors
//motor one
int enA = 10;
int in1 = 9;
int in2 = 8;
// motor two
int enB = 11;
int in3 = 7;
int in4 = 6;
void setup()
{
vw_set_ptt_inverted(true); // Required for DR3100
vw_set_rx_pin(12);
vw_setup(4000); // Bits per sec
//pinMode(13, OUTPUT);
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);
vw_rx_start(); // Start the receiver PLL running
}
void loop()
{
uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = 2;
if (vw_get_message(buf, &buflen)) // Non-blocking
{
  
  Serial.print(buf[0]) ;
  Serial.println(buf[1]);
  if(buf[0]=='f'){
  Serial.print("forward");
  Serial.println(buf[1]);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA,255);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB,255);
  }
  if(buf[0]=='b')  {
  Serial.print("backward");
  Serial.println(buf[1]);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA,255);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB,255);
}
  if(buf[0]=='s'){
  Serial.print("stop");
  Serial.println(buf[1]);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA,255);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enB,255);
}
if(buf[0]=='l'){
  Serial.print("left");
  Serial.println(buf[1]);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA,255);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB,255);
}
if(buf[0]=='r'){
  Serial.print("right");
  Serial.println(buf[1]);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA,255);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB,255);
}

}
}
