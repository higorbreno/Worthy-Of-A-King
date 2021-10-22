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
    void Init();                        // inicializa��o
    void Update();                      // atualiza��o
    void Draw();                        // desenho
    void Finalize();                    // finaliza��o
};

#endif // !GAMEOVER_H
