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

                                      +-----+
         +----[PWR]-------------------| USB |--+
         |                            +-----+  |
         |         GND/RST2  [ ][ ]            |
         |       MOSI2/SCK2  [ ][ ]  A5/SCL[ ] |
         |          5V/MISO2 [ ][ ]  A4/SDA[ ] |
         |                             AREF[ ] |
         |                              GND[ ] |
         | [ ]N/C                    SCK/13[ ] |
         | [ ]IOREF                 MISO/12[ ] | Kick 3
         | [ ]RST                   MOSI/11[ ]~| Down
         | [ ]3V3    +---+               10[ ]~| Start
         | [ ]5v    -|   |-               9[ ]~| Select
         | [ ]GND   -| A |-               8[ ] | Home
         | [ ]GND   -| 3 |-                    |
         | [ ]Vin   -| 2 |-               7[ ] |
         |          -| U |-               6[ ]~| Kick 4
      Up | [ ]A0    -| 4 |-               5[ ]~|
    Left | [ ]A1    -|   |-               4[ ] | Kick 1
   Right | [ ]A2     +---+           INT1/3[ ]~| Punch 1
  Kick 2 | [ ]A3                     INT0/2[ ] | Punch 2
         | [ ]A4/SDA  RST SCK MISO     TX>1[ ] | Punch 4
    Data | [ ]A5/SCL  [ ] [ ] [ ]      RX<0[ ] | Punch 3
         |            [ ] [ ] [ ]              |
         |  UNO_R3    GND MOSI 5V  ____________/
         \_______________________/

*/

/*
 * @description Config
 */
#include <Arduino.h>

 /*
 *
 */
unsigned long now;
unsigned long timestamp = 0;
const long interval = 100;
const long duration = 1500;

/*
 * @description DEBUG
 */
#define DEBUG

 /*
 * @description Config
 */
#include "Structures.h"

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
 * @method setup
 * @description main litebrite setup
 */
void setup()
{ 
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
}
