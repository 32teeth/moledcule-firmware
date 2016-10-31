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

bool animate = false;
ANIMATION intro = {0,0,250};

int intro_active = 0;
int intro_step = 0;
const int intro_elements = 7;
int intro_loops = intro_elements;

//*/
//int order[wiring] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
int intro_order[wiring] = {P1_INDEX,P2_INDEX,P3_INDEX,K3_INDEX,K2_INDEX,K1_INDEX,PLATE_RIGHT_INDEX,PLATE_DOWNRIGHT_INDEX,PLATE_DOWN_INDEX,PLATE_DOWNLEFT_INDEX,PLATE_LEFT_INDEX,PLATE_UPLEFT_INDEX,PLATE_UP_INDEX,PLATE_UPRIGHT_INDEX};

byte intro_clear[3] = {0,0,0};

byte intro_colors[intro_elements][3] = {
  {pink.r, pink.g, pink.b},  
  {violet.r, violet.g, violet.b},
  {blue.r, blue.g, blue.b},
  {green.r, green.g, green.b},
  {yellow.r, yellow.g, yellow.b},
  {orange.r, orange.g, orange.b},
  {red.r, red.g, red.b}    
};

byte intro_colors_reset[intro_elements][3] = {};



void animateSetPixel(int index, byte* color)
{
  int single = intro_order[index];
  pixel.setPixelColor(single, color[0], color[1], color[2]);
  if(leds[index] == 2)
  {
    pixel.setPixelColor(single+1, color[0], color[1], color[2]);
  }
}

void setupIntro()
{

}

void animateIntro()
{
  /*
   * @description
   */
	intro.now = millis();
	if(intro.now - intro.timestamp >= intro.interval)
	{
    /*
     * @description reset timestamp
     */   
		intro.timestamp = intro.now;

    /*
     * @description set the rainbow
     */
    for(int n = intro_elements; n > 0; n--)
    {
      int i = n - 1;
      animateSetPixel(wiring-i, intro_colors[i]);
    }	
    animateSetPixel(wiring-intro_elements, intro_clear);

    /*
     * @description
     */
    int prev_step = intro_step - 1;
    if(intro_step == -1){prev_step = wiring - 1;}
    animateSetPixel(prev_step, intro_clear);
    animateSetPixel(intro_step, intro_colors[0]);

    /*
     * @description
     */
    intro_step++;

    /*
     * @description
     */    
    if(intro_step > (wiring - intro_elements))
    {
      /*
       * @description
       */        
      for(int n = 0; n < intro_elements-1; n++){for(int m = 0; m < 3; m++){intro_colors_reset[n][m] = intro_colors[n+1][m];};};

      /*
       * @description
       */        
      for(int m = 0; m < 3; m++){intro_colors_reset[6][m] = intro_colors[0][m];};

      /*
       * @description
       */ 
      for(int n = 0; n < intro_elements; n++){for(int m = 0; m < 3; m++){intro_colors[n][m] = intro_colors_reset[n][m];};};

      /*
       * @description
       */  
      animateSetPixel(0, intro_clear);

      intro_step = 0;


      /*
       * @description
       */  
      /*
      intro_loops--;
      if(intro_loops == 0)
      {
        for(int n = 0; n < wiring; n++)
        {
          animateSetPixel(n, intro_clear);
        }
        pixel.show();
        animate = false;
      }
      */
    } 

    /*
     * @description
     */         
    pixel.show(); 
	}
}