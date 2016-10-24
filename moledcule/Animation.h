
ANIMATION animate = {0,0,50};

//int stick[20] = {P1_INDEX, P1_INDEX + 1, P2_INDEX, P2_INDEX + 1, P3_INDEX, P3_INDEX + 1, K3_INDEX, K3_INDEX + 1, K2_INDEX, K2_INDEX + 1, K1_INDEX, K1_INDEX + 1,PLATE_RIGHT_INDEX,PLATE_DOWNRIGHT_INDEX,PLATE_DOWN_INDEX,PLATE_DOWNLEFT_INDEX,PLATE_LEFT_INDEX,PLATE_UPLEFT_INDEX,PLATE_UP_INDEX,PLATE_UPRIGHT_INDEX};
int stick[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};

RGB red = {255,0,0};
RGB green = {0,255,0};
RGB blue = {0,0,255};
RGB yellow = {255,255,0};
RGB purple = {255,0,255};
RGB cyan = {0,255,255};
RGB black = {0,0,0};

const byte frames[3][3][3] = {
	{
		{red.r, red.g, red.b},
		{green.r, green.g, green.b},
		{blue.r, blue.g, blue.b}
	},
	{	
		{blue.r, blue.g, blue.b},
		{red.r, red.g, red.b},
		{green.r, green.g, green.b}
	},
	{
		{green.r, green.g, green.b},
		{blue.r, blue.g, blue.b},
		{red.r, red.g, red.b}
	}
};

int active = 0;
int step = 0;

void animation()
{
	animate.now = millis();
	if(animate.now - animate.timestamp >= animate.interval)
	{
		animate.timestamp = animate.now;

		for(int i = 0; i < 20; i++)
		{
			pixel.setPixelColor(i, 0, 0, 0);
		}		

		pixel.setPixelColor(stick[18], frames[active][0][0], frames[active][0][1], frames[active][0][2]);
		pixel.setPixelColor(stick[19], frames[active][1][0], frames[active][1][1], frames[active][1][2]);
		pixel.setPixelColor(stick[step], frames[active][2][0], frames[active][2][1], frames[active][2][2]);
		pixel.show();			

		step++;
		if(step >= 18)
		{
			active++;
			if(active > 2)
			{
				active = 0;
			}				
			step = 0;
		}	
		/*
		for(int n = 0; n < 6; n++)
		{
			int r = frames[current_frame][n][0];
			int g = frames[current_frame][n][1];
			int b = frames[current_frame][n][2];

			pixel.setPixelColor(index[n], r, g, b);
			pixel.setPixelColor(index[n] + 1, r, g, b);
			pixel.show();
		}

		current_frame++;
		if(current_frame >= total_frames)
		{
			current_frame = 0;
		}		
		*/
	}
}

