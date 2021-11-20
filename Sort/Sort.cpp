#include "Sort.h"

Sort::Sort(int amountOfValues, int maxValue)
	: amountOfValues(amountOfValues), maxValue(maxValue)
{

}

void Sort::SetupWindow(int& width, int& height, int& tileSize)
{
	width = amountOfValues;
	height = maxValue;
	tileSize = 10;
}

void Sort::Create()
{
	engine->updateTime = 20;
	values = new int[amountOfValues];
	for (int i = 0; i < amountOfValues; ++i)
	{
		values[i] = rand() % maxValue + 1;
	}
	index = 0;
	counter = amountOfValues - 1;
}

void Sort::Update()
{
	if (values[index] > values[index + 1])
	{
		int temp = values[index];
		values[index] = values[index + 1];
		values[index + 1] = temp;
	}
	if (index == counter)
	{
		index = 0;
		counter--;
	}
	else
	{ 
		index++;
	}
}

void Sort::Render()
{
	for (int i = 0; i < amountOfValues; ++i)
	{
		for (int j = maxValue - values[i]; j < maxValue; j++)
		{
			if (i == index)
			{
				engine->DrawTile(i, j, 0, 255, 0);
			}
			else
			{
				engine->DrawTile(i, j, 255, 255, 255);
			}
		}
	}
}
