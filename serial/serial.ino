/*
 * @description include libraries
 */
#define count_led 20
#define data_led 23
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(count_led, data_led, NEO_GRB + NEO_KHZ800);

/*
 * @struct RGB
 */
typedef struct{int r;int g;int b;} RGB;
RGB color = {255,0,154};

void setup() {
  /*
   * @description start pixel and turn them all off
   */
  pixel.begin();
  pixel.setBrightness(100);
  pixel.setPixelColor(0, 0, 0, 0);
  pixel.show();
    
  Serial.begin(115200);
  //while (!Serial) ;
  delay(1000);
}
int address;
void loop() {

  if(Serial.available() > 0)
  {
    address = Serial.parseInt();
    address -= address % 2;
    Serial.println(address);
    for(int i = 0; i < count_led; i++)
    {
      pixel.setPixelColor(i, 0, 0, 0);
    }         
    pixel.setPixelColor(address, color.r, color.g, color.b);
    pixel.setPixelColor(address + 1, color.r, color.g, color.b);
    pixel.show();
  }
}
