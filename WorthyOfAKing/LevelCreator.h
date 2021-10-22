#include "Game.h"
#include "Scene.h"
#include "Audio.h"
#include "LevelTile.h"

#ifndef LEVELCREATOR_H
#define LEVELCREATOR_H

class LevelCreator : public Game {
private:

public:
    static std::list<LevelTile*> tiles;
    static Scene* scene;
    static Audio* audio;

    void Init();                        // inicializa��o
    void Update();                      // atualiza��o
    void Draw();                        // desenho
    void Finalize();                    // finaliza��o
    void createLevelFile();
};

#endif // !LEVELCREATOR_H
