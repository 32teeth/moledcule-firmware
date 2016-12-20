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
	for(int i = 0; i < (sizeof(number)*4); i++){result += ((number & (1 << i)) ? "1" : "0");}
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
long int getLong(int r, int g, int b)
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
int* getRGB(long color)
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
COLOR getRGB(COLOR& rgb, long color)
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
COLOR getGRB(COLOR& rgb, long color)
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
String getHEX(long color)
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
	int r = rgb[0];
	int g = rgb[1];
	int b = rgb[2];
	return getHEX(getLong(r,g,b));
}