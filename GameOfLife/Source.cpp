#include <iostream>
#include "Engine.h"
#include "GOL.h"

Game* CreateGame()
{
	return new GOL();
}