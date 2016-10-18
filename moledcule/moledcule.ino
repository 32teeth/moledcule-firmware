/*
 * @author Eugene Andruszczenko
 * @version 0.0.5
 * @date created 08/19/16
 * @date updated 09/14/16
 * @description
 */

/*
 * @description DEBUG
 */
#define DEBUG

/*
 * @description Config
 */
#include <Arduino.h>

 /*
 * @description Config
 */
#include "Structures.h"

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
 * @description include libraries
 */
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(count_led, data_led, NEO_GRB + NEO_KHZ800);


/*
 *
 */
unsigned long now;
unsigned long timestamp = 0;
const long interval = 100;


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
	delay(1000);

	/*
	 *
	 */
	startComm();
	listenComm();
	printComm("Comm is ready!");
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
	}
}
