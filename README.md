# TileEngine
This is a small tile based engine I made with SDL and C++. The engine can be used to make very small games and to visualize algoritms. The repository has four examples for the usage of this engine. They all implement the game interface defined in Engine.h. The examples also implement the CreateGame function defined in the engine class, that will be called by the engine to start running the game.

# Explanation
The tile-engine contains the gameloop and provides an interface for drawing the tiles. It defines an interface for the engine to interact with. The engine also hides the main-function by declaring an external CreateGame function that acts as the entry point for the concrete Game-objects and returns the concrete Game-object for the engine to run. The examples implement the Game-interface and define the CreateGame function. The Game-interface contains a reference to the engine for the concretions to interact with.

# Installation
Visual Studio required:

Download the zip file and unpack it.

Open the solution file.

In the solution explorer press right click on the solution and press build.

Run each individual project (except for the TileEngine itself) by right clicking on the project -> debug -> start new instance

-------------------------------------------------------------------------------------

Or download the executables together with the .dll's
