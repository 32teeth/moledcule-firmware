/*
 * @description all punch IO
 */
IO P1_IO = {3, INPUT, HIGH, "d", P1_INDEX};
IO P2_IO = {2, INPUT, HIGH, "d", P2_INDEX};
IO P3_IO = {0, INPUT, HIGH, "d", P3_INDEX};
IO P4_IO = {1, INPUT, HIGH, "d", P4_INDEX};
/*
 * @description all kick IO
 */
IO K1_IO = {4, INPUT, HIGH, "d", K1_INDEX};
IO K2_IO = {A3, INPUT, HIGH, "a", K2_INDEX};
IO K3_IO = {12, INPUT, HIGH, "d", K3_INDEX};
IO K4_IO = {6, INPUT, HIGH, "d", K4_INDEX};

/*
 * @description all alt IO
 */		
IO START_IO = {10, INPUT, HIGH, "d", START_INDEX};
IO SELECT_IO = {9, INPUT, HIGH, "d", SELECT_INDEX};
IO HOME_IO = {8, INPUT, HIGH, "d", HOME_INDEX};

/*
 * @description direction IO
 */
IO RIGHT_IO = {A2, INPUT, HIGH, "a", RIGHT_INDEX};
IO DOWN_IO = {11, INPUT, HIGH, "d", DOWN_INDEX};	
IO LEFT_IO = {A1, INPUT, HIGH,"a", LEFT_INDEX};
IO UP_IO = {A0, INPUT, HIGH, "a", UP_INDEX};

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
Punch PUNCH = {{0,0,0,0},{0,0,0,0},0,"0"};
Kick KICK = {{0,0,0,0},{0,0,0,0},0,"0"};
Alt ALT = {{0,0,0},{0,0,0},0,"0"};
Direction DIRECTION = {{0,0,0,0},{0,0,0,0},0,"0"};


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
	char buffer[250];
	/*
	(String)sprintf(
		buffer,
		"punch:%d %s kick:%d %s alt:%d %s direction:%d %s",
		PUNCH.address, PUNCH.bin,
		KICK.address, KICK.bin,
		ALT.address, ALT.bin,
		DIRECTION.address, DIRECTION.bin
	);

	printComm(buffer);
	*/
;}

/*
** @method setPins
** @desc itterate through structs and invoke setPins
*/
void setPins()
{
	for(int n = 0; n < 4; n++){setPins(PUNCHS[n]);}
	for(int n = 0; n < 4; n++){setPins(KICKS[n]);}
	for(int n = 0; n < 3; n++){setPins(ALTS[n]);}
	for(int n = 0; n < 4; n++){setPins(DIRECTIONS[n]);}	
}

/*
** @method getPins
** @desc itterate through structs and set appropriate structs
*/
void getPins()
{
	PUNCH.address = 0;
	for(int n = 0; n < 4; n++)
	{
		getPins(PUNCHS[n]);
		PUNCH.states[n] = PUNCHS[n].state;
		PUNCH.address |= PUNCH.states[n] == 0 ? 1 << n : 0 << n;
	}
	PUNCH.bin = getBin(PUNCH.address);

	KICK.address = 0;
	for(int n = 0; n < 4; n++)
	{
		getPins(KICKS[n]);
		KICK.states[n] = KICKS[n].state;
		KICK.address |= KICK.states[n] == 0 ? 1 << n : 0 << n;
	}		
	KICK.bin = getBin(KICK.address);

	ALT.address = 0;
	for(int n = 0; n < 3; n++)
	{
		getPins(ALTS[n]);
		ALT.states[n] = ALTS[n].state;
		ALT.address |= ALT.states[n] == 0 ? 1 << n : 0 << n;	
	}			
	ALT.bin = getBin(ALT.address);

	DIRECTION.address = 0;
	for(int n = 0; n < 4; n++)
	{
		getPins(DIRECTIONS[n]);
		DIRECTION.states[n] = DIRECTIONS[n].state;		
		DIRECTION.address |= DIRECTION.states[n] == 0 ? 1 << n : 0 << n;	
	}
	DIRECTION.bin = getBin(DIRECTION.address);

	#ifdef DEBUG
		printPins();
	#endif
}




