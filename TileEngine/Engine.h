#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "SDL_ttf.h"
#include "SDL.h"
#include "KeyListener.h"

class Engine;

class Game
{
public:
	Engine* engine;

	virtual void SetupWindow(int& width, int& height, int& tileSize) = 0;

	virtual void Create() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

struct Text
{
	SDL_Rect area;
	SDL_Texture* text;
};

class Tile
{
public:
	SDL_Rect tile;
	int red;
	int green;
	int blue;
private:
};

class Engine
{
public:
	Engine(Game* game);
	void AddKeyListener(KeyListener* listener);
	void DrawTile(int xTile, int yTile, int r, int g, int b);
	void DrawText(const char* text, int x, int y, int w, int h);
	void StartLoop();
	void ChangeGame(Game* game);

	int GetWidth() { return WIDTH; }
	int GetHeight() { return HEIGHT; }


	int updateTime;
	int amountOfTiles;

	Game* currentScreen;
	std::vector<KeyListener*> listeners;

private:
	int WIDTH;
	int HEIGHT;
	int TILESIZE;

	Tile* tiles;

	std::vector<Text> textTextures;

	bool running;
	SDL_Event e;
	int lastTime;
	int currentTime;
	int deltaTime;
	int lag;

	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Renderer* renderer;
};

extern Game* CreateGame();
