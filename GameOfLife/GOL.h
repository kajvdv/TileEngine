#pragma once
#include "Engine.h"
class GOL :
	public Game
{
public:
	int HEIGHT;
	int WIDTH;

	int* currentState;
	int* output;

	GOL();
	virtual void SetupWindow(int& width, int& height, int& tileSize) override;
	virtual void Create() override;
	virtual void Update() override;
	virtual void Render() override;

	int cellValue(int x, int y);
};

