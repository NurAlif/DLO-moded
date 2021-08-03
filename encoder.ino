/* Rotary encoder methods
	CW        CCW
	01        00
	11        10
	10        11
	00        01
*/

int encoderVal = 0;


// ------------------------
// called by ISR
int getEncoderSteps()	{
// ------------------------
	static int encoderPrevVal = 0;
	int newCount = encoderVal - encoderPrevVal;

	// 4 ticks make one step in rotary encoder
	int numSteps = newCount / 4;
	int remainder = newCount % 4;

	encoderPrevVal = encoderVal - remainder;
	return numSteps;
}



// ------------------------
// ISR
void readEncoderISR()	{
// ------------------------
	static byte lastPos = 0b00;

	byte aNow = digitalRead(ENCODER_A);
	byte bNow = digitalRead(ENCODER_B);

	byte posNow = aNow << 1 | bNow;

	if(!aNow)
		encoderVal++;
	if(!bNow)
		encoderVal--;

	lastPos = posNow;

	// convert the encoder reading into rounded steps
	int steps = getEncoderSteps();

	if(steps != 0)	{
		// take action
		encoderChanged(steps);
	}
}



long lastABPress = 0;


// ------------------------
// ISR
void readASwitchISR()	{
// ------------------------
	if(millis() - lastABPress < BTN_DEBOUNCE_TIME)
		return;
	lastABPress = millis();

	encoderChanged(-1);
}



// ------------------------
// ISR
void readBSwitchISR()	{
// ------------------------
	if(millis() - lastABPress < BTN_DEBOUNCE_TIME)
		return;
	lastABPress = millis();
	
	encoderChanged(1);
}
