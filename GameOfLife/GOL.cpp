#include "GOL.h"

GOL::GOL()
{
	WIDTH = 80;
	HEIGHT = 90;
	
}

void GOL::SetupWindow(int& width, int& height, int& tileSize)
{
	width = WIDTH;
	height = HEIGHT;
	tileSize = 5;
}

void GOL::Create()
{
	engine->updateTime = 50;
	currentState = new int[WIDTH * HEIGHT];
	output = new int[WIDTH * HEIGHT];
	memset(currentState, 0, WIDTH * HEIGHT * sizeof(int));
	memset(output, 0, WIDTH * HEIGHT * sizeof(int));

	for (int i = 0; i < WIDTH * HEIGHT; i++)
		currentState[i] = rand() % 2;
		
}

void GOL::Update()
{
	// Counting neighbours of each cell
	// If cell is active:
		// Dies when the amount of active neighbours is less than 2
		// Dies when the amount of active neighbours is more than 3
	// If cell is dead:
		// Activates when it has 3 active neighboars

	for (int i = 0; i < WIDTH * HEIGHT; i++)
		output[i] = currentState[i];

	for (int x = 1; x < WIDTH - 1; x++)
		for (int y = 1; y < HEIGHT - 1; y++)
		{
			// Counting neighbours
			int buren = cellValue(x - 1, y - 1) + cellValue(x - 0, y - 1) + cellValue(x + 1, y - 1) +
						cellValue(x - 1, y - 0) +          0         +		cellValue(x + 1, y - 0) +
						cellValue(x - 1, y + 1) + cellValue(x - 0, y + 1) + cellValue(x + 1, y + 1);

			if (cellValue(x, y) == 1)
			{
				currentState[WIDTH * y + x] = buren == 2 || buren == 3;
			}
			else
			{
				currentState[WIDTH * y + x] = buren == 3;
			}
		}
}

void GOL::Render()
{
	for (int x = 1; x < WIDTH - 1; x++)
		for (int y = 1; y < HEIGHT - 1; y++)
		{
			if (cellValue(x, y) == 1)
			{
				engine->DrawTile(x, y, 255, 255, 255);
			}
		}
}

int GOL::cellValue(int x, int y)
{
	return output[WIDTH * y + x];
}