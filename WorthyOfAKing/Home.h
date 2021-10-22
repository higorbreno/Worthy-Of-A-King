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
    Audio* audio;               // sistema de áudio
    Sprite* background;
    TileSet* ts;
    Animation* anim;
    Font* font33;
    Font* font22;

public:

    void Init();                        // inicialização
    void Update();                      // atualização
    void Draw();                        // desenho
    void Finalize();                    // finalização
};

#endif // !HOME_H
