#include "Scene1.h"
#include "KinematicSeek.h"
#include "SDL_rect.h"
#include "Path.h"
#include "SteeringBehaviour.h"
#include "FollowAPath.h"

Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;

	// create a NPC
	hunter = nullptr;
	//myNPC = nullptr;
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

	// Set player image to PacMan
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
	hunter->SetPos(Vec3(0,0,0));

	darkness = std::make_unique<StaticImage>(Vec3(12.0f, 7.5f, 0));
	if (!darkness->OnCreate(this) || !darkness->setTextureWith("Sprites/Darkness.png"))
	{
		return false;
	}

	if (!hunter->readDecisionTreeFromFile("hunter"))
		return false;

	Vec3 position = Vec3(5.0f, 1.0f, 0.0f);
	float orientation = 0.0f;
	float maxSpeed = 1.0f;
	float maxAcceleration = 1.0f;
	float maxRotation = 1.0f;

	xAxis = game->getSceneWidth();
	yAxis = game->getSceneHeight();

	grid = std::make_unique<Grid>(3.0f, 3.0f, this);

	grid->createTiles(22,19);
	grid->createGraph();
	grid->calculateConnectionWeights();

	//grid->findPath(20, 58); //temporary (in game findPath will be used in the FollowAPath Class)
	
	std::vector<int> path = grid->findPath(20, 49);
	hunter->SetPath(20, 49);

	return true;
}

void Scene1::OnDestroy() {}

void Scene1::Update(const float deltaTime) {
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

	grid->playerTileCollision();
	//grid->enemyTileCollision(hunter.get());

	// Update player
	game->getPlayer()->Update(deltaTime);

	darkness->setPos(game->getPlayer()->getPos());

}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//Render tiles
	grid->Render();

	// render the player
	game->RenderPlayer(0.5f);

	//render npc
	hunter->render(0.2f);

	//render darkness
	darkness->render(1.0f);

	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to npc's as needed
	
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
}
