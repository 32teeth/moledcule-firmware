/*
 * @author Eugene Andruszczenko
 * @version 0.0.5
 * @date August 19th, 2016
 * @description - litebrite master 
 */


/*
 * @description Config
 */ 
#include "Config.h"

/*
 * @description include libraries
 */
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(leds, data, NEO_GRB + NEO_KHZ800);

/*
 * @description Utils
 */ 
#include "Utils.h"
Utils *UTILS;

/*
 * @description Pins
 */
#include "Pins.h"
Pins *PINS;

/*
 * @description Comm
 */ 
#include "Comm.h"
Comm *COMM;

/*
 * @description Theme
 */ 
#include "Theme.h"


/*
 *
 */
unsigned long now;
unsigned long timestamp = 0;
const long interval = 500;


/*
 * @method setup
 * @description main litebrite setup
 */
void setup()
{ 
	pixel.begin();
	pixel.setBrightness(50);
	pixel.setPixelColor(0, 0, 0, 255);
	pixel.show();
	UTILS = new Utils();
	PINS = new Pins();
	COMM = new Comm();
	//COMM->start();
  delay(1000);
}


/*
 * @method setup
 * @description main litebrite loop
 */
void loop()
{
	//COMM->listen();
	now = millis();
	if(now - timestamp >= interval)
	{
  	PINS->read();
		timestamp = now;	

		Serial.print(F("\n command:"));
		Serial.print(UTILS->getBin(PINS->command.address));
		Serial.print(F(" alt:"));
		Serial.print(UTILS->getBin(PINS->alt.address));		
		Serial.print(F(" direction:"));
		Serial.print(UTILS->getBin(PINS->direction.address));				
	}
}
