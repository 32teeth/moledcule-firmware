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
typedef struct{uint8_t r;uint8_t g;uint8_t b;} RGB;

/*
 * @struct PLATE
 */
typedef struct{RGB current; RGB from; RGB to;} PLATE;

/*
 * @struct IO
 */
typedef struct{uint8_t pin;uint8_t mode;uint8_t state;String type;uint8_t index;RGB current;RGB from;RGB to;unsigned long changed;} IO;	

/*
 * @struct Punch
 */
typedef struct{uint8_t states[4];uint8_t address;String bin;} Punch;

/*
 * @struct Kick
 */
typedef struct{uint8_t states[4];uint8_t address;String bin;} Kick;

/*
 * @struct Alt
 */
typedef struct{uint8_t states[3];uint8_t address;String bin;} Alt;

/*
 * @struct Direction
 */
typedef struct{uint8_t states[4];uint8_t address;String bin;} Direction;	

/*
 * @struct MODE
 */
//typedef struct{String name; IO direction; IO button; bool active;} MODE;

/*
 * @struct COMMAND
 */
//typedef struct{unsigned long now;unsigned long timestamp;const long interval; String mode;} COMMAND;
