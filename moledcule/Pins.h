/*
 * @author Eugene Andruszczenko
 *  ___ ___ _           _   _   
 * |_  |_  | |_ ___ ___| |_| |_ 
 * |_  |  _|  _| -_| -_|  _|   |
 * |___|___|_| |___|___|_| |_|_|
 * 
 * @version 0.0.5
 * @date created 08/19/16
 * @date updated 10/26/16
 * @description
 */

RGB P1_COLOR;
RGB P2_COLOR;
RGB P3_COLOR;
RGB P4_COLOR;

RGB K1_COLOR;
RGB K2_COLOR;
RGB K3_COLOR;
RGB K4_COLOR;

RGB START_COLOR;
RGB SELECT_COLOR;
RGB HOME_COLOR;

RGB RIGHT_COLOR;
RGB DOWN_COLOR;
RGB LEFT_COLOR;
RGB UP_COLOR;

const int P1_PIN = 3;
const int P2_PIN = 2;
const int P3_PIN = 0;
const int P4_PIN = 1;

const int K1_PIN = 4;
const int K2_PIN = A3;
const int K3_PIN = 12;
const int K4_PIN = 6;

const int START_PIN = 10;
const int SELECT_PIN = 9;
const int HOME_PIN = 8;

const int RIGHT_PIN = A2;
const int DOWN_PIN = 11;
const int LEFT_PIN = A1;
const int UP_PIN = A0;

/*
 * @description all punch IO
 */
IO P1_IO = {P1_PIN, INPUT, 1, "d", P1_INDEX, black, black, getRGB(P1_COLOR, getLong(P1)), 0};
IO P2_IO = {P2_PIN, INPUT, 1, "d", P2_INDEX, black, black, getRGB(P2_COLOR, getLong(P2)), 0};
IO P3_IO = {P3_PIN, INPUT, 1, "d", P3_INDEX, black, black, getRGB(P3_COLOR, getLong(P3)), 0};
IO P4_IO = {P4_PIN, INPUT, 1, "d", P4_INDEX, black, black, getRGB(P4_COLOR, getLong(P4)), 0};

/*
 * @description all kick IO
 */
IO K1_IO = {K1_PIN, INPUT, 1, "d", K1_INDEX, black, black, getRGB(K1_COLOR, getLong(K1)), 0};
IO K2_IO = {K2_PIN, INPUT, 1, "a", K2_INDEX, black, black, getRGB(K2_COLOR, getLong(K2)), 0};
IO K3_IO = {K3_PIN, INPUT, 1, "d", K3_INDEX, black, black, getRGB(K3_COLOR, getLong(K3)), 0};
IO K4_IO = {K4_PIN, INPUT, 1, "d", K4_INDEX, black, black, getRGB(K4_COLOR, getLong(K4)), 0};

/*
 * @description all alt IO
 */		
IO START_IO = {START_PIN, INPUT, 1, "d", START_INDEX, black, black, getRGB(START_COLOR, getLong(START)), 0};
IO SELECT_IO = {SELECT_PIN, INPUT, 1, "d", SELECT_INDEX, black, black, getRGB(SELECT_COLOR, getLong(SELECT)), 0};
IO HOME_IO = {HOME_PIN, INPUT, 1, "d", HOME_INDEX, black, black, getRGB(HOME_COLOR, getLong(HOME)), 0};

/*
 * @description direction IO
 */
IO RIGHT_IO = {RIGHT_PIN, INPUT, 1, "a", RIGHT_INDEX, black, black, getRGB(RIGHT_COLOR, getLong(RIGHT)), 0};
IO DOWN_IO = {DOWN_PIN, INPUT, 1, "d", DOWN_INDEX, black, black, getRGB(DOWN_COLOR, getLong(DOWN)), 0};
IO LEFT_IO = {LEFT_PIN, INPUT, 1,"a", LEFT_INDEX, black, black, getRGB(LEFT_COLOR, getLong(LEFT)), 0};
IO UP_IO = {UP_PIN, INPUT, 1, "a", UP_INDEX, black, black, getRGB(UP_COLOR, getLong(UP)), 0};

/*
 * @description array of IO
 */
IO PUNCHS[4] = {P1_IO, P2_IO, P3_IO, P4_IO};
IO KICKS[4] = {K1_IO, K2_IO, K3_IO, K4_IO};
IO ALTS[3] = {START_IO, SELECT_IO, HOME_IO};
IO DIRECTIONS[4] = {RIGHT_IO, DOWN_IO, LEFT_IO, UP_IO};

/*
 * @description
 */
Punch PUNCH = {{0,0,0,0},0,"0"};
Kick KICK = {{0,0,0,0},0,"0"};
Alt ALT = {{0,0,0},0,"0"};
Direction DIRECTION = {{0,0,0,0},0,"0"};


/*
** @method setPins
** @param io (Struct IO)
** @desc set pin, pin mode and write initial io state
*/
void setPins(IO& io)
{
	pinMode(io.pin, io.mode);
	digitalWrite(io.pin, io.state);
}

/*
** @method getPins
** @param io (Struct IO)
** @desc set io state
*/
void getPins(IO& io)
{
	io.state = digitalRead(io.pin);	
}

/*
** @method setPins
** @desc itterate through structs and invoke setPins
*/
void setPins()
{
	for(int n = 0; n < 4; n++)
	{
		setPins(PUNCHS[n]);
		setPins(KICKS[n]);
		setPins(DIRECTIONS[n]);
		if(n < 3){setPins(ALTS[n]);};		
	}
}

/*
** @method getPins
** @desc itterate through structs and set appropriate structs
*/
int getPin(int pin)
{
	return digitalRead(pin);
}


/*
** @method getPins
** @desc itterate through structs and set appropriate structs
*/
void getPins()
{
	PUNCH.address = 0;
	KICK.address = 0;
	DIRECTION.address = 0;
	ALT.address = 0;

	for(int n = 0; n < 4; n++)
	{
		/*
		 *
		 */
		getPins(PUNCHS[n]);
		if(PUNCH.states[n] != PUNCHS[n].state){PUNCHS[n].changed = (timer.now + duration);}
		PUNCH.states[n] = PUNCHS[n].state;
		PUNCH.address |= PUNCH.states[n] == 0 ? 1 << n : 0 << n;

		/*
		 *
		 */
		getPins(KICKS[n]);
		if(KICK.states[n] != KICKS[n].state){KICKS[n].changed = (timer.now + duration);}
		KICK.states[n] = KICKS[n].state;
		KICK.address |= KICK.states[n] == 0 ? 1 << n : 0 << n;

		/*
		 *
		 */
		getPins(DIRECTIONS[n]);
		if(DIRECTION.states[n] != DIRECTIONS[n].state){DIRECTIONS[n].changed = (timer.now + duration);}
		DIRECTION.states[n] = DIRECTIONS[n].state;
		DIRECTION.address |= DIRECTION.states[n] == 0 ? 1 << n : 0 << n;						

		/*
		 *
		 */
		if(n < 3)
		{
			getPins(ALTS[n]);
			if(ALT.states[n] != ALTS[n].state){ALTS[n].changed = (timer.now + duration);}
			ALT.states[n] = ALTS[n].state;
			ALT.address |= ALT.states[n] == 0 ? 1 << n : 0 << n;	
		}
	}
	
	PUNCH.bin = getBin(PUNCH.address);
	KICK.bin = getBin(KICK.address);
	DIRECTION.bin = getBin(DIRECTION.address);
	ALT.bin = getBin(ALT.address);
}




