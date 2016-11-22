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
 * @description Config
 */
#include <Arduino.h>

/*
** @method getBin
** @param number (int)
** @return result {String} 
** @desc converts the decimal param to binary string
*/
String getBin(int number)
{	
	String result = "";
	for(char i = 0; i < (sizeof(number)*4); i++){result += ((number & (1 << i)) ? "1" : "0");}
	return result;
}


/*
** @method getLong
** @desc convert rgb values to long int
** @param r {int} red value
** @param g {int} red value
** @param b {int} red value
** @return {long}
*/
long int getLong(char r, char g, char b)
{
	return (unsigned long)r << 16 | (unsigned long)g << 8 | (unsigned long)b;
}

/*
** @method getLong
** @desc convert hex values to long
** @param color {hex} hex value represantation of color
** @return {long}
*/
long int getLong(String color)
{
  long number = (long) strtol( &color[0], NULL, 16);	
  return number;
}

/*
** @method getRGB
** @desc convert long values to rgb array
** @param color {long} long value represantation of color
** @return {int*}
*/
int* getRGB(unsigned long color)
{
	int r = (color>>16);
	int g = ((color>>8) & 0xff);
	int b = (color & 0xff);
	int rgb[3] = {r,g,b};
	return rgb;
}

/*
** @method getRGB
** @desc convert long values to rgb array
** @param color {long} long value represantation of color
** @return {int*}
*/
RGB getRGB(RGB& rgb, unsigned long color)
{
	rgb.r = (color>>16);
	rgb.g = ((color>>8) & 0xff);
	rgb.b = (color & 0xff);

	return rgb;
}

/*
** @method getRGB
** @desc convert long values to rgb array
** @param color {long} long value represantation of color
** @return {int*}
*/
RGB getGRB(RGB& rgb, unsigned long color)
{
	rgb.g = (color>>16);
	rgb.r = ((color>>8) & 0xff);
	rgb.b = (color & 0xff);

	return rgb;
}

/*
** @method getHEX
** @desc convert long values to rgb array
** @param color {long} long value represantation of color
** @return {String}
*/
String getHEX(unsigned long color)
{
	return String(color, HEX);
}

/*
** @method getHEX
** @desc convert long values to rgb array
** @param color {long} long value represantation of color
** @return {String}
*/
String getHEX(int* rgb)
{
	char r = rgb[0];
	char g = rgb[1];
	char b = rgb[2];
	return getHEX(getLong(r,g,b));
}
