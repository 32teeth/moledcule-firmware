/*
 * @author Eugene Andruszczenko
 * @version 0.0.5
 * @date created 08/19/16
 * @date updated 09/16/16
 * @description
 */
#include "Pins.h"
	

/*
 * @description punchs
 */
IO P1 = {3, INPUT, HIGH, "d"};
IO P2 = {2, INPUT, HIGH, "d"};
IO P3 = {0, INPUT, HIGH, "d"};
IO P4 = {1, INPUT, HIGH, "d"};
/*
 * @description kicks
 */
IO K1 = {4, INPUT, HIGH, "d"};
IO K2 = {A3, INPUT, HIGH, "a"};
IO K3 = {12, INPUT, HIGH, "d"};
IO K4 = {6, INPUT, HIGH, "d"};

/*
 * @description alts
 */		
IO START = {10, INPUT, HIGH, "d"};
IO SELECT = {9, INPUT, HIGH, "d"};
IO HOME = {8, INPUT, HIGH, "d"};

/*
 * @description directions
 */
IO RIGHT = {A2, INPUT, HIGH, "a"};
IO DOWN = {11, INPUT, HIGH, "d"};	
IO LEFT = {A1, INPUT, HIGH,"a"};
IO UP = {A0, INPUT, HIGH, "a"};

/*
 * @description array of IO
 */
IO punchs[4] = {P1, P2, P3, P4};
IO kicks[4] = {K1, K2, K3, K4};
IO alts[3] = {START, SELECT, HOME};
IO directions[4] = {RIGHT, DOWN, LEFT, UP}; 

/*
 * @description
 */
Punch punch = {{0,0,0,0},{0,0,0,0},0,"0"};
Kick kick = {{0,0,0,0},{0,0,0,0},0,"0"};
Alt alt = {{0,0,0},{0,0,0},0,"0"};
Direction direction = {{0,0,0,0},{0,0,0,0},0,"0"};

/*
 * @class Pins
 * @constructor
 */ 
Pins::Pins()
{
	/*
	 * @description
	 */
	Punch punch = {{0,0,0,0},{0,0,0,0},0,"0"};
	Kick kick = {{0,0,0,0},{0,0,0,0},0,"0"};
	Alt alt = {{0,0,0},{0,0,0},0,"0"};
	Direction direction = {{0,0,0,0},{0,0,0,0},0,"0"};	
	this->set();
}

void Pins::set()
{
	for(int n = 0; n < 4; n++){set(punchs[n]);}
	for(int n = 0; n < 4; n++){set(kicks[n]);}
	for(int n = 0; n < 3; n++){set(alts[n]);}
	for(int n = 0; n < 4; n++){set(directions[n]);}	
}

void Pins::set(IO& io)
{
	pinMode(io.pin, io.mode);
	digitalWrite(io.pin, io.state);
}

void Pins::get()
{
	punch.address = 0;
	for(int n = 0; n < 4; n++)
	{
		get(punchs[n]);
		punch.states[n] = punchs[n].state;
		punch.address |= punch.states[n] == 0 ? 1 << n : 0 << n;
	}

	kick.address = 0;
	for(int n = 0; n < 4; n++)
	{
		get(kicks[n]);
		kick.states[n] = kicks[n].state;
		kick.address |= kick.states[n] == 0 ? 1 << n : 0 << n;
	}		

	alt.address = 0;
	for(int n = 0; n < 3; n++)
	{
		get(alts[n]);
		alt.states[n] = alts[n].state;
		alt.address |= alt.states[n] == 0 ? 1 << n : 0 << n;				
	}			

	direction.address = 0;
	for(int n = 0; n < 4; n++)
	{
		get(directions[n]);
		direction.states[n] = directions[n].state;		
		direction.address |= direction.states[n] == 0 ? 1 << n : 0 << n;	
	}
}

void Pins::get(IO& io)
{
	io.state = digitalRead(io.pin);	
}

/*
 * @class Pins
 * @deconstructor
 */ 
Pins::~Pins(){}