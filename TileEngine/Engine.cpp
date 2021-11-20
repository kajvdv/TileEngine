#include "Engine.h"


Engine::Engine(Game* game)
{
	lastTime = 0;
	currentTime = 0;
	deltaTime = 0;
	lag = 0;
	updateTime = 0;
	running = true;

	game->SetupWindow(WIDTH, HEIGHT, TILESIZE);
	currentScreen = game;
	currentScreen->engine = this;

	amountOfTiles = WIDTH * HEIGHT;
	tiles = new Tile[amountOfTiles];

	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			tiles[y * WIDTH + x].tile.x = x * TILESIZE;
			tiles[y * WIDTH + x].tile.y = y * TILESIZE;
			tiles[y * WIDTH + x].tile.w = TILESIZE;
			tiles[y * WIDTH + x].tile.h = TILESIZE;
			tiles[y * WIDTH + x].red = 0;
			tiles[y * WIDTH + x].green = 0;
			tiles[y * WIDTH + x].blue = 0;
		}
	}
}

void Engine::StartLoop()
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	window = SDL_CreateWindow("TileEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH * TILESIZE, HEIGHT * TILESIZE, 0);
	surface = SDL_GetWindowSurface(window);
	renderer = SDL_CreateSoftwareRenderer(surface);

	currentScreen->Create();

	lastTime = SDL_GetTicks();

	while (running)
	{
		currentTime = SDL_GetTicks();
		deltaTime = currentTime - lastTime;

		// Get user Input
		while (SDL_PollEvent(&e) == !0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				for (KeyListener* l : listeners)
				{
					l->OnKeyDown(e.key);
				}
				break;
			case SDL_KEYUP:
				for (KeyListener* l : listeners)
				{
					l->OnKeyUp(e.key);
				}
				break;
			}
		}
		// Update Game with a fixed timestep
		if (updateTime != 0)
		{
			lag += deltaTime;
			while (lag >= updateTime)
			{
				currentScreen->Update();
				lag -= updateTime;
			}
		}
		// Render Game
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		textTextures.clear();
		for (int i = 0; i < amountOfTiles; i++)
		{
			tiles[i].red = 0;
			tiles[i].green = 0;
			tiles[i].blue = 0;
		}
		//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		currentScreen->Render();
		for (int i = 0; i < amountOfTiles; i++)
		{
			SDL_SetRenderDrawColor(renderer, tiles[i].red, tiles[i].green, tiles[i].blue, 255);
			SDL_RenderFillRect(renderer, &((tiles + i)->tile));
		}
		// drawing grid
		/*SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
		for (int i = 0; i < amountOfTiles; i++)
		{
			SDL_RenderDrawRect(renderer, &tiles[i].tile);
		}*/
		// drawing text
		for (Text t : textTextures)
		{
			SDL_RenderCopy(renderer, t.text, NULL, &t.area);
		}
		SDL_UpdateWindowSurface(window);
		//SDL_RenderPresent(renderer);
		lastTime = currentTime;
	}
	SDL_Quit();
}

void Engine::AddKeyListener(KeyListener* listener)
{
	listeners.push_back(listener);
}

void Engine::ChangeGame(Game* game)
{
	currentScreen = game;
	currentScreen->engine = this;
	currentScreen->Create();
}


void Engine::DrawTile(int xTile, int yTile, int r, int g, int b)
{
	tiles[yTile * WIDTH + xTile].red = r;
	tiles[yTile * WIDTH + xTile].green = g;
	tiles[yTile * WIDTH + xTile].blue = b;
}

void Engine::DrawText(const char* text, int x, int y, int w, int h)
{
	TTF_Font* sans = TTF_OpenFont("..\\TileEngine\\LucidaTypewriterRegular.ttf", 50);
	SDL_Color white = { 255,255,255 };
	SDL_Surface* textSurface = TTF_RenderText_Solid(sans, text, white);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect r;
	r.x = x;
	r.y = y;
	r.h = h;
	r.w = w;
	Text t = { r, textTexture };
	textTextures.push_back(t);
}

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char* args[])
{
	Engine engine(CreateGame());
	engine.StartLoop();
	return 0;
}