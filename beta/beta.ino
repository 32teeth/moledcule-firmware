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
#include "structs.h"
#include "config.h"
#include "wiring.h"
#include "pins.h"
#include "io.h"
#include "utils.h"
#include "display.h"
#ifdef DEBUG
  #include "serial.h"
#endif

/*
 * @method setup
 * @description main litebrite setup
 */
void setup()
{
	TIMER moledcule = {0,millis(),1000};

  #ifdef DEBUG
    Serial.begin(115200);
    delay(1000);
  #endif

	pixel.begin();
	pixel.setBrightness(bright);

  delay(1000);

  pixel.setPixelColor(0, 0, 255, 255);
  pixel.show();


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
