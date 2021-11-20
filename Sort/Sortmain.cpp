#include "Engine.h"
#include "Sort.h"

Game* CreateGame()
{
	return new Sort(100, 80);
}