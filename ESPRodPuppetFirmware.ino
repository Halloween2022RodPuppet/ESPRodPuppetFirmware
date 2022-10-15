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

UDPSimplePacket coms;
void setup() {
	String name ="rodpuppet";
	coms.attach(new NameCheckerServer(&name));
	coms.attach(new SetServos());
}

void loop() {
	coms.server();
}
