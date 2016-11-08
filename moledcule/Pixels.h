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

void paintPixel(IO& io, bool pair)
{
	io.current = io.state == 0 ? io.to : io.from;
	pixel.setPixelColor(io.index, io.current.r, io.current.g, io.current.b);
	if(pair)
	{
		pixel.setPixelColor(io.index+1, io.current.r, io.current.g, io.current.b);
	}	
}

void fadePixel(IO& io, bool pair)
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
		if(pair)
		{
			pixel.setPixelColor(io.index+1, io.current.g, io.current.r, io.current.b); 
		}	
	}
}

void paintPlatePixel()
{
	DIRECTIONS[0].index = PLATE_RIGHT_INDEX;
	DIRECTIONS[1].index = PLATE_DOWN_INDEX;
	DIRECTIONS[2].index = PLATE_LEFT_INDEX;
	DIRECTIONS[3].index = PLATE_UP_INDEX;
	switch(DIRECTION.address)
	{
		default:
		case 0:
			DIRECTIONS[0].index = PLATE_RIGHT_INDEX;
			DIRECTIONS[1].index = PLATE_DOWN_INDEX;
			DIRECTIONS[2].index = PLATE_LEFT_INDEX;
			DIRECTIONS[3].index = PLATE_UP_INDEX;
		break;
		case 1:
			DIRECTIONS[0].index = PLATE_RIGHT_INDEX;
			paintPixel(DIRECTIONS[0], true);
		break;
		case 3:
			DIRECTIONS[0].index = PLATE_DOWNRIGHT_INDEX;
			paintPixel(DIRECTIONS[0], false);
			paintPixel(DIRECTIONS[1], false);
		break;			
		case 2:
			DIRECTIONS[1].index = PLATE_DOWN_INDEX;
			paintPixel(DIRECTIONS[1], true);
		break;
		case 6:
			DIRECTIONS[2].index = PLATE_DOWNLEFT_INDEX;
			paintPixel(DIRECTIONS[1], false);
			paintPixel(DIRECTIONS[2], false);
		break;				
		case 4:
			DIRECTIONS[2].index = PLATE_LEFT_INDEX;
			paintPixel(DIRECTIONS[2], true);
		break;
		case 12:
			DIRECTIONS[2].index = PLATE_UPLEFT_INDEX;
			paintPixel(DIRECTIONS[2], false);
			paintPixel(DIRECTIONS[3], false);
		break;
		case 8:
			DIRECTIONS[3].index = PLATE_UP_INDEX;
			paintPixel(DIRECTIONS[3], true);
		break;
		case 9:
			DIRECTIONS[3].index = PLATE_UPRIGHT_INDEX;
			paintPixel(DIRECTIONS[3], false);
			paintPixel(DIRECTIONS[0], false);
		break;									
	}
}

void fadePlatePixel()
{
	DIRECTIONS[0].index = PLATE_RIGHT_INDEX;
	DIRECTIONS[1].index = PLATE_DOWN_INDEX;
	DIRECTIONS[2].index = PLATE_LEFT_INDEX;
	DIRECTIONS[3].index = PLATE_UP_INDEX;
	switch(DIRECTION.address)
	{
		default:
		case 0:
			DIRECTIONS[0].index = PLATE_RIGHT_INDEX;
			DIRECTIONS[1].index = PLATE_DOWN_INDEX;
			DIRECTIONS[2].index = PLATE_LEFT_INDEX;
			DIRECTIONS[3].index = PLATE_UP_INDEX;
		break;
		case 1:
			DIRECTIONS[0].index = PLATE_RIGHT_INDEX;
			paintPixel(DIRECTIONS[0], true);
		break;
		case 3:
			DIRECTIONS[0].index = PLATE_DOWNRIGHT_INDEX;
			paintPixel(DIRECTIONS[0], false);
			paintPixel(DIRECTIONS[1], false);
		break;			
		case 2:
			DIRECTIONS[1].index = PLATE_DOWN_INDEX;
			paintPixel(DIRECTIONS[1], true);
		break;
		case 6:
			DIRECTIONS[2].index = PLATE_DOWNLEFT_INDEX;
			paintPixel(DIRECTIONS[1], false);
			paintPixel(DIRECTIONS[2], false);
		break;				
		case 4:
			DIRECTIONS[2].index = PLATE_LEFT_INDEX;
			paintPixel(DIRECTIONS[2], true);
		break;
		case 12:
			DIRECTIONS[2].index = PLATE_UPLEFT_INDEX;
			paintPixel(DIRECTIONS[2], false);
			paintPixel(DIRECTIONS[3], false);
		break;
		case 8:
			DIRECTIONS[3].index = PLATE_UP_INDEX;
			paintPixel(DIRECTIONS[3], true);
		break;
		case 9:
			DIRECTIONS[3].index = PLATE_UPRIGHT_INDEX;
			paintPixel(DIRECTIONS[3], false);
			paintPixel(DIRECTIONS[0], false);
		break;									
	}
}

void updatePixels()
{
	#ifdef FADE
		for(int n = 0; n < 4; n++){fadePixel(PUNCHS[n], true);}
		for(int n = 0; n < 4; n++){fadePixel(KICKS[n], true);}
		for(int n = 0; n < 3; n++){fadePixel(ALTS[n], true);}
		fadePlatePixel();
	#else
		for(int n = 0; n < 4; n++){paintPixel(PUNCHS[n], true);}
		for(int n = 0; n < 4; n++){paintPixel(KICKS[n], true);}
		for(int n = 0; n < 3; n++){paintPixel(ALTS[n], true);}
		paintPlatePixel();
	#endif	

	delay(5);		
	pixel.show();			
}