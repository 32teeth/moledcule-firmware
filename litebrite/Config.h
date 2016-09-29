#define KAIMANA
#ifdef LITEBRITE
	#define data_led 7
#endif

#ifdef KAIMANA
	#define data_led 23		
#endif

#define bright 100

#define punch_led 3
#define kick_led 3
#define alt_led 2
#define balltop_led 0
#define plate_led 8
#define controller_led 0

#define count_led punch_led + kick_led + alt_led + plate_led + balltop_led + controller_led

#define controller FIGHTSTICK						
/*
 EOF
*/