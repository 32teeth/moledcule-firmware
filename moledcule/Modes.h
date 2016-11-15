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
COMMAND command{millis(), millis(), 5000};

MODE simple = {"simple", &RIGHT_IO, &P1_IO, false};
MODE tournament = {"tournament", &LEFT_IO, &P1_IO, false};

MODE modes[2] = {simple, tournament};

void pollMode()
{
	bool polling = false;
	bool waiting = false;

	command.now = millis();

	for(int n = 0; n < 2; n++)
	{
		MODE poll = modes[n];

		char buffer[250];
		(String)sprintf(
			buffer,
			"direction:%d button:%d active:",
			poll.direction.state,
			poll.button.state
		);		

		Serial.println(buffer);
	}
	bool poll = false;
	bool wait = false;
	if(P1_IO.state == 0 && LEFT_IO.state == 0)
	{
		poll = true;
		if(!wait)
		{
			command.timestamp = command.now + command.interval;
			wait = true;
		}
		if(command.now - command.timestamp >= command.interval)
		{
			modes.tournament != modes.tournament;
			if(!modes.tournament)
			{
				modes.simple = true;
			}
		};
	}

	if(!poll){command.timestamp = millis();}
	command.now = millis();

	runMode();
}
*/