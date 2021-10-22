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

	void Init();                        // inicialização
	void Update();                      // atualização
	void Draw();                        // desenho
	void Finalize();                    // finalização
};

#endif