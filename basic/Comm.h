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
** @method startComm
** @desc start serial port if DEBUG is defined
*/
void startComm()
{
	#ifdef DEBUG
	  Serial.begin(115200);
	  //while (!Serial) ;
	  delay(1000);
  #endif
};

/*
** @method listenComm
** @desc listen to serial port if DEBUG is defined
*/
void listenComm()
{
  if(Serial.available() > 0)
  {
    String data = Serial.readStringUntil('\n');
    String message;
  }
};

/*
** @method printComm
** @param str (String)
** @desc print string to serial port if DEBUG is defined
*/
void printComm(String str)
{
	#ifdef DEBUG
		Serial.println(str);
	#endif
};