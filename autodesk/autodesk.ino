/*
 * @author Eugene Andruszczenko
 * @version 0.0.5
 * @date created 08/19/16
 * @date updated 09/14/16
 * @description
 */
#define DEBUG

/*
*/
#define KAIMANA
//#define LITEBRITE

#ifdef LITEBRITE
  #define data_led 7
#endif

#ifdef KAIMANA
  #define data_led A5   
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

/*
 * @author Eugene Andruszczenko
 * @version 0.0.5
 * @date created 08/19/16
 * @date updated 09/14/16
 * @description
 */

/*
 * @class Utils
 * @description 
 */
class Utils
{
  public:

    int block;

    /*
     * @class Utils
     * @constructor
     */ 
    Utils()
    {

    }

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

    
    ~Utils();


  private:
};

/*
 * @class Comm
 * @description 
 */
class Comm
{
  public:

    /*
     *
     */
    Comm();

    void start();
    void listen();
    void print(String str);

    /*
     *
     */
    ~Comm();

  private:    
};

/*
 * @class Comm
 * @constructor
 */ 
Comm::Comm()
{
  this->listen();   
}

void Comm::start()
{
  Serial.begin(115200);
  while (!Serial) ;
  delay(1000);
};

void Comm::listen()
{
  if(Serial.available() > 0)
  {
    String data = Serial.readStringUntil('\n');
    String message;
  }
};

void Comm::print(String str)
{
  Serial.println(str);
};

/*
 * @class Comm
 * @deconstructor
 */ 
Comm::~Comm(){} 

/*
 * @struct IO
 */
typedef struct{int pin;int mode;int state;String type;} IO; 

/*
 * @struct Punch
 */
typedef struct{int states[4];int stored[4];int address;String state;} Punch;

/*
 * @struct Kick
 */
typedef struct{int states[4];int stored[4];int address;String state;} Kick;

/*
 * @struct Alt
 */
typedef struct{int states[3];int stored[3];int address;String state;} Alt;

/*
 * @struct Direction
 */
typedef struct{int states[4];int stored[4];int address;String state;} Direction;    



class Pins
{
  public:
    /*
     *
     */
    Pins();

    /*
     *
     */
    void set();
    void set(IO& io);

    void get();
    void get(IO& io);   

    /*
     *
     */
    ~Pins();    

  private:
};

/*
 * @description punchs
 */
IO P1 = {3, INPUT, HIGH, "d"};
IO P2 = {2, INPUT, HIGH, "d"};
IO P3 = {0, INPUT, HIGH, "d"};
IO P4 = {1, INPUT, HIGH, "d"};
/*
 * @description kicks
 */
IO K1 = {4, INPUT, HIGH, "d"};
IO K2 = {A3, INPUT, HIGH, "a"};
IO K3 = {12, INPUT, HIGH, "d"};
IO K4 = {6, INPUT, HIGH, "d"};

/*
 * @description alts
 */   
IO START = {10, INPUT, HIGH, "d"};    
IO SELECT = {9, INPUT, HIGH, "d"};
IO HOME = {8, INPUT, HIGH, "d"};

/*
 * @description directions
 */
IO RIGHT = {A2, INPUT, HIGH, "a"};
IO DOWN = {11, INPUT, HIGH, "d"};   
IO LEFT = {A1, INPUT, HIGH, "a"};
IO UP = {A0, INPUT, HIGH, "a"};

/*
 * @description array of IO
 */
IO punchs[4] = {P1, P2, P3, P4};
IO kicks[4] = {K1, K2, K3, K4};
IO alts[3] = {START, SELECT, HOME};
IO directions[4] = {RIGHT, DOWN, LEFT, UP}; 

/*
 * @description
 */
Punch punch = {{0,0,0,0},{0,0,0,0},0,"0"};
Kick kick = {{0,0,0,0},{0,0,0,0},0,"0"};
Alt alt = {{0,0,0},{0,0,0},0,"0"};
Direction direction = {{0,0,0,0},{0,0,0,0},0,"0"};

