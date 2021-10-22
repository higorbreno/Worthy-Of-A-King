#include "GameOver.h"
#include "Engine.h"
#include "Home.h"
#include "Level.h"

int GameOver::level = 0;

void GameOver::Init()
{
	background = new Sprite("Resources/Background.png");
	font33 = new Font("Resources/Joystix33.png");
	font33->Spacing("Resources/Joystix33.dat");

	font22 = new Font("Resources/Joystix22.png");
	font22->Spacing("Resources/Joystix22.dat");
}

void GameOver::Update()
{
	if (window->KeyPress(VK_SPACE)) {
		Level::level = level;
		Engine::Next<Level>();
	}
	else if (window->KeyPress(VK_ESCAPE)) {
		Engine::Next<Home>();
	}
}

void GameOver::Draw()
{
	background->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
	font33->Draw(window->CenterX() - 140, window->CenterY() - 100, "Game Over");
	
	font22->Draw(window->CenterX() - 270, window->CenterY() + 100, "To restart your journey");
	font22->Draw(window->CenterX() - 140, window->CenterY() + 130, "Press Space");
}

void GameOver::Finalize()
{
	delete background;
	delete font22;
	delete font33;
}
