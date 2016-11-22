#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(2, A5, NEO_GRB + NEO_KHZ800);

unsigned long now;
unsigned long timestamp = 0;
const long interval = 100;
const float duration = 100;

/*
 * @struct RGB
 */
typedef struct{int r;int g;int b;} RGB;
typedef struct{int pin;int mode;int state;String type;int index;RGB current;RGB from;RGB to;float changed;} IO; 

RGB black = {0,0,0};
RGB white = {255,255,255};
RGB pink = {255, 29, 142};
RGB violet = {255, 0, 255};
RGB blue = {0, 0, 255};
RGB green = {0, 255, 0};
RGB yellow = {255, 255, 0};
RGB orange = {255, 127, 0};
RGB red = {255, 0 , 0};
IO LED1 = {2, INPUT, HIGH, "d", 0, black, black, violet, 0};
IO LED2 = {3, INPUT, HIGH, "d", 1, black, black, blue, 0}; 
IO LEDS[2] = {LED1, LED2};

/*
 * @method setup
 * @description main moledcule setup
 */
void setup()
{ 
  /*
   * @description start pixel and turn them all off
   */
  pixel.begin();
  pixel.setBrightness(100);
  pixel.show(); 

  pinMode(LED1.pin, LED1.mode);
  digitalWrite(LED1.pin, LED1.state);

  pinMode(LED2.pin, LED2.mode);
  digitalWrite(LED2.pin, LED2.state);  

  Serial.begin(115200);
}


/*
 * @method setup
 * @description main moledcule loop
 */
void loop()
{
  int state;
  
  for(int n = 0; n < 2; n++)
  {
    state = LEDS[n].state;
    LEDS[n].state = digitalRead(LEDS[n].pin);
    if(state != LEDS[n].state){LEDS[n].changed = (now + duration);}    
  }

  now = millis();
  if(now - timestamp >= interval){timestamp = now;};
  //paintPixel();
  fadePixel();
}

void paintPixel()
{
  for(int n = 0; n < 2; n++)
  {
    LEDS[n].current = LEDS[n].state == 0 ? LEDS[n].to : LEDS[n].from;
    pixel.setPixelColor(LEDS[n].index, LEDS[n].current.r, LEDS[n].current.g, LEDS[n].current.b);
  }
  pixel.show();   
}

void fadePixel()
{
  float percent;

  for(int n = 0; n < 2; n++)
  {
    percent = ((LEDS[n].changed-now)/duration);

    if(LEDS[n].changed >= now)
    {
      RGB to = LEDS[n].state == 0 ? LEDS[n].to : black;
      RGB from = LEDS[n].current;

      LEDS[n].current.r = to.r - from.r;
      LEDS[n].current.r = to.r - (LEDS[n].current.r*percent);

      LEDS[n].current.g = to.g - from.g;
      LEDS[n].current.g = to.g - (LEDS[n].current.g*percent);

      LEDS[n].current.b = to.b - from.b;
      LEDS[n].current.b = to.b - (LEDS[n].current.b*percent);

      pixel.setPixelColor(LEDS[n].index, LEDS[n].current.r, LEDS[n].current.g, LEDS[n].current.b);
    }    
  }

  pixel.show();    
}
