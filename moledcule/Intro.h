
bool animate = true;
ANIMATION intro = {0,0,500};

int intro_active = 0;
int intro_step = 0;
int intro_loops = 5;
const int intro_elements = 7;

//*/
//int order[wiring] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};

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

void setupIntro()
{

}

void animateSetLED(int index, byte* color)
{
  int single = order[index];
  int twin = leds[index] == 2 ? single + 1 : single;
  pixel.setPixelColor(single, color[0], color[1], color[2]);
  pixel.setPixelColor(twin, color[0], color[1], color[2]);
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
      animateSetLED(wiring-i, intro_colors[i]);
    }		

    /*
     * @description
     */
    int prev_step = intro_step - 1;
    if(intro_step == -1){prev_step = wiring - 1;}
    animateSetLED(prev_step, intro_clear);
    animateSetLED(intro_step, intro_colors[0]);

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
      for(int n = 0; n < intro_elements-1; n++)
      {
        /*
         * @description
         */          
        for(int m = 0; m < 3; m++)
        {
          intro_colors_reset[n][m] = intro_colors[n+1][m];  
        }
      }

      /*
       * @description
       */        
      for(int m = 0; m < 3; m++)
      {
        intro_colors_reset[6][m] = intro_colors[0][m];  
      }      

      /*
       * @description
       */  
      for(int n = 0; n < intro_elements; n++)
      {
        for(int m = 0; m < 3; m++)
        {
          intro_colors[n][m] = intro_colors_reset[n][m];  
        }
      }

      /*
       * @description
       */  
      animateSetLED(0, intro_clear);
      intro_step = 0;

      /*
       * @description
       */  
      intro_loops--;
      if(intro_loops == 0)
      {
        for(int n = 0; n < wiring; n++)
        {
          animateSetLED(n, intro_clear);
        }
        animate = false;        
      }
    } 

    /*
     * @description
     */         
    pixel.show();  
	}
}