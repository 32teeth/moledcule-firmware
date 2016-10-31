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
	RGB color = io.state == 1 ? io.to : io.from;
	pixel.setPixelColor(io.index, color.r, color.g, color.b);
	pixel.setPixelColor(io.index+1, color.r, color.g, color.b);
}

void fadePixel(IO& io)
{

}

void updatePixels()
{
	#ifdef FADE

		/*
		 * punch
		 */
		for(int n = 0; n < 4; n++){paintPixel(PUNCHS[n]);}

		/*
		 * kick
		 */
		for(int n = 0; n < 4; n++){paintPixel(KICKS[n]);}

		/*
		 * alt
		 */	
		for(int n = 0; n < 3; n++){paintPixel(ALTS[n]);}

		/*
		 * directions
		 */	
		for(int n = 0; n < 4; n++){paintPixel(DIRECTIONS[n]);}		
		
	#else
		
	#endif	
}