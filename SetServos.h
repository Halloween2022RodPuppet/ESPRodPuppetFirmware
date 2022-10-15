/*
 * SetServos.h
 *
 *  Created on: Jun 7, 2018
 *      Author: hephaestus
 */

#ifndef LIBRARIES_MEDIUMKATFIRMWARE_SRC_SETSERVOS_H_
#define LIBRARIES_MEDIUMKATFIRMWARE_SRC_SETSERVOS_H_
#include <SimplePacketComs.h>
#include "Arduino.h"
#if defined(ARDUINO_ARCH_ESP32)
#include <ESP32Servo.h>
#else
#include <PWMServo.h>
#endif

class SetServos: public PacketEventAbstract {
private:
	unsigned long long lastTime = 0;

#if defined(ARDUINO_ARCH_ESP32)
	Servo servos[20];
#else
	PWMServo servos[20];
#endif
	int currentPos[20] = {90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90};
	int ServoPins[20] ={3, 4, 5, 34, 35, 41, 30, 29, 10, 22, 21, 20, 2, 23, 35, 36};
		// { 10, 30, 29, 21, 22, 6, 8, 4, 38, 37, 35, 5, 2, 14, 36, 9, 3, 7, 23, 20 };
		//{9,8, 4, 5, 2,3, 7, 6, 22, 21, 10, 29, 30, 23, 20, 14, 36, 35, 37, 38}
		//
	


public:
	// Packet ID needs to be set
	SetServos() :
		PacketEventAbstract(1962)	// Address of this event
{
		for (int i = 0; i < 16; i++) {
			servos[i].attach(ServoPins[i],1000,2400);
			currentPos[i]=36;
			servos[i].write(currentPos[i]);
		}
}
	//User function to be called when a packet comes in
	// Buffer contains data from the packet coming in at the start of the function
	// User data is written into the buffer to send it back
	void event(float * buffer);
};




#endif /* LIBRARIES_MEDIUMKATFIRMWARE_SRC_SETSERVOS_H_ */
