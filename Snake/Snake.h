#pragma once
#include <iostream>
#include <vector>
#include "Engine.h"

struct Body
{
	int x = 0;
	int y = 0;
};

class Snake :
	public Game, public KeyListener
{
public:
	enum DIRECTION {
		UP, DOWN, LEFT, RIGHT
	};

	// Inherited via Game
	virtual void SetupWindow(int& width, int& height, int& tileSize) override;
	virtual void Create() override;
	virtual void Update() override;
	virtual void Render() override;

	// Inherited via KeyListener
	virtual void OnKeyDown(SDL_KeyboardEvent& e) override;
	virtual void OnKeyUp(SDL_KeyboardEvent& e) override;

private:

	void SpawnFood();

	std::vector<Body> snake;
	Body food;

	bool inputGiven;
	bool isDead;

	int score;

	DIRECTION dir;
};