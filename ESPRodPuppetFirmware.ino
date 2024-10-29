/* Basic Raw HID Example
 Teensy can send/receive 64 byte packets with a
 dedicated program running on a PC or Mac.

 You must select Raw HID from the "Tools > USB Type" menu

 Optional: LEDs should be connected to pins 0-7,
 and analog signals to the analog inputs.

 This example code is in the public domain.
 */
#include <SimplePacketComs.h>
#include <Esp32SimplePacketComs.h>
#include <Esp32WifiManager.h>
#include <ESP32Servo.h>
#include "SetServos.h"
#include "server/NameCheckerServer.h"
#include <WiiChuck.h>

UDPSimplePacket coms;
WifiManager manager;
String * name =new String("rodpuppet");
Accessory nunchuck1;
SetServos * servos = new SetServos();
uint8_t cp[NUM_SERVO_SERVED] = {90,90,90,90,90,90,90,90,90,90,90,90};

Delta * fb = new Delta(0,1,2,cp);
Delta * left = new Delta(3,4,5,cp);
Delta * right = new Delta(6,7,8,cp);


void setup() {
	//manager.setup();
	coms.attach(new NameCheckerServer(name));
	coms.attach(servos);
  nunchuck1.begin();
}

void loop() {
	//manager.loop();
	//coms.server();
  if(manager.getState()!=Connected){
    nunchuck1.readData();    // Read inputs and update maps
    //nunchuck1.printInputs(); // Print all inputs
    fb->update(nunchuck1.values[0], nunchuck1.values[1]);

    servos->event((float *)cp);
  }
}
