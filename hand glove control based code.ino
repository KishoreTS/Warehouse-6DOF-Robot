#include<Wire.h>
#include <Servo.h>

Servo myservo;
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

// flex sensor1 code
int pinkie = 0; 
int pinkie_Data = A0;
int pinkie_high = 0;
int pinkie_low = 0;

bool bool_caliberate = false;

const int MPU2 = 0x69, MPU1 = 0x68;

int16_t AcX1, AcY1, AcZ1, Tmp1, GyX1, GyY1, GyZ1;

int minVal = 265;
int maxVal = 402;

double x;
double y;
double z;

const int servo_joint_1_parking_pos = 70;
const int servo_joint_2_parking_pos = 40;
const int servo_joint_3_parking_pos = 60;
const int servo_joint_4_parking_pos = 60;
const int servo_joint_5_parking_pos = 60;

int servo_joint_1_pos_increment = 10;
int servo_joint_2_pos_increment = 10;
int servo_joint_3_pos_increment = 20;
int servo_joint_4_pos_increment = 20;
int servo_joint_5_pos_increment = 10;

int servo_joint_1_parking_pos_i = servo_joint_1_parking_pos;
int servo_joint_2_parking_pos_i = servo_joint_2_parking_pos;
int servo_joint_3_parking_pos_i = servo_joint_3_parking_pos;
int servo_joint_4_parking_pos_i = servo_joint_4_parking_pos;
int servo_joint_5_parking_pos_i = servo_joint_5_parking_pos;

int servo_joint_1_min_pos = 0;
int servo_joint_1_max_pos = 130;
int servo_joint_2_min_pos = 10;
int servo_joint_2_max_pos = 380;
int servo_joint_3_min_pos = 10;
int servo_joint_3_max_pos = 180;
int servo_joint_4_min_pos = 10;
int servo_joint_4_max_pos = 180;
int servo_joint_5_min_pos = 10;
int servo_joint_5_max_pos = 360;

int servo_joint_1_pos = 0;
int servo_joint_2_pos = 0;
int servo_joint_3_pos = 0;
int servo_joint_4_pos = 0;
int servo_joint_5_pos = 0;

int response_time_1 = 10;
char state = 0; // Changes value from ASCII to char
int response_time = 5;
int response_time_4 = 3;
int loop_check = 0;
int response_time_fast = 20;
int action_delay = 600;

