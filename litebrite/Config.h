#define KAIMANA

#ifdef LITEBRITE
	#define data_led 7
#endif

#ifdef KAIMANA
	#define data_led A5		
#endif

#define bright 25

#define punch_led 4
#define kick_led 4
#define alt_led 3
#define direction_led 8
#define joystick_led 1

#define count_led punch_led + kick_led + alt_led + direction_led + joystick_led