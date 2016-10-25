



ANIMATION intro_timing = {0,0,500};

int intro_active = 0;
int intro_step = 0;
int intro_loops = 5;
const int intro_elements = 7;
const int intro_length = 14;

///*
int intro_index[intro_length] = {
	P1_INDEX,
	P2_INDEX,
	P3_INDEX,
	K3_INDEX,
	K2_INDEX,
	K1_INDEX,
	PLATE_RIGHT_INDEX,
	PLATE_DOWNRIGHT_INDEX,
	PLATE_DOWN_INDEX,
	PLATE_DOWNLEFT_INDEX,
	PLATE_LEFT_INDEX,
	PLATE_UPLEFT_INDEX,
	PLATE_UP_INDEX,
	PLATE_UPRIGHT_INDEX
};
//*/
//int intro_index[intro_length] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};

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
    if(intro_step == -1){prev_step = intro_length - 1;}
      
    pixel.setPixelColor(intro_index[prev_step], black.r, black.g, black.b);    
    pixel.setPixelColor(intro_index[intro_step], intro_colors[0][0], intro_colors[0][1], intro_colors[0][2]);

    intro_step++;
    if(intro_step > (intro_length - intro_elements))
    {
      for(int n = 0; n < intro_elements-1; n++)
      {
        for(int m = 0; m < 3; m++)
        {
          intro_colors_reset[n][m] = intro_colors[n+1][m];  
        }
      }
      for(int m = 0; m < 3; m++)
      {
        intro_colors_reset[6][m] = intro_colors[0][m];  
      }      


      for(int n = 0; n < intro_elements; n++)
      {
        for(int m = 0; m < 3; m++)
        {
          intro_colors[n][m] = intro_colors_reset[n][m];  
        }
      }

      pixel.setPixelColor(intro_index[0], black.r, black.g, black.b);
      intro_step = 0;
    }    
    pixel.show();   
	}
}

