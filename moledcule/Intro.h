



ANIMATION intro_timing = {0,0,50};

int intro_active = 0;
int intro_step = 0;
int intro_loops = 5;
const int intro_length = 14;

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
//int intro_index[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};

const byte intro_frames[3][3][3] = {
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

void animateIntro()
{
	intro_timing.now = millis();
	if(intro_timing.now - intro_timing.timestamp >= intro_timing.interval)
	{
		intro_timing.timestamp = intro_timing.now;

		for(int i = 0; i < count_led; i++)
		{
			pixel.setPixelColor(i, 0, 0, 0);
		}		

		pixel.setPixelColor(intro_index[intro_length-2], intro_frames[intro_active][0][0], intro_frames[intro_active][0][1], intro_frames[intro_active][0][2]);
		pixel.setPixelColor(intro_index[intro_length-1], intro_frames[intro_active][1][0], intro_frames[intro_active][1][1], intro_frames[intro_active][1][2]);
		pixel.setPixelColor(intro_index[intro_step], intro_frames[intro_active][2][0], intro_frames[intro_active][2][1], intro_frames[intro_active][2][2]);
		pixel.show();			

		intro_step++;
		if(intro_step >= intro_length)
		{
			intro_active++;
			if(intro_active > 2)
			{
				intro_active = 0;
				intro_loops--;
				if(intro_loops != 0)
				{
					animateIntro();
				}
			}				
			intro_step = 0;
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

