 /*
   Notes on using this code to pair the BT0417C with the Arduino Uno
   
   by Daniel Sikar - 21.11.2012
   
   1. Pins 0 and 1 did not work as RX, TX.
   2. Pins 2 and 3 worked as RX, TX. Not only did they work, uploading sketches also worked, as opposed to pins 0 and 1, where the wires had to be
   disconnected on every compile and upload. IMPORTANT: Connect Arduino RX to Bluetooth adapter TX and Arduino TX to Bluetooth adapter RX.
   3. A delay was required to assemble messages typed into Serial Monitor without introducting line breaks.
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
  // Connectivity tests.
  // Tested with Amarino and Bluetooth Viewer (LITE).
  // Note, the BT0417C must NOT be *paired* while starting the Serial Monitor.
  
  // 1. SEND - Assemble message sent via Serial Monitor
  while (Serial.available() > 0) {
    char inChar = Serial.read();
    txtMsg += inChar;
  }
  // Delay used for human readability so we don't split messages
  // typed in Serial Monitor. 
  // If application at the other end can identify beginning and end
  // of message such as delimiters, delay is not required.
  delay(200);
  if (txtMsg.length() > 0) {
    // Echo message to Serial Monitor. 
    Serial.print("BT0417C sending message: ");
    Serial.println(txtMsg);
    // Send to BT0417C
    mySerial.print("BT0417C sending message: ");
    mySerial.println(txtMsg);
    txtMsg = "";
  }
  // 2. RECEIVE - Assemble message received by BT0417C
  while (mySerial.available() > 0) {
    //char inChar = Serial.read();
    char inChar = mySerial.read();
    txtMsg += inChar;
  }
  if (txtMsg.length() > 0) {
    // Print incoming message received by BT0417C to Serial Monitor then echo back to sender.
    Serial.print("BT0417C received message: ");
    Serial.println(txtMsg);  
    mySerial.print("BT0417C received message: ");
    mySerial.println(txtMsg);
    txtMsg = "";
  }
}
