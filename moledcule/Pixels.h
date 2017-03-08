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
 * @description include libraries
 */
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(count_led, data_led, NEO_RGB + NEO_KHZ800);

RGB PLATE_RIGHT_COLOR;
RGB PLATE_DOWNRIGHT_COLOR;
RGB PLATE_DOWN_COLOR;
RGB PLATE_DOWNLEFT_COLOR;
RGB PLATE_LEFT_COLOR;
RGB PLATE_UPLEFT_COLOR;
RGB PLATE_UP_COLOR;
RGB PLATE_UPRIGHT_COLOR;

PLATE plate[8] = {
	{black, black, getGRB(PLATE_RIGHT_COLOR, getLong(PLATE_RIGHT))},
	{black, black, getGRB(PLATE_DOWNRIGHT_COLOR, getLong(PLATE_DOWNRIGHT))},
	{black, black, getGRB(PLATE_DOWN_COLOR, getLong(PLATE_DOWN))},
	{black, black, getGRB(PLATE_DOWNLEFT_COLOR, getLong(PLATE_DOWNLEFT))},
	{black, black, getGRB(PLATE_LEFT_COLOR, getLong(PLATE_LEFT))},
	{black, black, getGRB(PLATE_UPLEFT_COLOR, getLong(PLATE_UPLEFT))},
	{black, black, getGRB(PLATE_UP_COLOR, getLong(PLATE_UP))},
	{black, black, getGRB(PLATE_UPRIGHT_COLOR, getLong(PLATE_UPRIGHT))}
};

int pairs[8][2] = {
	{PLATE_RIGHT_INDEX,PLATE_RIGHT_INDEX+1},
	{PLATE_RIGHT_INDEX+1,PLATE_RIGHT_INDEX+2},
	{PLATE_RIGHT_INDEX+2,PLATE_RIGHT_INDEX+3},
	{PLATE_RIGHT_INDEX+3,PLATE_RIGHT_INDEX+4},
	{PLATE_RIGHT_INDEX+4,PLATE_RIGHT_INDEX+5},
	{PLATE_RIGHT_INDEX+5,PLATE_RIGHT_INDEX+6},
	{PLATE_RIGHT_INDEX+6,PLATE_RIGHT_INDEX+7},
	{PLATE_RIGHT_INDEX+7,PLATE_RIGHT_INDEX}
};

int previous = 0;
int reference[13] = {-1,0,2,1,4,-1,3,-1,6,7,-1,-1,5};

unsigned long changed = 0;
float percent = 0;


RGB BALLTOP_COLOR;
RGB BT[1] = {
	getGRB(BALLTOP_COLOR, getLong(BALLTOP))
};

void paintBalltop(int address)
{
	/*
	unsigned int shift = 0;
	unsigned int index = reference[address];		
	if(previous != address){changed = timer.now + duration;}
	if(changed >= timer.now)
	{
		percent = (((float)changed-(float)timer.now)/(float)duration);
		RGB to = BT[1];
		RGB from = black;		
		if(address == 0)
		{
			to = black;
			from = BT[1];
		}

	  BALLTOP_COLOR.r = to.r - from.r;
	  BALLTOP_COLOR.r = to.r - (BALLTOP_COLOR.r*percent);

	  BALLTOP_COLOR.g = to.g - from.g;
	  BALLTOP_COLOR.g = to.g - (BALLTOP_COLOR.g*percent);

	  BALLTOP_COLOR.b = to.b - from.b;
	  BALLTOP_COLOR.b = to.b - (BALLTOP_COLOR.b*percent);			

		pixel.setPixelColor(BALLTOP_INDEX, BALLTOP_COLOR.r, BALLTOP_COLOR.g, BALLTOP_COLOR.b);		
	}
	*/
	pixel.setPixelColor(BALLTOP_INDEX, BALLTOP_COLOR.r, BALLTOP_COLOR.g, BALLTOP_COLOR.b);		
}

void paintPixel(int address)
{
	unsigned int shift = 0;
	unsigned int index = reference[address];

	/*
	 * diagonal shift
	 */
	if(address%3 == 0){shift = 1;}	
	if(address == 9){shift = -7;}

	/*
	 *
	 */
	if(previous != address){changed = timer.now + duration;}
	if(changed >= timer.now)
	{
		percent = (((float)changed-(float)timer.now)/(float)duration);

		for(int n = 0; n < 8; n++)
		{
			RGB to = index == n ? plate[n].to : black;
			RGB from = plate[n].current;

		  plate[n].current.r = to.r - from.r;
		  plate[n].current.r = to.r - (plate[n].current.r*percent);

		  plate[n].current.g = to.g - from.g;
		  plate[n].current.g = to.g - (plate[n].current.g*percent);

		  plate[n].current.b = to.b - from.b;
		  plate[n].current.b = to.b - (plate[n].current.b*percent);			

			pixel.setPixelColor(pairs[n][0], plate[n].current.r, plate[n].current.g, plate[n].current.b);
			pixel.setPixelColor(pairs[n][1], plate[n].current.r, plate[n].current.g, plate[n].current.b);
		}
		for(int n = 0; n < 8; n++)
		{
			if(index == n)
			{	
				pixel.setPixelColor(pairs[n][0], plate[n].current.r, plate[n].current.g, plate[n].current.b);
				pixel.setPixelColor(pairs[n][1], plate[n].current.r, plate[n].current.g, plate[n].current.b);
			}
		}		
	}
	previous = address;
}

