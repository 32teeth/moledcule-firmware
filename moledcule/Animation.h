/*
 *
 */

ANIMATION animate = {0,0,250};

RGB red = {255,0,0};
RGB green = {0,255,0};
RGB blue = {0,0,255};
RGB black = {0,0,0};

int index[6] = {P1_INDEX, P2_INDEX, P3_INDEX, K3_INDEX, K2_INDEX, K1_INDEX};
int current_frame = 0;
int total_frames = 12;

const byte frames[12][6][3] PROGMEM = {
	// blue shift
	{
		{red.r, red.g, red.b},
		{green.r, green.g, green.b},
		{blue.r, blue.g, blue.b},
		{black.r, black.g, black.b},
		{black.r, black.g, black.b},
		{black.r, black.g, black.b}
	},
	{
		{red.r, red.g, red.b},
		{green.r, green.g, green.b},
		{black.r, black.g, black.b},
		{blue.r, blue.g, blue.b},
		{black.r, black.g, black.b},
		{black.r, black.g, black.b}
	},
	{
		{red.r, red.g, red.b},
		{green.r, green.g, green.b},
		{black.r, black.g, black.b},
		{black.r, black.g, black.b},
		{blue.r, blue.g, blue.b},
		{black.r, black.g, black.b}
	},
	{
		{red.r, red.g, red.b},
		{green.r, green.g, green.b},
		{black.r, black.g, black.b},
		{black.r, black.g, black.b},
		{black.r, black.g, black.b},
		{blue.r, blue.g, blue.b}
	},
	// green shift
	{
		{blue.r, blue.g, blue.b},
		{red.r, red.g, red.b},
		{green.r, green.g, green.b},
		{black.r, black.g, black.b},
		{black.r, black.g, black.b},
		{black.r, black.g, black.b}
	},
	{
		{blue.r, blue.g, blue.b},
		{red.r, red.g, red.b},
		{black.r, black.g, black.b},
		{green.r, green.g, green.b},
		{black.r, black.g, black.b},
		{black.r, black.g, black.b}
	},
	{
		{blue.r, blue.g, blue.b},
		{red.r, red.g, red.b},
		{black.r, black.g, black.b},
		{black.r, black.g, black.b},
		{green.r, green.g, green.b},
		{black.r, black.g, black.b}
	},
	{
		{blue.r, blue.g, blue.b},
		{red.r, red.g, red.b},
		{black.r, black.g, black.b},
		{black.r, black.g, black.b},
		{black.r, black.g, black.b},
		{green.r, green.g, green.b}
	},
	// red shift
	{
		{green.r, green.g, green.b},
		{blue.r, blue.g, blue.b},
		{red.r, red.g, red.b},
		{black.r, black.g, black.b},
		{black.r, black.g, black.b},
		{black.r, black.g, black.b}
	},
	{
		{green.r, green.g, green.b},
		{blue.r, blue.g, blue.b},
		{black.r, black.g, black.b},
		{red.r, red.g, red.b},
		{black.r, black.g, black.b},
		{black.r, black.g, black.b}
	},
	{
		{green.r, green.g, green.b},
		{blue.r, blue.g, blue.b},
		{black.r, black.g, black.b},
		{black.r, black.g, black.b},
		{red.r, red.g, red.b},
		{black.r, black.g, black.b}
	},
	{
		{green.r, green.g, green.b},
		{blue.r, blue.g, blue.b},
		{black.r, black.g, black.b},
		{black.r, black.g, black.b},
		{black.r, black.g, black.b},
		{red.r, red.g, red.b}
	}
};

void animation()
{
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
}

