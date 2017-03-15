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
TIMER command = {0, millis(), 2500};


/*
 * @struct mode
 */
MODE active = {"simple", 0, 0, true};
MODE pending = {"none", 0, 0, false};

#define mode_count 5

/*
 * @struct mode array
 */
MODE modes[mode_count+2] = {
	{"simple", RIGHT_PIN, P1_PIN, false},
	{"tournament", LEFT_PIN, P1_PIN, false},
	{"screen", UP_PIN, P1_PIN, false},
	{"xbox", LEFT_PIN, K1_PIN, false},
	{"playstation", LEFT_PIN, K2_PIN, false}
};

void runMode()
{
  if(active.name == "tournament"){hidePixels();}
  if(active.name == "simple"){updatePixels();}
  if(active.name == "screen"){screenSaver();}
  if(active.name == "xbox"){xbox();}
  if(active.name == "playstation"){playstation();}
}

/*
 * @method setMode
 * #description set mode
 */
void setMode()
{
	for(int n = 0; n < mode_count; n++)
	{
		MODE& mode = modes[n];
		if(mode.name != active.name){mode.active = false;}
		//screenSaver();
		for(int n = count_led; n > 0; n--)
		{
			pixel.setPixelColor(n, black.r, black.g, black.b);
			pixel.show();
		}
	}

	int alloff = mode_count;
	for(int n = 0; n < mode_count; n++)
	{
		MODE& mode = modes[n];
		if(mode.active){alloff--;}
	}

	if(alloff == 0)
	{
		active.name = "simple";
		modes[0].active = true;
	}
}

bool waiting = false;
/*
 * @method pollMode
 * #description poll all modes
 */
void pollMode()
{
	command.now = millis();
	for(int n = 0; n < mode_count; n++)
	{
		MODE& mode = modes[n];

		if(getPin(mode.direction) == 0 && getPin(mode.button) == 0)
		{
			if(pending.name != mode.name)
			{
				command.timestamp = command.now;
				pending.name = mode.name;
			}
			if(!waiting)
			{
				command.timestamp = command.now;
				pending.name = mode.name;
				waiting = true;
			}
			if(command.now - command.timestamp >= command.interval && waiting)
			{
				mode.active = mode.active ? false : true;
				if(mode.active){active.name = mode.name;}
				command.timestamp = millis();
				waiting = false;
				setMode();
				delay(10);
			}
		}
	};

	command.now = millis();

	runMode();
};
