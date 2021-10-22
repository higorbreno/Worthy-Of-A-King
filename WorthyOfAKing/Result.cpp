#include "Result.h"
#include "Level.h"
#include "Engine.h"
#include "Home.h"

int Result::score = 0;
int Result::level = 0;

const int MAX_LEVELS = 4;

void Result::Init()
{
    background = new Sprite("Resources/Background.png");
    font33 = new Font("Resources/Joystix33.png");
    font33->Spacing("Resources/Joystix33.dat");

    font22 = new Font("Resources/Joystix22.png");
    font22->Spacing("Resources/Joystix22.dat");
}

void Result::Update()
{
    if (window->KeyPress(VK_SPACE)) {
        if (++level < MAX_LEVELS) {
            Level::level = level;
            Engine::Next<Level>();
        }
        else {
            Engine::Next<Home>();
        }
    }
    else if (window->KeyPress('R')) {
        Level::level = level;
        Engine::Next<Level>();
    }
}

void Result::Draw()
{
    background->Draw(window->CenterX(), window->CenterY(), Layer::BACK);

    font22->Draw(window->CenterX() - 120, window->CenterY() - 100, "Final Score:");
    font22->Draw(window->CenterX() - 10, window->CenterY() - 70, std::to_string(score));

    font22->Draw(window->CenterX() - 110, window->CenterY() + 100, " R = Reset");
    if(level < MAX_LEVELS - 1)
        font22->Draw(window->CenterX() - 120, window->CenterY() + 130, "Space = Next");
    else 
        font22->Draw(window->CenterX() - 120, window->CenterY() + 130, "Space = Home");
}

void Result::Finalize()
{
    delete background;
    delete font22;
    delete font33;
}