/*
 * @class Pins
 * @constructor
 */ 
Pins::Pins()
{
  this->set();
}

void Pins::set()
{
  for(int n = 0; n < 4; n++){set(punchs[n]);}
  for(int n = 0; n < 4; n++){set(kicks[n]);}
  for(int n = 0; n < 3; n++){set(alts[n]);}
  for(int n = 0; n < 4; n++){set(directions[n]);} 
}

void Pins::set(IO& io)
{
  pinMode(io.pin, io.mode);
  digitalWrite(io.pin, io.state);
}

void Pins::get()
{
  punch.address = 0;
  for(int n = 0; n < 4; n++)
  {
    get(punchs[n]);
    punch.states[n] = punchs[n].state;
    punch.address |= punch.states[n] == 0 ? 1 << n : 0 << n;
  } 

  kick.address = 0;
  for(int n = 0; n < 4; n++)
  {
    get(kicks[n]);
    kick.states[n] = kicks[n].state;
    kick.address |= kick.states[n] == 0 ? 1 << n : 0 << n;
  }   

  alt.address = 0;
  for(int n = 0; n < 3; n++)
  {
    get(alts[n]);
    alt.states[n] = alts[n].state;
    alt.address |= alt.states[n] == 0 ? 1 << n : 0 << n;        
  }     

  direction.address = 0;
  for(int n = 0; n < 4; n++)
  {
    get(directions[n]);
    direction.states[n] = directions[n].state;    
    direction.address |= direction.states[n] == 0 ? 1 << n : 0 << n;  
  }
  
  /*
   *
   */
  Serial.print(F("\n punch:"));    
  Serial.print(punch.address);   
  Serial.print(F(" kick:"));   
  Serial.print(kick.address);
  Serial.print(F(" alt:"));   
  Serial.print(alt.address);
  Serial.print(F(" direction:"));   
  Serial.print(direction.address);
}

void Pins::get(IO& io)
{
  io.state = digitalRead(io.pin);
  
}

/*
 * @class Pins
 * @deconstructor
 */ 
Pins::~Pins(){}


 /*
 * @description Config
 */
//#include "Config.h"

/*
 * @description include libraries
 */
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, 8, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

/*
 * @description Utils
 */ 
//#include "Utils.h"
Utils *UTILS;

/*
 * @description Comm
 */ 
//#include "Comm.h"
Comm *COMM;

/*
 * @description Config
 */
//#include "Theme.h"

/*
 * @description Pins
 */
//#include "Pins.h"
Pins *PINS;


/*
 *
 */
unsigned long now;
unsigned long timestamp = 0;
const long interval = 100;


typedef struct{
  int red;
  int green;
  int blue; 
} RGB;

RGB rgb_to_0 {random(0, 255), random(0, 255), random(0, 255)};
RGB rgb_from_0 {rgb_to_0.red, rgb_to_0.blue, rgb_to_0.green};
RGB rgb_shift_0 {rgb_to_0.red, rgb_to_0.blue, rgb_to_0.green};

RGB rgb_to_1 {random(0, 255), random(0, 255), random(0, 255)};
RGB rgb_from_1 {rgb_to_1.red, rgb_to_1.blue, rgb_to_1.green};
RGB rgb_shift_1 {rgb_to_1.red, rgb_to_1.blue, rgb_to_1.green};

RGB rgb_to_2 {random(0, 255), random(0, 255), random(0, 255)};
RGB rgb_from_2 {rgb_to_2.red, rgb_to_2.blue, rgb_to_2.green};
RGB rgb_shift_2 {rgb_to_2.red, rgb_to_2.blue, rgb_to_2.green};

RGB rgb_to_3 {random(0, 255), random(0, 255), random(0, 255)};
RGB rgb_from_3 {rgb_to_3.red, rgb_to_3.blue, rgb_to_3.green};
RGB rgb_shift_3 {rgb_to_3.red, rgb_to_3.blue, rgb_to_3.green};

