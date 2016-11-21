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
	if(previous != address){changed = now + duration;}
	if(changed >= now)
	{
		percent = (((float)changed-(float)now)/(float)duration);
		for(uint8_t n = 0; n < 8; n++)
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
		for(uint8_t n = 0; n < 8; n++)
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
	if(io.changed >= now && io.index != -1)
	{
		float percent = (((float)io.changed-(float)now)/(float)duration);	
		
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
RGB CROSS[4] = {PK1_COLOR, PK2_COLOR, PK3_COLOR, PK4_COLOR};

void paintCross(IO& PUNCH, IO& KICK, RGB& color)
{
	IO x[2] = {PUNCH, KICK};
	for(uint8_t n = 0; n < 2; n++)
	{
		IO io = x[2];
		if(io.changed >= now && io.index != -1)
		{
			float percent = ((io.changed-now)/duration);		
			
			RGB to = io.state == 0 ? color : black;
			RGB from = io.current;

		  io.current.r = color.r - from.r;
		  io.current.r = color.r - (io.current.r*percent);

		  io.current.g = color.g - from.g;
		  io.current.g = color.g - (io.current.g*percent);

		  io.current.b = color.b - from.b;
		  io.current.b = color.b - (io.current.b*percent);

			pixel.setPixelColor(io.index, io.current.g, io.current.r, io.current.b);
			pixel.setPixelColor(io.index+1, io.current.g, io.current.r, io.current.b); 
		}
	}
}

void updatePixels()
{
	for(uint8_t n = 0; n < 4; n++){paintPixel(PUNCHS[n]);}
	for(uint8_t n = 0; n < 4; n++){paintPixel(KICKS[n]);}
	for(uint8_t n = 0; n < 3; n++){paintPixel(ALTS[n]);}
	paintPixel(DIRECTION.address);

	delay(5);
	pixel.show();	
}

void hidePixels()
{
	for(uint8_t n = 0; n < count_led; n++)
	{
		pixel.setPixelColor(n, 0, 0, 0);
	}
}