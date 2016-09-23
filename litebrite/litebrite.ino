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
#include "Pattern.h"

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
const long interval = 100;

RGB rgb = {0,0,0};

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
	pixel.setPixelColor(0, 255, 0, 0);
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
			
	long punch[4] = {P1, P2, P3, P4};
	for(int i = 0; i < punch_led; i++)
	{
		UTILS->getRGB(rgb, (long) strtol(punch[i], NULL, 16));
		pixel.setPixelColor(i, rgb.r, rgb.g, rgb.b);
		pixel.show();	
		delay(50);	
	}

	long kick[4] = {K1, K2, K3, K4};
	for(int i = punch_led; i < punch_led + kick_led; i++)
	{
		UTILS->getRGB(rgb, (long) strtol(kick[i-punch_led], NULL, 16));
		pixel.setPixelColor(i, rgb.r, rgb.g, rgb.b);
		pixel.show();	
		delay(50);	
	}		

  /*
  long number = (long) strtol(P1, NULL, 16);
  int r = (number >> 16);
  int g = ((number >> 8) & 0xFF);
  int b = (number & 0xFF);
	*/

	//pixel.setPixelColor(0, rgb[0], rgb[1], rgb[2]);
	//pixel.show();	    		
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
		PINS->get();
		timestamp = now;	
	}
}