#include "RotEncoder.h"

RotEncoder::RotEncoder(int CLK, int DT, int SW) {
    clk = CLK;
    dt = DT;
	sw = SW;
    pinMode(clk, INPUT);
    pinMode(dt, INPUT);
	pinMode(sw, INPUT);
    lastStateCLK = digitalRead(clk);
}

void RotEncoder::readEncoder(){
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
		} else {
			// Encoder is rotating CW so increment
			val = 1;
		}
	}

	// Remember last CLK state
	lastStateCLK = currentStateCLK;

	// Read the button state
	btnState = digitalRead(sw);

	// LOW signal, button is pressed
	if (btnState == LOW) {
		//if 50ms have passed since last LOW pulse, it means that the
		//button has been pressed, released and pressed again
		if (millis() - lastButtonPress > 50) {
			btnPress = true;
		}
		// Remember last button press event
		lastButtonPress = millis();
	} else {
		//btnState = false;
		btnPress = false;
	}

	// debounce the reading
	delay(1);
}
