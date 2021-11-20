#pragma once
#include <array>
#include <stack>
#include <chrono>
#include <iostream>
#include <random>
#include "Engine.h"

struct Hall
{
	bool north, east, south, west, visited;
};

enum DIRECTION {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

class Maze :
	public Game
{
public:
	Maze(int width, int height);
private:
	int width;
	int height;

	Hall* maze;
	int hallCount;

	int visitedCount;
	std::stack<int> visitedHalls;

	// Inherited via Game
	virtual void Create() override;

	virtual void Update() override;

	virtual void Render() override;

	virtual void SetupWindow(int& width, int& height, int& tileSize) override;

	void DrawHall(int mazeX, int mazeY, int r, int g, int b);

	void Move(int mazeX, int mazeY, DIRECTION dir);

	std::vector<DIRECTION> GetValidDirections();

};

Game* CreateGame()
{
	return new Maze(20, 20);
}

