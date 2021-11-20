#pragma once
#include <iostream>
#include "Engine.h"

class Sort :
	public Game
{
public:
	Sort(int amountOfValues, int maxValue);

private:
	// Inherited via Game
	virtual void SetupWindow(int& width, int& height, int& tileSize) override;
	virtual void Create() override;
	virtual void Update() override;
	virtual void Render() override;

	int amountOfValues;
	int maxValue;

	int* values;
	int index;
	int counter;
};

