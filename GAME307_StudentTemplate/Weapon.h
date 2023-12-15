#pragma once
#include "Body.h"
#include "Scene.h"
#include <vector>

class Weapon
{
private:
    Vec3 pos;
    SDL_Surface* image = nullptr;
    SDL_Texture* texture = nullptr;
    SDL_Window* window = nullptr;
    SDL_Rect* square = nullptr;
    SDL_Renderer* renderer = nullptr;
    Scene* scene = nullptr;
    std::vector<Vec3> possiblePositions;

    //bool enabled = false;

    float randomFloat() { return (float)(rand()) / (float)(RAND_MAX); }
public:
    Weapon(std::vector<Vec3> possibleLocations_, Scene* scene_);
    ~Weapon();

    void Render(float scale_);
    void CheckCollision(SDL_Rect* collisionBox_);

    //void setPossiblePositions(std::vector<Vec3> positions_) { possiblePositions = positions_; }
};

