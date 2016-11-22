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
 * @struct command
 */
COMMAND command = {millis(), millis(), 5000};

/*
 * @struct mode
 */
MODE simple = {"simple", &RIGHT_IO, &P1_IO, true};
MODE tournament = {"tournament", &LEFT_IO, &P1_IO, false};

/*
 * @struct mode array
 * #description the order you put it in is the address of the eeprom
 */
MODE modes[] = {simple, tournament};

/*
 * @method printMode
 * #description debug print
 */
void printMode(char status, MODE mode)
{	
	char buffer[100];
	(String)sprintf(
		buffer,
		"command:%s status:%s direction:%d button:%d active:%s",
		mode.name,
		status,
		mode.direction.state,
		mode.direction.state,
		mode.button.state,
		mode.active ? "true" : "false"
	);		
	Serial.println(buffer);	
};

bool polling = false;
bool waiting = false;

/*
 *
 *
 */
void runMode()
{
	if(simple.active){updatePixels();}
}

/*
 * @method pollMode
 * #description poll all modes
 */
void pollMode()
{
	command.now = millis();

	for(int n = 0; n < sizeof(modes); n++)
	{
		MODE mode = modes[n];

		if(mode.direction.state == 0 && mode.button.state == 0)
		{
			polling = true;
			printMode("polling", mode);

			if(!waiting)
			{
				command.timestamp = command.now + command.interval;
				waiting = true;	
				printMode("waiting", mode);					
			};

			if(command.now - command.timestamp >= command.interval)
			{
				//command.timestamp = millis();
				mode.active != mode.active;
				printMode("set", mode);
				polling = false;
				waiting = false;
				delay(1000);
			};			
		}
	};

	runMode();
};