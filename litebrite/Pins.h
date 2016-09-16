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
 * @struct Command
 */
typedef struct {
	int states[8];
	int stored[8];
	int address;
	String state;				
} Command;

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

/*
 * @description commands
 */
IO P1 = {3, INPUT, HIGH, "d"};
IO P2 = {2, INPUT, HIGH, "d"};
IO P3 = {0, INPUT, HIGH, "d"};
IO P4 = {1, INPUT, HIGH, "d"};
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

/*
 * @description array of IO
 */
IO commands[8] = {P1, P2, P3, P4, K1, K2, K3, K4};
IO alts[3] = {START, SELECT, HOME};
IO directions[4] = {RIGHT, DOWN, LEFT, UP}; 

/*
 * @description
 */
Command command;
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
	command.address = 0;
	for(int n = 0; n < 8; n++)
	{
		command.states[n] = commands[n].type.equals("a") ? analogRead(commands[n].pin) > 100 ? 1 : 0 : digitalRead(commands[n].pin);
		command.address |= command.states[n] == 0 ? 1 << n : 0 << n;
	}	

	alt.address = 0;
	for(int n = 0; n < 3; n++)
	{
		alt.states[n] = alts[n].type.equals("a") ? analogRead(alts[n].pin) > 100 ? 1 : 0 : digitalRead(alts[n].pin);
		alt.address |= alt.states[n] == 0 ? 1 << n : 0 << n;				
	}			

	direction.address = 0;
	for(int n = 0; n < 4; n++)
	{
		direction.states[n] = analogRead(directions[n].pin) > 100 ? 1 : 0;
		direction.address |= direction.states[n] == 0 ? 1 << n : 0 << n;	
	}				
}	

/*
 *
 */
void initPins()
{
	for(int n = 0; n < 8; n++){setPins(commands[n]);}
	for(int n = 0; n < 3; n++){setPins(alts[n]);}
	for(int n = 0; n < 4; n++){setPins(directions[n]);}
}

/*
	#ifdef KAIMANA
    IO P1 = {3, INPUT, HIGH, "d"};
    IO P2 = {2, INPUT, HIGH, "d"};
    IO P3 = {0, INPUT, HIGH, "d"};
    IO P4 = {1, INPUT, HIGH, "d"};
    IO K1 = {4, INPUT, HIGH, "d"};
    IO K2 = {A3, INPUT, HIGH, "a"};
    IO K3 = {12, INPUT, HIGH, "d"};
    IO K4 = {6, INPUT, HIGH, "d"};
    
    IO START = {10, INPUT, HIGH, "d"};    
    IO SELECT = {9, INPUT, HIGH, "d"};
    IO HOME = {8, INPUT, HIGH, "d"};

    IO RIGHT = {A2, INPUT, HIGH, "a"};
    IO DOWN = {11, INPUT, HIGH, "d"};   
    IO LEFT = {A1, INPUT, HIGH, "a"};
    IO UP = {A0, INPUT, HIGH, "a"};
  #endif

  #ifdef LITEBRITE
    IO P1 = {5, INPUT, HIGH, "d"};
    IO P2 = {10, INPUT, HIGH, "d"};
    IO P3 = {9, INPUT, HIGH, "d"};
    IO P4 = {8, INPUT, HIGH, "d"};
    IO K1 = {12, INPUT, HIGH, "d"};
    IO K2 = {6, INPUT, HIGH, "d"};
    IO K3 = {2, INPUT, HIGH, "d"};
    IO K4 = {4, INPUT, HIGH, "d"};
    
    IO START = {13, INPUT, HIGH, "d"};    
    IO SELECT = {A1, INPUT, HIGH, "a"};
    IO HOME = {A0, INPUT, HIGH, "a"};

    IO RIGHT = {A3, INPUT, HIGH, "a"};
    IO DOWN = {A4, INPUT, HIGH, "a"};   
    IO LEFT = {A2, INPUT, HIGH, "a"};
    IO UP = {A5, INPUT, HIGH, "a"};       
  #endif
 */