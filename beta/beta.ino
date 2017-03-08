#define DEBUG
/*
 * @author Eugene Andruszczenko
 * @version 0.1
 * @date created 03/08/17
 * @date updated 03/08/17
 * @web http://moledcule.club
 */

/*
 * @description Config
 */
#include <Arduino.h>
#include "pixel/pixel.h"
#include "config.h"
#include "structures.h"
#include "wiring.h"
#include "pins.h"
#include "io.h"

TIMER moledcule;
Pixel pixel = Pixel(number_of_leds, data_pin, NEO_RGB + NEO_KHZ800);

/*å∫
 * @method setup
 * @description main litebrite setup
 */
void setup()
{
	TIMER moledcule = {0,millis(),1000};
	delay(1000);
}


/*
 * @method setup
 * @description main litebrite loop
 */
void loop()
{
	moledcule.now = millis();
  if(moledcule.now - moledcule.timestamp >= moledcule.interval)
  {
  	moledcule.timestamp = moledcule.now;
  };
}
