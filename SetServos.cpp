/*
 * SetServos.cpp
 *
 *  Created on: Jun 7, 2018
 *      Author: hephaestus
 */

#include "SetServos.h"

//User function to be called when a packet comes in
// Buffer contains data from the packet coming in at the start of the function
// User data is written into the buffer to send it back
void SetServos::event(float * buffer) {
	uint8_t * bytes = (uint8_t *) buffer;
	if ((lastTime + 20) < millis()) {
		lastTime = millis();
		for (int i = 0; i < 16; i++) {
			if (currentPos[i] != bytes[i]) {
				//Serial.println(bytes[i]);
				servos[i].write((int)map(bytes[i], 0, 255, 0, 180));
				currentPos[i] = bytes[i];
			}

		}
	}
	//Serial.println("=========");
}
