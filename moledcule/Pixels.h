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

void paintPixel(IO& io)
{
	io.current = io.state == 0 ? io.to : io.from;
	pixel.setPixelColor(io.index, io.current.r, io.current.g, io.current.b);
	pixel.setPixelColor(io.index+1, io.current.r, io.current.g, io.current.b);
}

void paintPlate(int address)
{

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

void fadePlate(int address)
{
	int states[8] = {0,0,0,0,0,0,0,0};
	int x = -1;
	int y = -1;
	float changed[8] = {0,0,0,0,0,0,0,0};
	float change;

	switch(address)
	{
		/*
		 * NEUTRAL
		 */
		case 0:
		{
			x = -1; y = -1;
		}
		/*
		 * RIGHT
		 */
		case 1:
			x = 0; y = 1;
		break;
		/*
		 * DOWNRIGHT
		 */
		case 3:
			x = 1; y = 2;
		break;
		/*
		 * DOWN
		 */
		case 2:
			x = 2; y = 3;
		break;	
		/*
		 * DOWNLEFT
		 */
		case 6:
			x = 3; y = 4;
		break;	
		/*
		 * LEFT
		 */
		case 4:
			x = 4;y = 5;
		break;
		/*
		 * UPLEFT
		 */
		case 12:
			x = 5;y = 6;
		break;	
		/*
		 * UP
		 */
		case 8:		
			x = 6;y = 7;
		break;	
		/*
		 * UPRIGHT
		 */
		case 9:
			x = 7;y = 0;
		break;				
	};
	if(x != -1 && y != -1)
	{
		states[x] = 1;
		states[y] = 1;
		change = DIRECTIONS[x].changed > DIRECTIONS[y].changed ? DIRECTIONS[x].changed : DIRECTIONS[y].changed;
		changed[x] = changed[y] = change;		
	}

	for(int n = 0; n < 8; n++)	
	{
		if(changed[n] >= now)
		{
			float percent = ((changed[n]-now)/duration);		
			
			RGB to = states[n] == 1 ? plate[n].to : black;
			RGB from = plate[n].current;
			
		  plate[n].current.r = to.r - from.r;
		  plate[n].current.r = to.r - (plate[n].current.r*percent);

		  plate[n].current.g = to.g - from.g;
		  plate[n].current.g = to.g - (plate[n].current.g*percent);

		  plate[n].current.b = to.b - from.b;
		  plate[n].current.b = to.b - (plate[n].current.b*percent);

			pixel.setPixelColor(PLATE_RIGHT_INDEX + n, plate[n].current.g, plate[n].current.r, plate[n].current.b);
		}		
	}
}

void updatePixels()
{
	#ifdef FADE
		for(int n = 0; n < 4; n++){fadePixel(PUNCHS[n]);}
		for(int n = 0; n < 4; n++){fadePixel(KICKS[n]);}
		for(int n = 0; n < 3; n++){fadePixel(ALTS[n]);}
		for(int n = 0; n < 4; n++){fadePlate(DIRECTION.address);}
	#else
		for(int n = 0; n < 4; n++){paintPixel(PUNCHS[n]);}
		for(int n = 0; n < 4; n++){paintPixel(KICKS[n]);}
		for(int n = 0; n < 3; n++){paintPixel(ALTS[n]);}
		for(int n = 0; n < 4; n++){paintPlate(DIRECTION.address);}			
		paintPlatePixel();
	#endif	

	delay(5);
	pixel.show();			
}