void paintPixel(IO& io)
{
	if(io.changed >= timer.now && io.index != -1)
	{
		float percent = (((float)io.changed-(float)timer.now)/(float)duration);		
		
		RGB to = io.state == 0 ? io.to : black;
		RGB from = io.current;

	  io.current.r = to.r - from.r;
	  io.current.r = to.r - (io.current.r*percent);

	  io.current.g = to.g - from.g;
	  io.current.g = to.g - (io.current.g*percent);

	  io.current.b = to.b - from.b;
	  io.current.b = to.b - (io.current.b*percent);

		pixel.setPixelColor(io.index, io.current.g, io.current.r, io.current.b);
		pixel.setPixelColor(io.index+1, io.current.g, io.current.r, io.current.b); 
	}
	else
	{
		if(io.state == 1)
		{
			pixel.setPixelColor(io.index, black.g, black.r, black.b);
			pixel.setPixelColor(io.index+1, black.g, black.r, black.b); 		
		}
	}
}

RGB PK1_COLOR;
RGB PK2_COLOR;
RGB PK3_COLOR;
RGB PK4_COLOR;
RGB CROSS[4] = {
	getGRB(PK1_COLOR, getLong(PK1)), 
	getGRB(PK2_COLOR, getLong(PK2)), 
	getGRB(PK3_COLOR, getLong(PK3)), 
	getGRB(PK4_COLOR, getLong(PK4))
};

void paintCross(IO& PUNCH, IO& KICK, RGB& color)
{	
	if(PUNCH.changed > KICK.changed){KICK.changed = PUNCH.changed;}
	if(KICK.changed > PUNCH.changed){PUNCH.changed = KICK.changed;}

	float percent = (((float)PUNCH.changed-(float)timer.now)/(float)duration);	
	if(PUNCH.changed >= timer.now && PUNCH.index != -1)
	{
		RGB to = PUNCH.state == 0 ? color : black;
		RGB from = PUNCH.current;

	  PUNCH.current.r = to.r - from.r;
	  PUNCH.current.r = to.r - (PUNCH.current.r*percent);

	  PUNCH.current.g = to.g - from.g;
	  PUNCH.current.g = to.g - (PUNCH.current.g*percent);

	  PUNCH.current.b = to.b - from.b;
	  PUNCH.current.b = to.b - (PUNCH.current.b*percent);

		pixel.setPixelColor(PUNCH.index, PUNCH.current.r, PUNCH.current.g, PUNCH.current.b);
		pixel.setPixelColor(PUNCH.index+1, PUNCH.current.r, PUNCH.current.g, PUNCH.current.b); 
	}	

	if(KICK.changed >= timer.now && KICK.index != -1)
	{
		RGB to = KICK.state == 0 ? color : black;
		RGB from = KICK.current;

	  KICK.current.r = to.r - from.r;
	  KICK.current.r = to.r - (KICK.current.r*percent);

	  KICK.current.g = to.g - from.g;
	  KICK.current.g = to.g - (KICK.current.g*percent);

	  KICK.current.b = to.b - from.b;
	  KICK.current.b = to.b - (KICK.current.b*percent);

		pixel.setPixelColor(KICK.index, KICK.current.r, KICK.current.g, KICK.current.b);
		pixel.setPixelColor(KICK.index+1, KICK.current.r, KICK.current.g, KICK.current.b); 
	}					
}

void updatePixels()
{
	timer.now = millis();

	for(int n = 0; n < 4; n++)
	{
		if((PUNCHS[n].state == KICKS[n].state) && PUNCHS[n].state == 0)
		{
			paintCross(PUNCHS[n], KICKS[n], CROSS[n]);
		}
		else
		{
			paintPixel(PUNCHS[n]);
			paintPixel(KICKS[n]);
		}
		if(n < 3){paintPixel(ALTS[n]);}
	}
	if(plate_led > 0)
	{
		paintPixel(DIRECTION.address);		
	}
	if(balltop_led > 0)
	{
		paintBalltop(DIRECTION.address);		
	}		

	delay(5);
	pixel.show();	
}

void hidePixels()
{
	for(int n = 0; n < 4; n++)
	{
		pixel.setPixelColor(PUNCHS[n].index, black.r, black.g, black.b);
		pixel.setPixelColor(KICKS[n].index, black.r, black.g, black.b);
		if(n < 3){pixel.setPixelColor(ALTS[n].index, black.r, black.g, black.b);}
	}
	paintPixel(0);
	
	delay(5);
	pixel.show();		
}