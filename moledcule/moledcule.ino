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
 *
 */
unsigned long now;
unsigned long timestamp = 0;
unsigned long interval = 100;
unsigned long duration = 10;

/*
 * @description Config
 */
#include <Arduino.h>

/*
 * @description DEBUG
 */
#define DEBUG

 /*
 * @description Config
 */
#include "Structures.h"

 /*
 * @description Colors
 */
#include "Colors.h"

 /*
 * @description Config
 */
#include "Config.h"

/*
 * @description Pattern
 */
#include "Pattern.h"

/*
 * @description Wiring
 */
#include "Wiring.h"

/*
 * @description Define
 */
#include "Define.h"

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
 * @description Pixels
 */
#include "Pixels.h"

/*
 * @description Modes
 */
#include "Modes.h"


/*
 * @method setup
 * @description main litebrite setup
 */
void setup()
{ 
	/*
	 * @description start pixel and turn them all off
	 */
	pixel.begin();
	pixel.setBrightness(bright);
	for(uint8_t n = 0; n < count_led; n++)
	{
		pixel.setPixelColor(n, 0, 0, 0);
	}
	pixel.show();


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

	/*
	 *
	 */
	#ifdef FADE
		interval = 100;
		duration = 1500;
	#endif

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
	pollMode();
}
