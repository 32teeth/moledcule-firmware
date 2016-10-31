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
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(count_led, data_led, NEO_GRB + NEO_KHZ800);

void paintPixel(IO& io)
{
	io.current = io.state == 0 ? io.to : io.from;
	pixel.setPixelColor(io.index, io.current.r, io.current.g, io.current.b);
	pixel.setPixelColor(io.index+1, io.current.r, io.current.g, io.current.b);
}

void fadePixel(IO& io)
{
	float percent = ((io.changed-now)/duration);

	if(io.changed >= now)
	{
		RGB to = io.state == 0 ? io.to : black;
		RGB from = io.current;

	  io.current.r = to.r - from.r;
	  io.current.r = to.r - (io.current.r*percent);

	  io.current.g = to.g - from.g;
	  io.current.g = to.g - (io.current.g*percent);

	  io.current.b = to.b - from.b;
	  io.current.b = to.b - (io.current.b*percent);

		pixel.setPixelColor(io.index, io.current.r, io.current.g, io.current.b);
		pixel.setPixelColor(io.index+1, io.current.r, io.current.g, io.current.b); 
	}
}

void updatePixels()
{
	#ifdef FADE
		for(int n = 0; n < 4; n++){paintPixel(PUNCHS[n]);}
		for(int n = 0; n < 4; n++){paintPixel(KICKS[n]);}
		for(int n = 0; n < 3; n++){paintPixel(ALTS[n]);}
		for(int n = 0; n < 4; n++){paintPixel(DIRECTIONS[n]);}
	#else
		for(int n = 0; n < 4; n++){fadePixel(PUNCHS[n]);}
		for(int n = 0; n < 4; n++){fadePixel(KICKS[n]);}
		for(int n = 0; n < 3; n++){fadePixel(ALTS[n]);}
		for(int n = 0; n < 4; n++){fadePixel(DIRECTIONS[n]);}
	#endif	

	pixel.show();
}