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
#define NUM_SERVO_SERVED 12
class SetServos: public PacketEventAbstract {
private:
	unsigned long long lastTime = 0;

#if defined(ARDUINO_ARCH_ESP32)
	Servo servos[NUM_SERVO_SERVED];
#else
	PWMServo servos[NUM_SERVO_SERVED];
#endif
	int currentPos[NUM_SERVO_SERVED] = {90,};
	int ServoPins[NUM_SERVO_SERVED] ={15,2,4,16,17,5,18,13,12,14,27,26,25};
		// { 10, 30, 29, 21, 22, 6, 8, 4, 38, 37, 35, 5, 2, 14, 36, 9, 3, 7, 23, 20 };
		//{9,8, 4, 5, 2,3, 7, 6, 22, 21, 10, 29, 30, 23, 20, 14, 36, 35, 37, 38}
		//
	


public:
	// Packet ID needs to be set
	SetServos() :
		PacketEventAbstract(1962)	// Address of this event
{
		for (int i = 0; i < NUM_SERVO_SERVED; i++) {
			servos[i].attach(ServoPins[i],1000,2400);
			servos[i].write(currentPos[i]);
		}
}
	//User function to be called when a packet comes in
	// Buffer contains data from the packet coming in at the start of the function
	// User data is written into the buffer to send it back
	void event(float * buffer);
};




#endif /* LIBRARIES_MEDIUMKATFIRMWARE_SRC_SETSERVOS_H_ */
