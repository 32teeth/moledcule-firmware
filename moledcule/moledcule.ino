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
 * @description
 */

 /*
 *
 */
unsigned long now;
unsigned long timestamp = 0;
const long interval = 100;
const float duration = 100;

/*
 * @description DEBUG
 */
//#define DEBUG

/*
 * @description ACTIVE
 */
//String MODE = "active";

/*
 * @description Config
 */
#include <Arduino.h>

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
 * @description Utils
 */ 
#include "Utils.h"

/*
 * @description Comm
 */ 
#include "Comm.h"

/*
 * @description Pins
 */
#include "Pins.h"

/*
 * @description Pixels
 */
#include "Pixels.h"

/*
 * @description Animation
 */
#include "Intro.h"

/*
 * @description Animation
 */
#include "Animation.h"


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
	printComm("Comm is ready!");

	/*
	 *
	 */
	setPins(); 
}


/*
 * @method setup
 * @description main litebrite loop
 */
void loop()
{
  now = millis();
  if(now - timestamp >= interval)
  {
    getPins();
    timestamp = now;
  };

  updatePixels();

  /*
   *
   */
}