void setup() {
 
  myservo.attach(11);
  myservo1.attach(10);
  myservo2.attach(9);
  myservo3.attach(8);// y axis wrist pitch
  myservo4.attach(7);// x axis waist
  Wire.begin();
  Wire.beginTransmission(MPU1);
  Wire.write(0x6B);// PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true); 
  delay(1000);

}
void loop() {
  //get values for first mpu having address of 0x68
  GetMpuValue1(MPU1);
  delay(10);
  if ( x > 15 && x < 55 ) {
    servo1();
    delay(response_time_1);
  }
  if ( x < 310 && x > 270) {
    servo1return();
    delay(response_time_1);
  }
   if ( y > 60 && y < 80) {
    servo2();
    delay(response_time_1);
  }
  if ( y < 310 && y > 270) {
    servo2return();
    delay(response_time_1);
  }
  
  // flex sensor 1
  pinkie = analogRead(pinkie_Data);
  
if (bool_caliberate == false ) {
    delay(1000);
 pinkie_high = (pinkie * 1.02);
 pinkie_low = (pinkie * 1.1);

    bool_caliberate = true;
  }
  if (pinkie >= 136) {
    servo3();
    delay(response_time_1);

  }
  if (pinkie <= 128 ) {
    servo3return();
    delay(response_time_1);
  }
  if(  y < 230 && y > 190 )
  { 
    servo4();
    delay(response_time_1);
    }
    if(  y < 160 && y > 140 )
  { 
    servo4return();
    delay(response_time_1);
    }
     if(  x < 150 && x > 130 )
  { 
    servo5();
    delay(response_time_1);
    }
     if(  x < 200 && x > 190 )
  { 
    servo5return();
    delay(response_time_1);
    }
  Serial.print(pinkie);  
  Serial.print("\t");
  
  Serial.print(pinkie_high);
  Serial.print("\t");

  Serial.print(pinkie_low);
  Serial.print("\t");
  Serial.println("check");
}
void servo1(){
   if (servo_joint_1_parking_pos_i < servo_joint_1_max_pos) {
    myservo.write( servo_joint_1_parking_pos_i);
    delay(response_time_1);
    Serial.println(servo_joint_1_parking_pos_i);

    servo_joint_1_parking_pos_i = servo_joint_1_parking_pos_i + servo_joint_1_pos_increment;

  }
}
void servo1return(){
   if (servo_joint_1_parking_pos_i > servo_joint_1_min_pos) {
    myservo.write(servo_joint_1_parking_pos_i);
    delay(response_time_1);
    Serial.println(servo_joint_1_parking_pos_i);

    servo_joint_1_parking_pos_i = servo_joint_1_parking_pos_i - servo_joint_1_pos_increment;

  }
}
  void servo2(){
     if (servo_joint_2_parking_pos_i < servo_joint_2_max_pos) {
    myservo1.write( servo_joint_2_parking_pos_i);
    delay(response_time_4);
    Serial.println(servo_joint_2_parking_pos_i);

    servo_joint_2_parking_pos_i = servo_joint_2_parking_pos_i + servo_joint_2_pos_increment;

   }
}
void servo2return(){
   if (servo_joint_2_parking_pos_i > servo_joint_2_min_pos) {
    myservo1.write(servo_joint_2_parking_pos_i);
    delay(response_time_4);
    Serial.println(servo_joint_2_parking_pos_i);

    servo_joint_2_parking_pos_i = servo_joint_2_parking_pos_i - servo_joint_2_pos_increment;

  }
}
void servo3() {

  if (servo_joint_3_parking_pos_i > servo_joint_3_min_pos) {
    myservo2.write( servo_joint_3_parking_pos_i);
    delay(response_time_1); //Delay the time takee to turn the servo by the given increment
    Serial.println(servo_joint_3_parking_pos_i);
    servo_joint_3_parking_pos_i = servo_joint_3_parking_pos_i - servo_joint_3_pos_increment;

  }
}
void servo3return() {

  if (servo_joint_3_parking_pos_i < servo_joint_3_max_pos) {
    myservo2.write( servo_joint_3_parking_pos_i);
    delay(response_time_1); 
    Serial.println(servo_joint_3_parking_pos_i);
    servo_joint_3_parking_pos_i = servo_joint_3_parking_pos_i + servo_joint_3_pos_increment;

  }
}
void servo4(){
   if (servo_joint_4_parking_pos_i < servo_joint_4_max_pos) {
    myservo3.write( servo_joint_4_parking_pos_i);
    delay(response_time_1);
    Serial.println(servo_joint_4_parking_pos_i);

    servo_joint_4_parking_pos_i = servo_joint_4_parking_pos_i + servo_joint_4_pos_increment;

  }
}
void servo4return(){
   if (servo_joint_4_parking_pos_i > servo_joint_4_min_pos) {
    myservo3.write(servo_joint_4_parking_pos_i);
    delay(response_time_1);
    Serial.println(servo_joint_4_parking_pos_i);

    servo_joint_4_parking_pos_i = servo_joint_4_parking_pos_i - servo_joint_4_pos_increment;

  }
}
void servo5(){
   if (servo_joint_5_parking_pos_i < servo_joint_5_max_pos) {
    myservo4.write( servo_joint_5_parking_pos_i);
    delay(response_time_1);
    Serial.println(servo_joint_5_parking_pos_i);

    servo_joint_5_parking_pos_i = servo_joint_5_parking_pos_i + servo_joint_5_pos_increment;

  }
}
void servo5return(){
   if (servo_joint_5_parking_pos_i > servo_joint_5_min_pos) {
    myservo4.write(servo_joint_5_parking_pos_i);
    delay(response_time_1);
    Serial.println(servo_joint_5_parking_pos_i);

    servo_joint_5_parking_pos_i = servo_joint_5_parking_pos_i - servo_joint_5_pos_increment;

  }
}
void GetMpuValue1(const int MPU) {

  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true); // request a total of 14 registers

  AcX1 = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY1 = Wire.read() << 8 |  Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ1 = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  Tmp1 = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)

  int xAng = map(AcX1, minVal, maxVal, -90, 90);
  int yAng = map(AcY1, minVal, maxVal, -90, 90);
  int zAng = map(AcZ1, minVal, maxVal, -90, 90);

  GyX1 = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY1 = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ1 = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI) + 4; //offset by 4 degrees to get back to zero
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

  Serial.print("AngleX= ");
  Serial.print(x);
  Serial.print("\t");

  Serial.print("AngleY= ");
  Serial.print(y);
  Serial.print("\t");

  Serial.print("AngleZ= ");
  Serial.print(z);
  Serial.print("\t");
  Serial.println("-----------just try------------------------------");
 
 delay(2000);
}
