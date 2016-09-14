/*
 * @author Eugene Andruszczenko
 * @version 0.0.5
 * @date created 08/19/16
 * @date updated 09/14/16
 * @description
 */

#ifndef Pins_h
#define Pins_h
#include <Arduino.h>
/*
 * @class Pins
 * @description 
 */
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
		typedef struct {
			byte pin;
			byte mode;
			byte state;
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
		IO P1;IO P2;IO P3;IO P4;IO K1;IO K2;IO K3;IO K4;
		
		/*
		 * @description alts
		 */		
		IO START;IO SELECT;IO HOME;

		/*
		 * @description directions
		 */
		IO RIGHT;IO DOWN;IO LEFT;IO UP;

		/*
		 * @description array of IO
		 */
		IO commands[8];
		IO alts[3];
		IO directions[4];

		/*
		 * @description
		 */
		Command command;
    Alt alt;
    Direction direction; 

		void read();

		/*
		 *
		 */
		~Pins();

	private:
		/*
		 *
		 */
		void set();

		/*
		 *
		 */
		void set(IO& io);	

		/*
		 *
		 */
		IO& read(IO& io);	
};

#endif