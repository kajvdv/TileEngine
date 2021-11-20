#include "Engine.h"
#include "Snake.h"

Game* CreateGame()
{
	return new Snake();
}