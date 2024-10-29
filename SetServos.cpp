/*
 * SetServos.cpp
 *
 *  Created on: Jun 7, 2018
 *      Author: hephaestus
 */

#include "SetServos.h"

 float Delta::fmap(float x, float in_min, float in_max, float out_min, float out_max) {
    const float run = in_max - in_min;
    if(run == 0){
        log_e("map(): Invalid input range, min == max");
        return -1; // AVR returns -1, SAM returns 0
    }
    const float rise = out_max - out_min;
    const float delta = x - in_min;
    return (delta * rise) / run + out_min;
}
//User function to be called when a packet comes in
// Buffer contains data from the packet coming in at the start of the function
// User data is written into the buffer to send it back
void SetServos::event(float * buffer) {
	uint8_t * bytes = (uint8_t *) buffer;
	if ((lastTime + 20) < millis()) {
		lastTime = millis();
		for (int i = 0; i < NUM_SERVO_SERVED; i++) {
			if (currentPos[i] != bytes[i]) {
				Serial.println("Byte "+String(i)+" val= "+String((int)bytes[i]));
				servos[i].write(constrain(bytes[i],0,180));
				currentPos[i] = bytes[i];
			}

		}
	}
	//Serial.println("=========");
}
