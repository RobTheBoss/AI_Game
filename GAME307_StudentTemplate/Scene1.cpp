#include "Scene1.h"
#include "KinematicSeek.h"
#include "SDL_rect.h"
#include "Path.h"
#include "SteeringBehaviour.h"
#include "FollowAPath.h"

Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_){
	/* initialize random seed: */
	srand(time(NULL));

	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;

	// create a NPC
	hunter = nullptr;
	ghost = nullptr;
}

Scene1::~Scene1(){
	
}

bool Scene1::OnCreate() {
	//tileWidth = 3.0f;
	//tileHeight = 3.0f;

	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	
	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	SDL_Surface* image;
	SDL_Texture* texture;

	image = IMG_Load("Sprites/BlueSquare.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);

	// Set up characters, choose good values for the constructor
	// or use the defaults, like this
	hunter = std::make_unique<Character>();
	if (!hunter->OnCreate(this) || !hunter->setTextureWith("Sprites/FaceThing.png") )
	{
		return false;
	}
	hunter->SetPos(Vec3(4.5f,1.5f,0));

	ghost = std::make_unique<Character>();
	if (!ghost->OnCreate(this) || !ghost->setTextureWith("Sprites/Clyde.png"))
	{
		return false;
	}
	ghost->SetVisibility(false);

	darkness = std::make_unique<StaticImage>(Vec3(12.0f, 7.5f, 0));
	if (!darkness->OnCreate(this) || !darkness->setTextureWith("Sprites/Darkness.png"))
	{
		return false;
	}

	if (!hunter->readDecisionTreeFromFile("hunter"))
		return false;

	if (!ghost->readDecisionTreeFromFile("ghost"))
		return false;

	std::vector<Vec3> possiblePositions;
	possiblePositions.push_back(Vec3(32.0f, 58.0f, 0.0f));
	possiblePositions.push_back(Vec3(45.0f, 35.0f, 0.0f));
	possiblePositions.push_back(Vec3(25.0f, 30.0f, 0.0f));
	possiblePositions.push_back(Vec3(48.0f, 5.0f, 0.0f));
	possiblePositions.push_back(Vec3(7.0f, 5.0f, 0.0f));
	possiblePositions.push_back(Vec3(46.0f, 52.0f, 0.0f));

	weapon = std::make_unique<Weapon>(possiblePositions, this);

	xAxis = game->getSceneWidth();
	yAxis = game->getSceneHeight();

	grid = std::make_unique<Grid>(3.0f, 3.0f, this);

	grid->createTiles(22,19);
	grid->createGraph();
	grid->calculateConnectionWeights();
	
	paths.push_back(Pathway(20, 388));
	paths.push_back(Pathway(388, 244));
	paths.push_back(Pathway(244, 54));
	paths.push_back(Pathway(54, 20));

	hunter->SetPath(paths[0].start, paths[0].end);

	return true;
}

void Scene1::OnDestroy() {}

void Scene1::Update(const float deltaTime) {
	if (gameFinished)
		return;

	//SDL_Rect rect = game->getPlayer()->getSDL_Rect();

	float left, right, top, bottom;
	left = (game->getPlayer()->getPos().x) - (xAxis / 2.0f);
	right = (game->getPlayer()->getPos().x) + (xAxis / 2.0f);
	bottom = (game->getPlayer()->getPos().y) - (yAxis / 2.0f);
	top = (game->getPlayer()->getPos().y) + (yAxis / 2.0f);

	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(left, right, bottom, top, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	hunter->Update(deltaTime);
	if (hunter->getPathComplete())
	{
		currentPath++;
		if (currentPath >= paths.size())
			currentPath = 0;

		hunter->SetPath(paths[currentPath].start, paths[currentPath].end);
	}

	ghost->Update(deltaTime);

	grid->playerTileCollision();
	//grid->enemyTileCollision(hunter.get());

	// Update player
	game->getPlayer()->Update(deltaTime);

	if (game->getPlayer()->checkCollisionGhost(ghost.get()) || VMath::distance(game->getPlayer()->getPos(), ghost.get()->getPos()) > 10.0f)
		ghostSpawned = false;

	if (game->getPlayer()->checkCollisionHunter(hunter.get()))
		hunter.get()->HurtEnemy();

	darkness->setPos(game->getPlayer()->getPos());

	weapon->CheckCollision(game->getPlayer()->getSDL_Rect());
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//Render tiles
	grid->Render();

	// render the player
	game->RenderPlayer(0.5f);

	//render npc
	ghost->render(0.2f);

	//render npc
	hunter->render(0.2f);

	//render darkness
	darkness->render(1.0f);

	weapon->Render(2.0f);

	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to npc's as needed
	
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
}
