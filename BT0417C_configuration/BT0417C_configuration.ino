/*
  Software serial multple serial test
 
 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.
 
 The circuit: 
 * RX is digital pin 2 (connect to TX of other device)
 * TX is digital pin 3 (connect to RX of other device)
 
 created back in the mists of time
 modified 9 Apr 2012
 by Tom Igoe
 based on Mikal Hart's example
 
 This example code is in the public domain.
 
 */
 
 /*
   Notes on using this code to pair the BT0417C with the Arduino Uno
   
   by Daniel Sikar - 21.11.2012
   
   1. Pins 0 and 1 did not work as RX, TX.
   2. Pins 2 and 3 worked as RX, TX. Not only did they work, uploading sketches also worked, as opposed to pins 0 and 1, where the wires had to be
   disconnected on every compile and upload. IMPORTANT: Connect Arduino RX to Bluetooth adapter TX and Arduino TX to Bluetooth adapter RX.
   3. A delay was required after every serial write to the BT0417C,
   4. Default baud rate for the BT0417C is 9600.
   5. Response to command AT+NAMEyourname is OKsetname, not OKyourname as per datasheet.
   
 */
#include <SoftwareSerial.h>

#define RX   2
#define TX   3

// SoftwareSerial mySerial(2, 3); // RX, TX
SoftwareSerial mySerial(RX, TX); // RX, TX
int led = 7;
int yellowled = 13;
String txtMsg = ""; 

void blinkred()
{
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
}

void blinkyellowled()
{
  digitalWrite(yellowled, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(yellowled, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
}

void read_serial() {
  // one second delay for module to deal with incoming data
  delay(1000);
  while (mySerial.available() > 0) {
    char inByte = mySerial.read();
    Serial.write(inByte);
  }  
  Serial.write("\n------\n"); 
}

void setup()  
{
  pinMode(led, OUTPUT);
  pinMode(yellowled, OUTPUT);
 
  // Open serial communications and wait for port to open:
  //Serial.begin(57600);
  // Default serial baud rate = 9600, optimal Android baud rate (according to Amarino documentation): 57600
  Serial.begin(9600);
  // set the data rate for the SoftwareSerial port
  mySerial.begin(57600);
  Serial.println("STARTING serial communication with BT0417C device...");

  // if more than one serial communication channel (RX + TX pins) connected, listen explicitly the desired channel
  //mySerial.listen(); 
  
  Serial.println("Sending command AT...");
  Serial.print("REPLY: ");
  mySerial.write("AT");
  read_serial(); 
  Serial.println("Sending command AT+NAME...");
  Serial.print("REPLY: ");  
  mySerial.write("AT+NAMEmed_hum_v0.1");
  read_serial(); 
  Serial.println("Sending command AT+PIN...");
  Serial.print("REPLY: ");
  mySerial.write("AT+PIN0123");
  read_serial();   
  Serial.println("Sending command AT+BAUD7 (57600)...");
  Serial.print("REPLY: ");  
  mySerial.write("AT+BAUD7");
  read_serial();
}

void loop() // run over and over
{

  //while (Serial.available() > 0) {
    while (mySerial.available() > 0) {
    //char inChar = Serial.read();
    char inChar = mySerial.read();
    txtMsg += inChar;
  }
  if (txtMsg.length() > 0) {
    if(txtMsg.substring(1,3) == "on") {
      digitalWrite(led, HIGH);
    }
    if(txtMsg.substring(1,4) == "off") {
      digitalWrite(led, LOW);
   }      
    Serial.println(txtMsg);
    mySerial.write("Message received ok");
    txtMsg = "";
    
    delay(2000);
  }
}
