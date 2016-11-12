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

PLATE plate[8] = {
	{black, black, black},
	{black, black, black},
	{black, black, black},
	{black, black, black},
	{black, black, black},
	{black, black, black},
	{black, black, black},
	{black, black, black}
};

void plateInit()
{
	getRGB(plate[0].to, getLong(PLATE_RIGHT));
	getRGB(plate[1].to, getLong(PLATE_DOWNRIGHT));
	getRGB(plate[2].to, getLong(PLATE_DOWN));
	getRGB(plate[3].to, getLong(PLATE_DOWNLEFT));
	getRGB(plate[4].to, getLong(PLATE_LEFT));
	getRGB(plate[5].to, getLong(PLATE_UPLEFT));
	getRGB(plate[6].to, getLong(PLATE_UP));
	getRGB(plate[7].to, getLong(PLATE_UPRIGHT));		
}

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
float changed = now;
void fadePixel(int address)
{
	int shift = 0;
	int index = reference[address];
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
		float percent = ((changed-now)/duration);

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

void fadePixel(IO& io)
{
	if(io.changed >= now && io.index != -1)
	{
		float percent = ((io.changed-now)/duration);		
		
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
}

void paintPixel(IO& io)
{
	io.current = io.state == 0 ? io.to : black;
	pixel.setPixelColor(io.index, io.current.r, io.current.g, io.current.b);
	pixel.setPixelColor(io.index+1, io.current.r, io.current.g, io.current.b);
}

void paintPixel(int address)
{

}

void updatePixels()
{
	#ifdef FADE
		for(int n = 0; n < 4; n++){fadePixel(PUNCHS[n]);}
		for(int n = 0; n < 4; n++){fadePixel(KICKS[n]);}
		for(int n = 0; n < 3; n++){fadePixel(ALTS[n]);}
		fadePixel(DIRECTION.address);
	#else
		for(int n = 0; n < 4; n++){paintPixel(PUNCHS[n]);}
		for(int n = 0; n < 4; n++){paintPixel(KICKS[n]);}
		for(int n = 0; n < 3; n++){paintPixel(ALTS[n]);}	
		paintPixel(DIRECTION.address);
	#endif	

	delay(5);
	pixel.show();			
}