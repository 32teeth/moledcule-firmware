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
 * @web http://moledcule.club
 */

/*
 * @description Config
 */
#include <Arduino.h>

 /*
 *
 */
unsigned long now;
unsigned long timestamp = 0;
const long interval = 1000;
const long duration = 1500;

/*
 * @description DEBUG
 */
#define DEBUG

 /*
 * @description Config
 */
#include "Structures.h"

/*
 * @description Comm
 */ 
#include "Comm.h"

/*
 * @description Utils
 */ 
#include "Utils.h"

/*
 * @description Pins
 */
#include "Pins.h"

/*
 * @method setup
 * @description main litebrite setup
 */
void setup()
{ 
	/*
	 *
	 */
	startComm();
	listenComm();
	printComm("Serial Ready");

	/*
	 *
	 */
	setPins(); 
	delay(1000);
}


/*
 * @method setup
 * @description main litebrite loop
 */
void loop()
{
	now = millis();
  if(now - timestamp >= interval){timestamp = now;};	
	getPins(); 
}
