/*
----------------------------------
Hope programm for BLE Android App
----------------------------------

BLE HC06
--------
Vcc -> 3,3V
GND -> GND
RX -> pin2
TX -> pin3

SERVO
-----
BLACK -> GND
RED -> 5V
YELLOW -> pin5
*/

#include <SoftwareSerial.h>
#include <Servo.h>

/*
GLOBAL VARIABLES
*/

//BLUETOOTH
/*
Not all pins on the Leonardo and Micro support change interrupts,
so only the following can be used for RX: 8, 9, 10, 11, 14 (MISO),
15 (SCK), 16 (MOSI)
*/
int bleRX=10; //Connect to HC06 TX
int bleTX=11; //Connect to HC06 RX
SoftwareSerial bluetooth(bleRX,bleTX);
//Append the command from the BLE device
String message;

//SERVO
int servoPin=5;
Servo myServo;
int pos=0;

//Setup serial and bluetooth comunication
void setup(){
  Serial.begin(9600);
  bluetooth.begin(9600);
  myServo.attach(servoPin);
  //Serial.println("HOPE...");
}

//Loop
void loop(){

  //During the transmission collect all the data in message
  while(bluetooth.available()){
    message+=char(bluetooth.read());
    //Serial.println(message);
    //If no transmission read the message
    if(!bluetooth.available()){
      if(message!=""){
        //Serial.print("Messagge: ");
        //Serial.println(message);
        //Convert message to int
        String bleDataString=message.substring(1);
        int bleData=bleDataString.toInt();
        Serial.print("Data: ");
        Serial.println(bleData);
        moveServo(bleData);
        message="";

      }
    }
  }
  delay(100);
  //Serial.println("...");

}

//Servo
void moveServo(int data){
  //"data" range from 0 to 180
  myServo.write(data);
}
