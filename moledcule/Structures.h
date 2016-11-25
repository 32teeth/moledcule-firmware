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
 * @struct RGB
 */
typedef struct{int r;int g;int b;} RGB;

/*
 * @struct PLATE
 */
typedef struct{RGB current; RGB from; RGB to;} PLATE;

/*
 * @struct IO
 */
typedef struct{int pin;int mode;int state;String type;int index;RGB current;RGB from;RGB to;long changed;} IO;	

/*
 * @struct Punch
 */
typedef struct{int states[4];int address;String bin;} Punch;

/*
 * @struct Kick
 */
typedef struct{int states[4];int address;String bin;} Kick;

/*
 * @struct Alt
 */
typedef struct{int states[3];int address;String bin;} Alt;

/*
 * @struct Direction
 */
typedef struct{int states[4];int address;String bin;} Direction;	
