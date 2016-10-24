#include <Adafruit_NeoPixel.h>

#define PIN A5
#define PIXELS 24
#define BRIGHTNESS 50

Adafruit_NeoPixel pixel = Adafruit_NeoPixel(PIXELS, PIN, NEO_GRB + NEO_KHZ800);

/*
 * @struct RGB
 */
typedef struct{unsigned long now;unsigned long timestamp;const long interval;} ANIMATION;

/*
 * @struct RGB
 */
typedef struct{int r;int g;int b;} RGB;

RGB black = {0,0,0};
RGB white = {255,255,255};
RGB pink = {255, 29, 142};
RGB violet = {255, 0, 255};
RGB blue = {0, 0, 255};
RGB green = {0, 255, 0};
RGB yellow = {255, 255, 0};
RGB orange = {255, 127, 0};
RGB red = {255, 0 , 0};

void setup() {
  pixel.begin();
  pixel.setBrightness(BRIGHTNESS);
  
  for(int n = 0; n < PIXELS; n++)
  {
    pixel.setPixelColor(n, black.r, black.g, black.b);
  }
  
  pixel.show();
  animateSet();
}

void loop() {
  animateIntro();
}

ANIMATION intro_timing = {0,0,100};

int intro_active = 0;
int intro_step = 0;
int intro_loops = 5;
const int intro_elements = 7;
const int intro_length = 24;

int intro_index[intro_length];

byte intro_colors[intro_elements][3] = {
  {pink.r, pink.g, pink.b},  
  {violet.r, violet.g, violet.b},
  {blue.r, blue.g, blue.b},
  {green.r, green.g, green.b},
  {yellow.r, yellow.g, yellow.b},
  {orange.r, orange.g, orange.b},
  {red.r, red.g, red.b}    
};

void animateSet()
{
  for(int n = 0; n < intro_length; n++)
  {
    intro_index[n] = n;
  }
}

void animateIntro()
{
  intro_timing.now = millis();
  if(intro_timing.now - intro_timing.timestamp >= intro_timing.interval)
  {
    intro_timing.timestamp = intro_timing.now;

    for(int n = intro_elements; n > 0; n--)
    {
      int i = n - 1;
      pixel.setPixelColor(intro_index[intro_length-i], intro_colors[i][0], intro_colors[i][1], intro_colors[i][2]);
    }

    int prev_step = intro_step - 1;
    if(intro_step == -1)
    {intro_step = intro_length - 1;}
    
    pixel.setPixelColor(intro_index[prev_step], black.r, black.g, black.b);    
    pixel.setPixelColor(intro_index[intro_step], intro_colors[0][0], intro_colors[0][1], intro_colors[0][2]);

    pixel.show();

    intro_step++;
    if(intro_step > (intro_length - intro_elements))
    {
      byte intro_colors_reset[intro_elements][3] = {
        {intro_colors[1][0], intro_colors[1][1], intro_colors[1][2]},
        {intro_colors[2][0], intro_colors[2][1], intro_colors[2][2]},
        {intro_colors[3][0], intro_colors[3][1], intro_colors[3][2]},
        {intro_colors[4][0], intro_colors[4][1], intro_colors[4][2]},
        {intro_colors[5][0], intro_colors[5][1], intro_colors[5][2]},
        {intro_colors[6][0], intro_colors[6][1], intro_colors[6][2]},
        {intro_colors[0][0], intro_colors[0][1], intro_colors[0][2]}
      };
      for(int n = 0; n < intro_elements; n++)
      {
        intro_colors[n][0] = intro_colors_reset[n][0];
        intro_colors[n][1] = intro_colors_reset[n][1];
        intro_colors[n][2] = intro_colors_reset[n][2];
      }

      pixel.setPixelColor(intro_index[intro_length-intro_elements], black.r, black.g, black.b);
      intro_step = 0;
    }     
  }  
}



