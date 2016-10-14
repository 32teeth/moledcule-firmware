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
 * @description Pattern
 */
#include "Pattern.h"

/*
 * @description Utils
 */ 
#include "Utils.h"
Utils *UTILS;
RGB color = {0,0,0};

/*
 * @description Comm
 */ 
#include "Comm.h"
Comm *COMM;

/*
 * @description Wiring
 */
#include "Wiring.h"

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

/*
 * @description include libraries
 */
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(count_led, data_led, NEO_GRB + NEO_KHZ800);

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









	int address;
	for(int i = 0; i < length; i++)
	{
		Serial.print("index:");
		Serial.print(i);		
		Serial.print(" order:");
		Serial.print(order[i]);
		Serial.print(" leds:");
		Serial.print(leds[i]);
		Serial.print(" color:");
		Serial.print(colors[i]);
		Serial.print("\n");	

		UTILS->getRGB(color, (long) strtol(colors[i], NULL, 16));

		pixel.setPixelColor(order[i], color.r, color.g, color.b);
		if(leds[i] == 2){pixel.setPixelColor(order[i]+1, color.r, color.g, color.b);}
		pixel.show();	
		delay(100);
	}		

	delay(2500);
}


/*
 * @method setup
 * @description main litebrite loop
 */
void loop()
{
	//COMM->listen();
	/*
	now = millis();
	if(now - timestamp >= interval)
	{
		PINS->get();
		timestamp = now;	
	}
	*/
}
