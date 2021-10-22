#include "Home.h"
#include "Resources.h"
#include "Engine.h"
#include "Level.h"
#include "LevelCreator.h"
#include "GameOver.h"
#include "Result.h"

void Home::Init()
{
    audio = new Audio();
    audio->Add(0, "Resources/MenuMusic.wav");

	background = new Sprite("Resources/Background.png");
    ts = new TileSet("Resources/Title.png", 2, 1);
    anim = new Animation(ts, 0.4f, true);

    font33 = new Font("Resources/Joystix33.png");
    font33->Spacing("Resources/Joystix33.dat");

    font22 = new Font("Resources/Joystix22.png");
    font22->Spacing("Resources/Joystix22.dat");

    audio->Play(0, true);
}

void Home::Update()
{
    anim->NextFrame();
    if (window->KeyPress(VK_SPACE)) {
        Level::level = 0;
        Engine::Next<Level>();
    }
}

void Home::Draw()
{
    background->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    anim->Draw(window->CenterX(), window->CenterY() - 70);

    font22->Draw(window->CenterX() - 275, window->CenterY() + 100, "Press Space to enter a");
    font22->Draw(window->CenterX() - 300, window->CenterY() + 130, "Journey Worthy of a King!");
}

void Home::Finalize()
{
    delete background;
    delete ts;
    delete anim;
    delete font33;
    delete font22;
    delete audio;
}

// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine* engine = new Engine();

    // configura motor
    engine->window->Mode(WINDOWED);
    engine->window->Size(640, 320);
    engine->window->Color(50, 100, 200);
    engine->window->Title("Worthy of a King");
    engine->window->Icon(IDI_ICON);
    //engine->window->Cursor(IDC_CURSOR);
    engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new Home());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------