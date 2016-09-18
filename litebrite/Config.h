#define KAIMANA
//#define LITEBRITE

#ifdef LITEBRITE
	#define data_led 7
#endif

#ifdef KAIMANA
	#define data_led 23		
#endif

#define punch_led 4
#define kick_led 4
#define alt_led 3
#define direction_led 8
#define joystick_led 1

typedef struct {
	int punch[punch_led];
	int kick[kick_led];
	int alt[alt_led];
	int directions[direction_led];
	int joystick[joystick_led];				
} Order;

#define count_led punch_led + kick_led + alt_led + direction_led + joystick_led