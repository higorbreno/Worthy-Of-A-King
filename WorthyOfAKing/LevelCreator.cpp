#include "LevelCreator.h"
#include "LevelMouse.h"
#include <fstream>
using std::ifstream;
using std::ofstream;

std::list<LevelTile*> LevelCreator::tiles;
Scene* LevelCreator::scene = nullptr;
Audio* LevelCreator::audio = nullptr;

const string ARQUIVO = "3.lvl";

void LevelCreator::Init()
{
	scene = new Scene();
	LevelMouse* mouse = new LevelMouse();
	scene->Add(mouse, MOVING);

	ifstream fin;
	fin.open(ARQUIVO);

	if (fin.is_open()) {
		int tilesCount;
		fin >> tilesCount;

		for (int i = 0; i < tilesCount; ++i) {
			int type, id;
			float x, y;
			fin >> type >> id >> x >> y;
			LevelTile* tile = new LevelTile(x, y, TileType(type), id);
			tile->MoveTo(x, y);
			scene->Add(tile, STATIC);
			tiles.push_back(tile);
		}
		fin.close();
	}
}

void LevelCreator::Update()
{
	if (window->KeyDown('A'))
		camera->Translate(-300 * gameTime, 0);
	if (window->KeyDown('D'))
		camera->Translate(300 * gameTime, 0);
	if (window->KeyDown('W'))
		camera->Translate(0, -300 * gameTime);
	if (window->KeyDown('S'))
		camera->Translate(0, 300 * gameTime);

	if (window->KeyPress('T'))
		createLevelFile();

	scene->Update();
	scene->CollisionDetection();
}

void LevelCreator::Draw()
{
	scene->Draw();
	scene->DrawBBox();
}

void LevelCreator::Finalize()
{
	delete scene;
	if (!LevelTile::blocks.empty()) {
		for (auto block : LevelTile::blocks) {
			if(block)
				delete block;
		}
		LevelTile::blocks.clear();
	}
	if (!LevelTile::obstacles.empty()) {
		for (auto obstacle : LevelTile::obstacles) {
			if (obstacle)
				delete obstacle;
		}
		LevelTile::obstacles.clear();
	}
	if (!LevelTile::enemies.empty()) {
		for (auto enemy : LevelTile::enemies) {
			if (enemy)
				delete enemy;
		}
		LevelTile::enemies.clear();
	}
	if (!LevelTile::collectables.empty()) {
		for (auto collectable : LevelTile::collectables) {
			if (collectable)
				delete collectable;
		}
		LevelTile::collectables.clear();
	}
}

void LevelCreator::createLevelFile()
{
	ofstream fout;

	fout.open(ARQUIVO);

	fout << tiles.size() << "\n";
	
	for (LevelTile* tile : tiles) {
		fout << tile->tileType << " " << tile->Id() << " " << tile->X() << " " << tile->Y() << "\n";
	}
	
	fout.close();
}

