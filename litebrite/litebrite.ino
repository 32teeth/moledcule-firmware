/*
 * @author Eugene Andruszczenko
 * @version 0.0.5
 * @date created 08/19/16
 * @date updated 09/14/16
 * @description
 */
#define DEBUG

 /*
 * @description Config
 */
#include "Config.h"

/*
 * @description include libraries
 */
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(count_led, data_led, NEO_GRB + NEO_KHZ800);

/*
 * @description Utils
 */ 
#include "Utils.h"
Utils *UTILS;

/*
 * @description Comm
 */ 
#include "Comm.h"
Comm *COMM;

/*
 * @description Config
 */
#include "Theme.h"

/*
 * @description Pins
 */
#include "Pins.h"
Pins *PINS;


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
	/*
	 * @description start pixel and turn them all off
	 */
	pixel.begin();
	pixel.setBrightness(50);
	pixel.setPixelColor(0, 0, 0, 255);
	pixel.show();

	/*
	 * @description create UTILS
	 */
	UTILS = new Utils();

	/*
	 * @description create COMM
	 */	
	COMM = new Comm();
	COMM->start();

	//initPins();
	/*
	 * @description create PINS
	 */	
	PINS = new Pins();	

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
		//readPins();
		timestamp = now;			
	}
}
