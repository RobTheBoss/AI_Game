#ifndef SCENE1_H
#define SCENE1_H

#include <MMath.h>
#include <VMath.h>
#include "Scene.h"
#include "Character.h"
#include "StaticBody.h"
#include "StaticImage.h"
#include "Node.h"
#include "Graph.h"
#include "Tile.h"
#include "Grid.h"
#include "Weapon.h"


using namespace MATH;
class Scene1 : public Scene {
private:
	SDL_Window *window;
	float xAxis;
	float yAxis;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
    Matrix4 inverseProjection;

	std::unique_ptr<Character> hunter;
	std::unique_ptr<Character> ghost;
	std::unique_ptr<Weapon> weapon;

	std::unique_ptr<StaticImage> darkness;

	std::unique_ptr<Grid> grid;

	std::vector<struct Pathway> paths;
	int currentPath = 0;


	//Graph* graph;
	//std::vector<Node*> sceneNodes;

	//float tileWidth;
	//float tileHeight;

	//std::vector<std::vector<Tile*>> tiles;
	//void createTiles(int rows, int cols);
	//void calculateConnectionWeights();

public:
	bool ghostSpawned = false;

	Scene1(SDL_Window* sdlWindow, GameManager* game_);
	~Scene1();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
    void HandleEvents(const SDL_Event &event);
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	SDL_Window* getWindow() { return window; }
    Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }
	Grid* getGrid() { return grid.get(); }

	void SpawnEnemy(Vec3 pos_)
	{
		ghost->SetVisibility(true);
		ghost->SetPos(pos_);
	}

	void setGhostVisible(bool visible) { ghost.get()->SetVisibility(visible); }
};

struct Pathway {
public:
	Pathway(int start_, int end_) { start = start_, end = end_; }

	int start;
	int end;
};
#endif
