#include "Game.h"
#include "Audio.h"
#include "Sprite.h"
#include "Font.h"
#include "Animation.h"

#ifndef HOME_H
#define HOME_H

class Home : public Game
{
private:
    Audio* audio;               // sistema de �udio
    Sprite* background;
    TileSet* ts;
    Animation* anim;
    Font* font33;
    Font* font22;

public:

    void Init();                        // inicializa��o
    void Update();                      // atualiza��o
    void Draw();                        // desenho
    void Finalize();                    // finaliza��o
};

#endif // !HOME_H
