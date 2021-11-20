#include "Maze.h"


Maze::Maze(int width, int height)
	: width(width), height(height)
{

}

void Maze::Create()
{
	hallCount = width * height;
	maze = new Hall[hallCount];
	engine->updateTime = 50;
	for (int i = 0; i < hallCount; ++i)
	{
		maze[i].north = false;
		maze[i].east = false;
		maze[i].south = false;
		maze[i].west = false;
		maze[i].visited = false;
	}
	visitedCount = 1;
	maze[0].visited = true;
	visitedHalls.push(0);
	srand(time(nullptr));
}



void Maze::Update()
{
	if (visitedCount == hallCount) return; // does not update if all cells are visited
	auto directions = GetValidDirections();
	if (directions.size() == 0)
	{
		visitedHalls.pop();
	}
	else
	{
		int random = rand() % directions.size();
		int current = visitedHalls.top();
		switch (directions[random])
		{
		case DIRECTION::UP:
			maze[current].north = true;
			maze[current - width].south = true;
			maze[current - width].visited = true;
			visitedHalls.push(current - width);
			break;
		case DIRECTION::RIGHT:
			maze[current].east = true;
			maze[current + 1].west = true;
			maze[current + 1].visited = true;
			visitedHalls.push(current + 1);
			break;
		case DIRECTION::DOWN:
			maze[current].south = true;
			maze[current + width].north = true;
			maze[current + width].visited = true;
			visitedHalls.push(current + width);
			break;
		case DIRECTION::LEFT:
			maze[current].west = true;
			maze[current - 1].east = true;
			maze[current - 1].visited = true;
			visitedHalls.push(current - 1);
			break;
		}
		visitedCount++;
	}
}

void Maze::Render()
{
	for (int Y = 0; Y < height; ++Y)
	{
		for (int X = 0; X < width; ++X)
		{
			DrawHall(X, Y, 255, 255, 255);
		}
	}
	int xHead = visitedHalls.top() % width;
	int yHead = visitedHalls.top() / width;
	DrawHall(xHead, yHead, 255, 0, 0);
}

void Maze::DrawHall(int mazeX, int mazeY, int r, int g, int b)
{
	int screenX = mazeX * 6;
	int screenY = mazeY * 6;
	int index = mazeY * width + mazeX;
	if (maze[index].north)
	{
		engine->DrawTile(screenX + 1, screenY + 0, r, g, b);
		engine->DrawTile(screenX + 2, screenY + 0, r, g, b);
		engine->DrawTile(screenX + 3, screenY + 0, r, g, b);
		engine->DrawTile(screenX + 4, screenY + 0, r, g, b);
	}
	if (maze[index].east)
	{
		engine->DrawTile(screenX + 5, screenY + 1, r, g, b);
		engine->DrawTile(screenX + 5, screenY + 2, r, g, b);
		engine->DrawTile(screenX + 5, screenY + 3, r, g, b);
		engine->DrawTile(screenX + 5, screenY + 4, r, g, b);
	}
	if (maze[index].south)
	{
		engine->DrawTile(screenX + 1, screenY + 5, r, g, b);
		engine->DrawTile(screenX + 2, screenY + 5, r, g, b);
		engine->DrawTile(screenX + 3, screenY + 5, r, g, b);
		engine->DrawTile(screenX + 4, screenY + 5, r, g, b);
	}
	if (maze[index].west)
	{
		engine->DrawTile(screenX + 0, screenY + 1, r, g, b);
		engine->DrawTile(screenX + 0, screenY + 2, r, g, b);
		engine->DrawTile(screenX + 0, screenY + 3, r, g, b);
		engine->DrawTile(screenX + 0, screenY + 4, r, g, b);
	}
	for (int X = 1; X < 5; ++X)
	{
		for (int Y = 1; Y < 5; ++Y)
		{
			engine->DrawTile(screenX + X, screenY + Y, 255, 255, 255);
		}
	}
}

std::vector<DIRECTION> Maze::GetValidDirections()
{
	std::vector<DIRECTION> directionList;
	int x = visitedHalls.top() % width;
	int y = visitedHalls.top() / width;
	int testedX = x;
	int testedY = y - 1;
	if (testedY >= 0)
	{
		if (maze[testedY * width + testedX].visited == false)
		{
			directionList.push_back(DIRECTION::UP);
		}
	}
	testedX = x + 1;
	testedY = y;
	if (testedX < width)
	{
		if (maze[testedY * width + testedX].visited == false)
		{
			directionList.push_back(DIRECTION::RIGHT);
		}
	}
	testedX = x;
	testedY = y + 1;
	if (testedY < height)
	{
		if (maze[testedY * width + testedX].visited == false)
		{
			directionList.push_back(DIRECTION::DOWN);
		}
	}
	testedX = x - 1;
	testedY = y;
	if (testedX >= 0)
	{
		if (maze[testedY * width + testedX].visited == false)
		{
			directionList.push_back(DIRECTION::LEFT);
		}
	}
	return directionList;
}

void Maze::SetupWindow(int& width, int& height, int& tileSize)
{
	width = this->width * 6;
	height = this->height * 6;
	tileSize = 5;
}

void Maze::Move(int mazeX, int mazeY, DIRECTION dir)
{
	int index = mazeY * width + mazeX;
	switch (dir)
	{
	case UP:
		maze[index].north = true;
		maze[index - width].south = true;
		break;
	case RIGHT:
		maze[index].east = true;
		maze[index + 1].west = true;
		break;
	case DOWN:
		maze[index].south = true;
		maze[index + width].north = true;
		break;
	case LEFT:
		maze[index].west = true;
		maze[index - 1].east = true;
		break;
	}
}