RGB rgb_to_4 {random(0, 255), random(0, 255), random(0, 255)};
RGB rgb_from_4 {rgb_to_4.red, rgb_to_4.blue, rgb_to_4.green};
RGB rgb_shift_4 {rgb_to_4.red, rgb_to_4.blue, rgb_to_4.green};

RGB rgb_to_5 {random(0, 255), random(0, 255), random(0, 255)};
RGB rgb_from_5 {rgb_to_5.red, rgb_to_5.blue, rgb_to_5.green};
RGB rgb_shift_5 {rgb_to_5.red, rgb_to_5.blue, rgb_to_5.green};

/*
 * @method setup
 * @description main litebrite setup
 */
void setup()
{ 
  /*
   * @description start pixel and turn them all off
   */
  /*
  pixel.begin();
  pixel.setBrightness(10);
  pixel.setPixelColor(0, rgb_shift_0.red, rgb_shift_0.green, rgb_shift_0.blue);
  pixel.setPixelColor(1, rgb_shift_1.red, rgb_shift_1.green, rgb_shift_1.blue);
  pixel.setPixelColor(2, rgb_shift_2.red, rgb_shift_2.green, rgb_shift_2.blue);
  pixel.setPixelColor(3, rgb_shift_3.red, rgb_shift_3.green, rgb_shift_3.blue);
  pixel.setPixelColor(4, rgb_shift_4.red, rgb_shift_4.green, rgb_shift_4.blue);
  pixel.setPixelColor(5, rgb_shift_5.red, rgb_shift_5.green, rgb_shift_5.blue);
  pixel.show();
  */
  /*
   * @description create UTILS
   */
  UTILS = new Utils();

  /*
   * @description create COMM
   */ 
  COMM = new Comm();
  COMM->start();

  //initPins();
  /*
   * @description create PINS
   */ 
  PINS = new Pins();  

  /*
  Serial.println("count_led:");
  Serial.print(count_led);

  Serial.print(" data_led:");
  Serial.print(data_led); 
  */

  delay(1000);
  
}

/*
 * @method setup
 * @description main litebrite loop
 */
float changed;
float duration = interval/4;

void loop()
{
  //COMM->listen();
  now = millis();
  if(now - timestamp >= interval)
  {
    PINS->get();
    timestamp = now;  
  }
}

void crossfade(int led)
{ 
  float percent = ((changed-now)/duration);

  RGB to;
  RGB from;
  RGB shift;
  switch (led) {
    case 0:
      to = rgb_to_0;
      from = rgb_from_0;
      shift = rgb_shift_0;
    break;
    case 1:
      to = rgb_to_1;
      from = rgb_from_1;
      shift = rgb_shift_1;
    break;
    case 2:
      to = rgb_to_2;
      from = rgb_from_2;
      shift = rgb_shift_2;
    break;    
    case 3:
      to = rgb_to_3;
      from = rgb_from_3;
      shift = rgb_shift_3;
    break;
    case 4:
      to = rgb_to_4;
      from = rgb_from_4;
      shift = rgb_shift_4;
    break;
    case 5:
      to = rgb_to_5;
      from = rgb_from_5;
      shift = rgb_shift_5;
    break;

  }
  shift.red = to.red - from.red;
  shift.red = to.red - (shift.red*percent);

  shift.green = to.green - from.green;
  shift.green = to.green - (shift.green*percent);

  shift.blue = to.blue - from.blue;
  shift.blue = to.blue - (shift.blue*percent);  

  Serial.print("\nled:");
  Serial.print(led);  
  Serial.print(" red:");
  Serial.print(shift.red);
  Serial.print(" green:");
  Serial.print(shift.red);
  Serial.print(" blue:");
  Serial.print(shift.red);

  pixel.setPixelColor(led, shift.red, shift.green, shift.blue);
  pixel.show();
  
  delay(1);
}

