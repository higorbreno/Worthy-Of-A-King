#include "Game.h"
#include "Sprite.h"
#include "Font.h"

#ifndef GAMEOVER_H
#define GAMEOVER_H

class GameOver : public Game {
private:
    Sprite* background;
    Font* font33;
    Font* font22;

public:
    static int level;
    void Init();                        // inicialização
    void Update();                      // atualização
    void Draw();                        // desenho
    void Finalize();                    // finalização
};

#endif // !GAMEOVER_H
