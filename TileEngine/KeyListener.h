#pragma once

#include "SDL.h"

struct SDL_KeyboardEvent;

class KeyListener
{
public:
	virtual void OnKeyDown(SDL_KeyboardEvent& e) = 0;
	virtual void OnKeyUp(SDL_KeyboardEvent& e) = 0;
};