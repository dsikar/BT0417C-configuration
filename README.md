BT0417C Configuration
==============

# What is the BT0417C?

The BT0417C is a Wireless Bluetooth TTL Transceiver Module on one end and RS232 communication at the other. That means you can use it to add Bluetooth to any RS232 enabled device such as a microcontroller.  
At the heart of this breakout board, manufactured by mdfly.com is the CSR BC417 chip, once manufactured by CSR (Cambridge Silicon Radio Limited now Qualcomm).

# Configuration

To configure the module, first wire the breakout board to an Anduino Uno, load the sketch and change the parameters to suit your application.

## Wiring

![BT0417C Wiring](images/BT0417C-wiring.png)

Wire ground (green) and +5V (red) from your breadboard to the UNO (the actual labels are written at the back of the BT0417C), then TX to 2 and RX to 3. Once the module is powered up, a blinking LED indicates that Bluetooth radio is functional but device is not paired. Once it is paired, the LED will stay on and stop blinking. Note, the UNO must also be connected. 

## Configuring

Load the sketch into your IDE. In setup(), edit four-digit PIN and name (57600 baud rate works ok with Android) then compile and upload.

## Testing

Once paired and connected, messages sent from Android (Bluetooth monitoring app of your choice required) should turn up at Serial Monitor and vice-versa.

## Datasheets

TODO  
CSR  
MDFLY x2
