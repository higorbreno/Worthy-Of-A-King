/**********************************************************************************
// Vector2D (Arquivo de Cabeçalho)
//
// Criação:     11 Nov 2011
// Atualização: 13 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Exemplo de utilização da classe Vector
//
**********************************************************************************/

#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_

// ---------------------------------------------------------------------------------

#include "Game.h"
#include "Scene.h"
#include "Audio.h"
#include "Sprite.h"
#include "Resources.h"

// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------

class Level : public Game
{
private:
    float time;

public:
    static bool isGameOver;
    static bool isFinished;
    static int score;
    static int level;
    static Scene * scene;               // gerenciador de cena 
    static Audio * audio;               // sistema de áudio

    void Init();                        // inicialização
    void Update();                      // atualização
    void Draw();                        // desenho
    void Finalize();                    // finalização
};

// ---------------------------------------------------------------------------------

#endif