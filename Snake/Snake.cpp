#include "Snake.h"

void Snake::SetupWindow(int& width, int& height, int& tileSize)
{
	width = 30;
	height = 30;
	tileSize = 20;
}

void Snake::SpawnFood()
{
	bool isInSnake = false;
	do
	{
		food.x = rand() % engine->GetWidth();
		food.y = rand() % engine->GetHeight();
		for (Body& b : snake)
		{
			if (b.x == food.x && b.y == food.y)
			{
				isInSnake = true;
				std::cout << "Food is inside snake" << std::endl;
				break;
			}
			else
			{
				isInSnake = false;
			}
		}
	} while (isInSnake);
}

void Snake::Create()
{
	engine->AddKeyListener(this);
	snake.clear();
	score = 0;
	dir = DIRECTION::RIGHT;
	engine->updateTime = 60;
	Body head;
	head.x = 4;
	head.y = 4;
	snake.push_back(head);
	head.x = 3;
	snake.push_back(head);
	head.x = 2;
	snake.push_back(head);
	SpawnFood();
	inputGiven = false;
	isDead = false;
}

void Snake::Update()
{
	if (snake.size() > 1)
	{
		for (int i = snake.size() - 1; i > 0; i--)
		{
			snake[i].x = snake[i - 1].x;
			snake[i].y = snake[i - 1].y;
		}
	}
	if (dir == DIRECTION::UP) snake[0].y -= 1;
	if (dir == DIRECTION::DOWN) snake[0].y += 1;
	if (dir == DIRECTION::LEFT) snake[0].x -= 1;
	if (dir == DIRECTION::RIGHT) snake[0].x += 1;
	for (Body& b : snake)
	{
		if (b.x < 0) b.x = engine->GetWidth() - 1;
		if (b.x > engine->GetWidth() - 1) b.x = 0;
		if (b.y < 0) b.y = engine->GetHeight() - 1;
		if (b.y > engine->GetHeight() - 1) b.y = 0;
	}
	for (int i = 0; i < snake.size() - 1; i++)
	{
		for (int j = i + 1; j < snake.size(); j++)
		{
			if (snake[i].x == snake[j].x && snake[i].y == snake[j].y)
			{
				isDead = true;
				Create();
			}
		}
	}
	if (snake[0].x == food.x && snake[0].y == food.y && isDead == false)
	{
		Body newBody;
		newBody.x = snake[0].x;
		newBody.y = snake[0].y;
		snake.push_back(newBody);
		SpawnFood();
		score++;
	}
	inputGiven = false;
}

void Snake::Render()
{
	for (Body& b : snake)
	{
		engine->DrawTile(b.x, b.y, 255, 255, 255);
	}
	engine->DrawTile(food.x, food.y, 255, 255, 0);
	std::string scoreText = "score: ";
	scoreText.append(std::to_string(score));
	engine->DrawText(scoreText.c_str(), 0, 0, 75, 25);
}

void Snake::OnKeyDown(SDL_KeyboardEvent& e)
{
	SDL_Keycode code = e.keysym.sym;
	if (code == SDLK_SPACE && engine->updateTime != 0)
	{
		engine->updateTime = 0;
	}
	else if (code == SDLK_SPACE && engine->updateTime == 0)
	{
		engine->updateTime = 100;
	}
	if (engine->updateTime == 0) return;
	if (inputGiven) return;
	inputGiven = true;
	if (code == SDLK_UP && dir != DIRECTION::DOWN) dir = DIRECTION::UP;
	if (code == SDLK_DOWN && dir != DIRECTION::UP) dir = DIRECTION::DOWN;
	if (code == SDLK_LEFT && dir != DIRECTION::RIGHT) dir = DIRECTION::LEFT;
	if (code == SDLK_RIGHT && dir != DIRECTION::LEFT) dir = DIRECTION::RIGHT;
}

void Snake::OnKeyUp(SDL_KeyboardEvent& e)
{
}
