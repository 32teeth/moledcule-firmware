/*
 * @author Eugene Andruszczenko
 * @version 0.0.5
 * @date created 08/19/16
 * @date updated 09/14/16
 * @description
 */
#include <Arduino.h>

/*
 * @struct IO
 */
typedef struct{
	int pin;
	int mode;
	int state;
	String type;
} IO;	

/*
 * @struct Punch
 */
typedef struct {
	int states[4];
	int stored[4];
	int address;
	String state;				
} Punch;

/*
 * @struct Kick
 */
typedef struct {
	int states[4];
	int stored[4];
	int address;
	String state;				
} Kick;

/*
 * @struct Alt
 */
typedef struct {
	int states[3];
	int stored[3];
	int address;		
	String state;				
} Alt;

/*
 * @struct Direction
 */
typedef struct {
	int states[4];
	int stored[4];
	int address;			
	String state;			
} Direction;

#ifdef KAIMANA
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
IO LEFT = {A1, INPUT, HIGH, "a"};
IO UP = {A0, INPUT, HIGH, "a"};
#endif

#ifdef LITEBRITE
/*
 * @description punchs
 */
IO P1 = {5, INPUT, HIGH, "d"};
IO P2 = {10, INPUT, HIGH, "d"};
IO P3 = {9, INPUT, HIGH, "d"};
IO P4 = {8, INPUT, HIGH, "d"};
/*
 * @description kicks
 */
IO K1 = {12, INPUT, HIGH, "d"};
IO K2 = {6, INPUT, HIGH, "d"};
IO K3 = {2, INPUT, HIGH, "d"};
IO K4 = {4, INPUT, HIGH, "d"};

/*
 * @description alts
 */		  
IO START = {13, INPUT, HIGH, "d"};    
IO SELECT = {A1, INPUT, HIGH, "a"};
IO HOME = {A0, INPUT, HIGH, "a"};

/*
 * @description directions
 */
IO RIGHT = {A3, INPUT, HIGH, "a"};
IO DOWN = {A4, INPUT, HIGH, "a"};   
IO LEFT = {A2, INPUT, HIGH, "a"};
IO UP = {A5, INPUT, HIGH, "a"};       
#endif

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
Punch punch;
Kick kick;
Alt alt;
Direction direction; 

void setPins(IO& io)
{	
	pinMode(io.pin, io.mode);
	digitalWrite(io.pin, io.state);
}		

void readPins(IO& io)
{	
	io.state = digitalRead(io.pin);			
}

void readPins()
{
	punch.address = 0;
	for(int n = 0; n < 4; n++)
	{
		//punch.states[n] = punchs[n].type.equals("a") ? analogRead(punchs[n].pin) > 100 ? 1 : 0 : digitalRead(punchs[n].pin);
		readPins(punchs[n]);
		punch.states[n] = punchs[n].state;
		punch.address |= punch.states[n] == 0 ? 1 << n : 0 << n;
	}	

	kick.address = 0;
	for(int n = 0; n < 4; n++)
	{
		//kick.states[n] = kicks[n].type.equals("a") ? analogRead(kicks[n].pin) > 100 ? 1 : 0 : digitalRead(kicks[n].pin);
		readPins(kicks[n]);
		kick.states[n] = kicks[n].state;
		kick.address |= kick.states[n] == 0 ? 1 << n : 0 << n;
	}		

	alt.address = 0;
	for(int n = 0; n < 3; n++)
	{
		//alt.states[n] = alts[n].type.equals("a") ? analogRead(alts[n].pin) > 100 ? 1 : 0 : digitalRead(alts[n].pin);
		readPins(alts[n]);
		alt.states[n] = alts[n].state;
		alt.address |= alt.states[n] == 0 ? 1 << n : 0 << n;				
	}			

	direction.address = 0;
	for(int n = 0; n < 4; n++)
	{
		//direction.states[n] = directions[n].type.equals("a") ? analogRead(directions[n].pin) > 100 ? 1 : 0 : digitalRead(directions[n].pin);
		readPins(directions[n]);
		direction.states[n] = directions[n].state;		
		direction.address |= direction.states[n] == 0 ? 1 << n : 0 << n;	
	}

	#ifdef DEBUG
		COMM->print("hello");
	#endif
}	

/*
 *
 */
void initPins()
{
	for(int n = 0; n < 4; n++){setPins(punchs[n]);}
	for(int n = 0; n < 4; n++){setPins(kicks[n]);}
	for(int n = 0; n < 3; n++){setPins(alts[n]);}
	for(int n = 0; n < 4; n++){setPins(directions[n]);}
}