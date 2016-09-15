/*
 * @author Eugene Andruszczenko
 * @version 0.0.5
 * @date created 08/19/16
 * @date updated 09/14/16
 * @description
 */

 /*
 * @description Pins include files
 */
#include "Pins.h"
#include "Utils.h"

/*
 * @class Pins
 * @constructor
 */ 
Pins::Pins()
{
  /*
	#define  PIN_DOWN    11   //PB7
	#define  PIN_UP      18   //PF7
	#define  PIN_LEFT    19   //PF6
	#define  PIN_RIGHT   20   //PF5
	#define  PIN_SELECT  9    //PB5
	#define  PIN_HOME    8    //PB4
	#define  PIN_START   10   //PB6
	#define  PIN_P1      3    //PD0
	#define  PIN_P2      2    //PD1
	#define  PIN_P3      0    //PD2
	#define  PIN_P4      1    //PD3
	#define  PIN_K1      4    //PD4
	#define  PIN_K2      21   //PF4
	#define  PIN_K3      12   //PD6
	#define  PIN_K4      6    //PD7 
  */	
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

  IO commands[11] = {P1, P2, P3, P4, K1, K2, K3, K4};
  IO alts[3] = {START, SELECT, HOME};
  IO directions[4] = {RIGHT, DOWN, LEFT, UP}; 

  this->set();	
}

void Pins::set()
{
	for(int n = 0; n < 8; n++){set(commands[n]);}
	for(int n = 0; n < 3; n++){set(alts[n]);}
	for(int n = 0; n < 4; n++){set(directions[n]);}
}

void Pins::set(IO& io)
{
	pinMode(io.pin, io.mode);
	digitalWrite( io.pin, io.state);
}		

Pins::IO& Pins::read(IO& io)
{	
	io.state = digitalRead(io.pin);			
	return io;
}

void Pins::read()
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

void Pins::echo()
{
	Serial.print(F("\n command:"));
	Serial.print(UTILS->getBin(command.address));
	Serial.print(F(" alt:"));
	Serial.print(UTILS->getBin(alt.address));		
	Serial.print(F(" direction:"));
	Serial.print(UTILS->getBin(direction.address));	
}


/*
 * @class Pins
 * @deconstructor
 */ 
Pins::~Pins(){}	
