//connection for DNPU6
//VCC = 3.3/5v
//GND = GND
//SCL = 3
//SDA = 2
//INT = 7

//connection for transmitter
//DATA=12
//VCC=5V
//GND=GND

#include <VirtualWire.h>
char *controller;
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
void setup() 
{
  pinMode(13,OUTPUT);
  vw_set_ptt_inverted(true); //
  vw_set_tx_pin(12);
  vw_setup(4000);// speed of data transfer Kbps
  Serial.begin(9600);
 
  Serial.println("Initialize MPU6050");

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
}

void loop()
{
  // Read normalized values 
  Vector normAccel = mpu.readNormalizeAccel();

  // Calculate Pitch & Roll
  int pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;
  int roll = (atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI;

    Serial.print(" \nPitch = ");
    Serial.print(pitch);
    Serial.print(" Roll = ");
    Serial.print(roll);
    
   if( pitch > 30){
    controller="f" ;
    vw_send((uint8_t *)controller, strlen(controller));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, HIGH);
    delay(200);
     }   
     else if( pitch < -30){
    controller="b" ;
    vw_send((uint8_t *)controller, strlen(controller));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, LOW);
    delay(200);
     }   
     else if(roll > 30){
    controller="r" ;
    vw_send((uint8_t *)controller, strlen(controller));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, HIGH);
    delay(200);
     }   
     else if(roll < -30){
    controller="l" ;
    vw_send((uint8_t *)controller, strlen(controller));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, LOW);
    delay(200);
     }
      else {
      controller="s" ;
      vw_send((uint8_t *)controller, strlen(controller));
      vw_wait_tx(); // Wait until the whole message is gone  
      delay(200); 
      digitalWrite(13, LOW);
     } 
  
  delay(10);
}


