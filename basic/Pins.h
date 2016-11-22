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

/*
 * @description all punch IO
 */
IO P1_IO = {3, INPUT, HIGH, "d", 0};
IO P2_IO = {2, INPUT, HIGH, "d", 0};
IO P3_IO = {0, INPUT, HIGH, "d", 0};
IO P4_IO = {1, INPUT, HIGH, "d", 0};

/*
 * @description all kick IO
 */
IO K1_IO = {4, INPUT, HIGH, "d", 0};
IO K2_IO = {A3, INPUT, HIGH, "a", 0};
IO K3_IO = {12, INPUT, HIGH, "d", 0};
IO K4_IO = {6, INPUT, HIGH, "d", 0};

/*
 * @description all alt IO
 */		
IO START_IO = {10, INPUT, HIGH, "d", 0};
IO SELECT_IO = {9, INPUT, HIGH, "d", 0};
IO HOME_IO = {8, INPUT, HIGH, "d", 0};

/*
 * @description direction IO
 */
IO RIGHT_IO = {A2, INPUT, HIGH, "a", 0};
IO DOWN_IO = {11, INPUT, HIGH, "d", 0};
IO LEFT_IO = {A1, INPUT, HIGH,"a", 0};
IO UP_IO = {A0, INPUT, HIGH, "a", 0};

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
** @method printPins
** @desc create string buffer and dump to serial
*/
void printPins()
{
	char punch[8];PUNCH.bin.toCharArray(punch, 8);
	char kick[8];KICK.bin.toCharArray(kick, 8);
	char alt[8];ALT.bin.toCharArray(alt, 8);
	char direction[8];DIRECTION.bin.toCharArray(direction, 8);
		
	char buffer[100];

	(String)sprintf(
		buffer,
		"punch:%d %s kick:%d %s alt:%d %s direction:%d %s",
		PUNCH.address, punch,
		KICK.address, kick,
		ALT.address, alt,
		DIRECTION.address, direction
	);

	printComm(buffer);
;}

/*
** @method setPins
** @desc itterate through structs and invoke setPins
*/
void setPins()
{
	for(uint8_t n = 0; n < 4; n++)
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
void getPins()
{
	PUNCH.address = 0;
	KICK.address = 0;
	DIRECTION.address = 0;
	ALT.address = 0;

	for(uint8_t n = 0; n < 4; n++)
	{
		/*
		 *
		 */
		getPins(PUNCHS[n]);
		if(PUNCH.states[n] != PUNCHS[n].state){PUNCHS[n].changed = (now + duration);}
		PUNCH.states[n] = PUNCHS[n].state;
		PUNCH.address |= PUNCH.states[n] == 0 ? 1 << n : 0 << n;

		/*
		 *
		 */
		getPins(KICKS[n]);
		if(KICK.states[n] != KICKS[n].state){KICKS[n].changed = (now + duration);}
		KICK.states[n] = KICKS[n].state;
		KICK.address |= KICK.states[n] == 0 ? 1 << n : 0 << n;

		/*
		 *
		 */
		getPins(DIRECTIONS[n]);
		if(DIRECTION.states[n] != DIRECTIONS[n].state){DIRECTIONS[n].changed = (now + duration);}
		DIRECTION.states[n] = DIRECTIONS[n].state;
		DIRECTION.address |= DIRECTION.states[n] == 0 ? 1 << n : 0 << n;						

		/*
		 *
		 */
		if(n < 3)
		{
			getPins(ALTS[n]);
			if(ALT.states[n] != ALTS[n].state){ALTS[n].changed = (now + duration);}
			ALT.states[n] = ALTS[n].state;
			ALT.address |= ALT.states[n] == 0 ? 1 << n : 0 << n;	
		}
	}
	
	PUNCH.bin = getBin(PUNCH.address);
	KICK.bin = getBin(KICK.address);
	DIRECTION.bin = getBin(DIRECTION.address);
	ALT.bin = getBin(ALT.address);


	#ifdef DEBUG
		printPins();
	#endif
}




