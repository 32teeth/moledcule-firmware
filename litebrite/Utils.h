/*
 * @author Eugene Andruszczenko
 * @version 0.0.5
 * @date created 08/19/16
 * @date updated 09/14/16
 * @description
 */
#include <Arduino.h>

typedef struct{int r;int g;int b;} RGB;

#ifndef Utils_h
#define Utils_h  

/*
 * @class Utils
 * @description 
 */
class Utils
{
	public:
		/*
		 *
		 */
		Utils();

		/*
		 *
		 */		 
		String getBin(int number);

		/*
		 *
		 */
		long int getLong(int r, int g, int b);

		/*
		 *
		 */
		int getRGB(long color);

    /*
     *
     */
    void getRGB(RGB& rgb, long color);
		
		/*
		 *
		 */
		String getHEX(long color);

		/*
		 *
		 */
		String getHEX(int* rgb);

		/*
		 *
		 */
		~Utils();

	private:
};

#endif