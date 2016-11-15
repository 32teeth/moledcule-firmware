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
COMMAND command = {millis(), millis(), 5000, "simple"};

/*
 * @struct mode
 */
MODE simple = {"simple", &RIGHT_IO, &P1_IO, false};
MODE tournament = {"tournament", &LEFT_IO, &P1_IO, false};

#define mode_count 2

/*
 * @struct mode array
 */
MODE modes[mode_count] = {simple, tournament};

/*
 * @method printMode
 * #description debig print
 */
void printMode(MODE mode)
{
	char buffer[250];	
	(String)sprintf(
		buffer,
		"waiting polling direction:%d button:%d active:%s",
		mode.direction.state,
		mode.button.state,
		mode.active ? "true" : "false"
	);		
	Serial.println(buffer);	
};

/*
 * @method pollMode
 * #description poll all modes
 */
void pollMode()
{
	bool polling = false;
	bool waiting = false;

	command.now = millis();

	for(int n = 0; n < mode_count; n++)
	{
		MODE mode = modes[n];

		if(mode.direction.state == 0 && mode.button.state == 0)
		{
			polling = true;

			printMode(mode);

			if(!waiting)
			{
				command.timestamp = command.now + command.interval;
				waiting = true;	
				printMode(mode);					
			};
			if(command.now - command.timestamp >= command.interval)
			{
				command.timestamp = millis();
				printMode(mode);	
				if(!mode.active)
				{
					simple.active = true;
				}
			};			
		}
	};

	command.now = millis();

	//runMode();
};