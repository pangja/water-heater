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
	// Read the current state of CLK
	currentStateCLK = digitalRead(clk);

	// If last and current state of CLK are different, then pulse occurred
	// React to only 1 state change to avoid double count
	if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

		// If the DT state is different than the CLK state then
		// the encoder is rotating CCW so decrement
		if (digitalRead(dt) != currentStateCLK) {
			counter --;
			currentDir ="CCW";
		} else {
			// Encoder is rotating CW so increment
			counter ++;
			currentDir ="CW";
		}

		// Serial.print("Direction: ");
		// Serial.print(currentDir);
		// Serial.print(" | Counter: ");
		Serial.println(counter);
	}

	// Remember last CLK state
	lastStateCLK = currentStateCLK;

	// Read the button state
	// int btnState = digitalRead(1);

	//If we detect LOW signal, button is pressed
	// if (btnState == LOW) {
	// 	//if 50ms have passed since last LOW pulse, it means that the
	// 	//button has been pressed, released and pressed again
	// 	if (millis() - lastButtonPress > 50) {
	// 		Serial.println("Button pressed!");
	// 	}

	// 	// Remember last button press event
	// 	lastButtonPress = millis();
	// }

	// Put in a slight delay to help debounce the reading
	delay(1);
}
