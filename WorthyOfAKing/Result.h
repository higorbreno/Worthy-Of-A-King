#include "Game.h"
#include "Sprite.h"
#include "Font.h"

#ifndef RESULT_H
#define RESULT_H

class Result : public Game {
private:
	Sprite* background;
	Font* font33;
	Font* font22;

public:
	static int score;
	static int level;

	void Init();                        // inicializa��o
	void Update();                      // atualiza��o
	void Draw();                        // desenho
	void Finalize();                    // finaliza��o
};

#endif