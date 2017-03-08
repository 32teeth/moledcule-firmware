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
 * @description Screen
 */
#include "Screen.h"

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
	timer = {0,millis(),1000};

	/*
	 * @description start pixel and turn them all off
	 */
	pixel.begin();
	pixel.setBrightness(bright);
	for(int i = 0; i < count_led; i++)
	{
		pixel.setPixelColor(i, 0, 0, 0);
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
		timer.interval = 100;
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
	timer.now = millis();
  if(timer.now - timer.timestamp >= timer.interval)
  {
  	timer.timestamp = timer.now;
  };	

	getPins();
	pollMode();
  //updatePixels();
}
