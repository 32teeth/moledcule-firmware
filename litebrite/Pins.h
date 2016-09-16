/*
 * @author Eugene Andruszczenko
 * @version 0.0.5
 * @date created 08/19/16
 * @date updated 09/16/16
 * @description
 */
#include <Arduino.h>
#ifndef Pins_h
#define Pins_h


class Pins
{
	public:
		/*
		 *
		 */
		Pins();

		/*
		 * @struct IO
		 */
		typedef struct{int pin;int mode;int state;String type;} IO;	

		/*
		 * @struct Punch
		 */
		typedef struct{int states[4];int stored[4];int address;String state;} Punch;

		/*
		 * @struct Kick
		 */
		typedef struct{int states[4];int stored[4];int address;String state;} Kick;

		/*
		 * @struct Alt
		 */
		typedef struct{int states[3];int stored[3];int address;String state;} Alt;

		/*
		 * @struct Direction
		 */
		typedef struct{int states[4];int stored[4];int address;String state;} Direction;		

		/*
		 *
		 */
		~Pins();		

	private:
};




#endif