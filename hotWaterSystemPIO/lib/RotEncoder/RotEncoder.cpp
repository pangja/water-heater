#include "RotEncoder.h"

RotEncoder::RotEncoder(int CLK, int DT) {
    clk = CLK;
    dt = DT;
    pinMode(clk, INPUT);
    pinMode(dt, INPUT);
    lastStateCLK = digitalRead(clk);
    	// Setup Serial Monitor
    Serial.begin(9600);
}

void RotEncoder::readEncoder(){
    // // Read the current state of CLK
	// currentStateCLK = digitalRead(clk);

	// // If last and current state of CLK are different, then pulse occurred
	// // React to only 1 state change to avoid double count
	// if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
    //     rotation = true;
	// 	// If the DT state is different than the CLK state then
	// 	// the encoder is rotating CCW so decrement
	// 	if (digitalRead(dt) != currentStateCLK) {
	// 		val = -1;
	// 	} else {
	// 		// Encoder is rotating CW so increment
	// 		val = 1;
	// 	}
	// }
	// // Remember last CLK state
	// lastStateCLK = currentStateCLK;

// Read the current state of CLK
	// Read the current state of CLK
	currentStateCLK = digitalRead(clk);

	// If last and current state of CLK are different, then pulse occurred
	// React to only 1 state change to avoid double count
	if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
		rotation = true;
		// If the DT state is different than the CLK state then
		// the encoder is rotating CCW so decrement
		if (digitalRead(dt) != currentStateCLK) {
			val = -1;
			counter --;
			currentDir ="CCW";
		} else {
			// Encoder is rotating CW so increment
			val = 1;
			counter ++;
			currentDir ="CW";
		}

		// Serial.print("Direction: ");
		// Serial.print(currentDir);
		// Serial.print(" | Counter: ");
		//Serial.println(val);
	}

	// Remember last CLK state
	lastStateCLK = currentStateCLK;

	// Put in a slight delay to help debounce the reading
	delay(1);
}
