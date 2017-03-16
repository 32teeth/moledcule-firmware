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
typedef struct __attribute__((__packed__))
{
  volatile unsigned long now;
  volatile unsigned long timestamp;
  volatile unsigned long interval;
} TIMER;
TIMER moledcule;
/*
 * @struct COLOR
 */
typedef struct __attribute__((__packed__))
{
  byte r;
  byte g;
  byte b;
} COLOR;

/*
 * @struct IO
 */
typedef struct __attribute__((__packed__))
{
  byte pin;
  bool state;
  byte index;
  volatile unsigned long changed;
} IO;

/*
 * @struct STATES
 */
typedef struct __attribute__((__packed__))
{
  byte states[4];
  byte address;
  String bin;
} STATES;
