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

SoftwareSerial mySerial(RX, TX);
String txtMsg = ""; 

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
  // Set hardware serial baud rate
  Serial.begin(9600);
  // Set software serial baud rate
  mySerial.begin(57600);
  Serial.println("STARTING serial communication with BT0417C device...");
  
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
  Serial.println("Sending command AT+BAUD7 (57600)..."); // 57600 Optimal Android Bluetooth baud rate
  Serial.print("REPLY: ");  
  mySerial.write("AT+BAUD7");
  read_serial();
}

void loop()
{
  // Connectivity tests
  
  // TODO Send messages coming in via Serial Monitor to Bluetooth module and beyond, which should happened if it is paired and connected.
 
 
  // Send message coming in via Bluetooth monitor to Serial Monitor
   while (mySerial.available() > 0) {
    //char inChar = Serial.read();
    char inChar = mySerial.read();
    txtMsg += inChar;
  }
  if (txtMsg.length() > 0) {
    
    Serial.println(txtMsg);
    mySerial.write("Message received ok");
    txtMsg = "";
    
    delay(2000);
  }
}
