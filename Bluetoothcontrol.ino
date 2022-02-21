
#include <SoftwareSerial.h> // TX RX software library for bluetooth
 #include <Servo.h> // servo library
Servo myservo1, myservo2, myservo3, myservo4, myservo5, myservo6; // servo name
 int bluetoothTx = 10; // bluetooth tx to 10 pin
int bluetoothRx = 11; // bluetooth rx to 11 pin
 SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
 void setup()
{
 myservo1.attach(3); // attach to preffered pin
 myservo2.attach(4);
 myservo3.attach(5);
 myservo4.attach(6);
 myservo5.attach(7);
 myservo6.attach(8);
  myservo1.write(0);
  myservo2.write(90);
  myservo3.write(160);
  myservo4.write(180);
  myservo5.write(0);
  myservo6.write(90);
  
 //Setup usb serial connection to computer
 Serial.begin(9600);
 //Setup Bluetooth serial connection to android
 bluetooth.begin(9600);
}
 void loop()
{
 //Read from bluetooth and write to usb serial
 if(bluetooth.available()>= 2 )
 {
 unsigned int servopos = bluetooth.read();
 unsigned int servopos1 = bluetooth.read();
 unsigned int realservo = (servopos1 *256) + servopos;
 Serial.println(realservo);
 if (realservo >= 1000 && realservo <1220) {
 int servo1 = realservo;
 servo1 = map(servo1, 1000, 1220, 0, 220);
 myservo1.write(servo1);
 Serial.println("Servo 1 ON");
 delay(10);
 }
 if (realservo >= 2000 && realservo <2220) {
 int servo2 = realservo;
 servo2 = map(servo2, 2000, 2220, 0, 220);
 myservo2.write(servo2);
 Serial.println("Servo 2 ON");
 delay(10);
 }
 if (realservo >= 3000 && realservo <3220) {
 int servo3 = realservo;
 servo3 = map(servo3, 3000, 3220, 0, 220);
 myservo3.write(servo3);
 Serial.println("Servo 3 ON");
 delay(10);
 }
 if (realservo >= 4000 && realservo <4220) {
 int servo4 = realservo;
 servo4 = map(servo4, 4000, 4220, 0, 220);
 myservo4.write(servo4);
 Serial.println("Servo 4 ON");
 delay(10);
 }
 if (realservo >= 5000 && realservo <5220) {
 int servo5 = realservo;
 servo5 = map(servo5, 5000, 5220, 0, 220);
 myservo5.write(servo5);
 Serial.println("Servo 5 ON");
 delay(10);
 }
 if (realservo >= 6000 && realservo <6220) {
 int servo6 = realservo;
 servo6 = map(servo6, 6000, 6220, 0, 220);
 myservo6.write(servo6);
 Serial.println("Servo 6 ON");
 delay(10);
 }
 }
}
