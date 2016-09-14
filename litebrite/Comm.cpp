/*
 * @author Eugene Andruszczenko
 * @version 0.0.5
 * @date created 08/19/16
 * @date updated 09/14/16
 * @description
 */

 
/*
 * @description Comm include files
 */
#include "Comm.h"

/*
 * @class Comm
 * @constructor
 */ 
Comm::Comm()
{
	this->listen();   
}

void Comm::start()
{
  Serial.begin(115200);
  while (!Serial) ;
  delay(1000);
};

void Comm::listen()
{
  if(Serial.available() > 0)
  {
    String data = Serial.readStringUntil('\n');
    String message;
  }
};


/*
 * @class Comm
 * @deconstructor
 */ 
Comm::~Comm(){}	