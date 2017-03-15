/*
 * @author Eugene Andruszczenko
 * @version 0.1
 * @date created 03/08/17
 * @date updated 03/08/17
 * @web http://moledcule.club
 */

/*
 * @struct timer
 */
typedef struct{unsigned long now;unsigned long timestamp;unsigned long interval;} TIMER;
TIMER moledcule;
/*
 * @struct COLOR
 */
typedef struct{byte r;byte g;byte b;} COLOR;

/*
 * @struct IO
 */
typedef struct{byte pin;byte state;byte index;long changed;} IO;
