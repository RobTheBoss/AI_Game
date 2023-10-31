#include "Scene1.h"
#include "KinematicSeek.h"
#include "SDL_rect.h"


void Scene1::createTiles(int rows, int cols)
{
	tiles.resize(rows);
	for (int i = 0; i < rows; i++)
	{
		tiles[i].resize(cols);
	}

	Node* n;
	Tile* t;
	int i, j, label;
	i = j = label = 0;

	//for (float y = 0.0f; y < yAxis; y += tileHeight)
	//{
	//	// do stuff for a row, y stays constant
	//	for (float x = 0.0f; x < xAxis; x += tileWidth)
	//	{
	//		//create tiles and nodes
	//		n = new Node(label);
	//		Vec3 tilePos = Vec3(x, y, 0.0f);
	//		t = new Tile(n, tilePos, tileWidth, tileHeight, this);
	//		tiles[i][j] = t;
	//		j++;
	//		label++;
	//	}
	//	j = 0;
	//	i++;
	//}

	for (int i = 0; i < rows; i++)
	{
		// do stuff for a row, y stays constant
		for (int j = 0; j < cols; j++)
		{
			//create tiles and nodes
			n = new Node(label);
			Vec3 tilePos = Vec3(i * tileWidth, j * tileHeight, 0.0f);
			t = new Tile(n, tilePos, tileWidth, tileHeight, this);
			tiles[i][j] = t;
			label++;
		}
		j = 0;
	}
}

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
	tileWidth = 3.0f;
	tileHeight = 3.0f;

	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	//calculate amount of rows and columns we will have
	int rows = ceil((yAxis - 0.5f * tileHeight) / tileHeight);
	int cols = ceil((xAxis - 0.5f * tileWidth) / tileWidth);
	createTiles(50,70);
	
	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	// Set player image to PacMan
	SDL_Surface* image;
	SDL_Texture* texture;

	image = IMG_Load("Sprites/BlueSquare.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);

	/*delete image;
	delete texture;*/

	// Set up characters, choose good values for the constructor
	// or use the defaults, like this
	hunter = std::make_unique<Character>();
	if (!hunter->OnCreate(this) || !hunter->setTextureWith("Sprites/FaceThing.png") )
	{
		return false;
	}

	hunter2 = std::make_unique<StaticBody>(Vec3(0,0,0), 0.0f, 3.0f, 1.0f);
	if (!hunter2->OnCreate(this) || !hunter2->setTextureWith("Sprites/FaceThing.png"))
	{
		return false;
	}

	background = std::make_unique<StaticImage>(Vec3(12.0f,7.5f,0));
	if (!background->OnCreate(this) || !background->setTextureWith("Sprites/Background.png"))
	{
		return false;
	}

	darkness = std::make_unique<StaticImage>(Vec3(12.0f, 7.5f, 0));
	if (!darkness->OnCreate(this) || !darkness->setTextureWith("Sprites/Darkness.png"))
	{
		return false;
	}

	Vec3 position = Vec3(5.0f, 1.0f, 0.0f);
	float orientation = 0.0f;
	float maxSpeed = 1.0f;
	float maxAcceleration = 1.0f;
	float maxRotation = 1.0f;

	xAxis = game->getSceneWidth();
	yAxis = game->getSceneHeight();

	return true;
}

void Scene1::OnDestroy() {}

void Scene1::Update(const float deltaTime) {
	//camera follows player (broken for now)
	SDL_Rect rect = game->getPlayer()->getSDL_Rect();

	float left, right, top, bottom;
	left = (game->getPlayer()->getPos().x) - (xAxis / 2.0f);
	right = (game->getPlayer()->getPos().x) + (xAxis / 2.0f);
	bottom = (game->getPlayer()->getPos().y) + (yAxis / 2.0f);
	top = (game->getPlayer()->getPos().y) - (yAxis / 2.0f);

	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(left, right, top, bottom, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	hunter->Update(deltaTime);

	//KinematicSteeringOutput* steering = new KinematicSteeringOutput();

	//create kinematic seek
	hunter2->Update(deltaTime);

	// Update player
	game->getPlayer()->Update(deltaTime);

	darkness->setPos(game->getPlayer()->getPos());
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//render background
	background->render(1.5f);

	//Render tiles
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i].size(); j++)
		{
			tiles[i][j]->Render();
		}
	}

	// render the player
	game->RenderPlayer(0.7f);

	//render npc
	hunter->render(0.2f);
	hunter2->Render(0.2f);

	//render darkness
	darkness->render();

	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to npc's as needed

	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
}
