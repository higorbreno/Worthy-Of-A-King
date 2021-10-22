/**********************************************************************************
// Level (Código Fonte)
//
// Criação:     11 Nov 2011
// Atualização: 13 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Exemplo de utilização da classe Vector
//
**********************************************************************************/

#include "Engine.h"
#include "Level.h"
#include "Player.h"
#include "Block.h"
#include "LevelCreator.h"
#include <fstream>
#include "Obstacle.h"
#include "Enemy.h"
#include "Collectable.h"
#include "Finish.h"
#include "Home.h"
#include "Result.h"
#include "GameOver.h"
using std::ifstream;
using std::ofstream;

// ------------------------------------------------------------------------------

bool Level::isFinished = false;
bool Level::isGameOver = false;
int Level::score = 0;
int Level::level = 0;                      // identificador de nível
Scene * Level::scene = nullptr;            // gerenciador de cena 
Audio * Level::audio = nullptr;            // sistema de áudio

// ------------------------------------------------------------------------------

void Level::Init()
{
    // inicializa as variáveis de pontuação
    score = 0;
    isFinished = false;
    isGameOver = false;

    // cria sistema de áudio
    audio = new Audio();
    audio->Add(0, "Resources/LevelMusic.wav");
    audio->Add(1, "Resources/Collect.wav", 3);
    audio->Add(2, "Resources/EnemyKill.wav", 3);

    audio->Volume(1, 0.1f);

    scene = new Scene();

    ifstream fin;
    fin.open(std::to_string(level) + ".lvl");

    if (fin.is_open()) {
        int tilesCount;
        fin >> tilesCount;

        for (int i = 0; i < tilesCount; ++i) {
            int type, id;
            float x, y;
            fin >> type >> id >> x >> y;
            
            if (type == TileType::PLAYER) {
                Player* player = new Player();
                player->MoveTo(x, y);
                scene->Add(player, MOVING);
            }
            else if (type == TileType::BLOCK) {
                Block* block = new Block(id, x, y);
                scene->Add(block, STATIC);
            }
            else if (type == TileType::OBSTACLE) {
                Obstacle* obstacle = new Obstacle(id, x, y);
                scene->Add(obstacle, STATIC);
            }
            else if (type == TileType::ENEMY) {
                Enemy* enemy = new Enemy(id, x, y);
                scene->Add(enemy, MOVING);
            }
            else if (type == TileType::COLLECTABLE) {
                Collectable* collectable = new Collectable(id, x, y);
                scene->Add(collectable, STATIC);
            }
            else if (type == TileType::FINISH) {
                Finish* finish = new Finish(x, y);
                scene->Add(finish, STATIC);
            }
        }
         fin.close();
    }

    audio->Play(0);
}

// ------------------------------------------------------------------------------

void Level::Update()
{
    // atualização da cena
    scene->Update();
    scene->CollisionDetection();

    if (window->KeyDown(VK_ESCAPE))
        Engine::Next<Home>();

    if (isFinished || window->KeyPress('N')) {
        Result::score = score;
        Result::level = level;
        Engine::Next<Result>();
    }
    else if (isGameOver) {
        GameOver::level = level;
        Engine::Next<GameOver>();
    }
} 

// ------------------------------------------------------------------------------

void Level::Draw()
{
    // desenha pano de fundo
    
    
    // desenho da cena
    scene->Draw();
    //scene->DrawBBox();
} 

// ------------------------------------------------------------------------------

void Level::Finalize()
{
    delete scene;
    scene = nullptr;
    delete audio;
    audio = nullptr;
    if (Player::tileSet)
        delete Player::tileSet;
    for (auto image : Block::images) {
        delete image;
    }
    Block::images.clear();
}
