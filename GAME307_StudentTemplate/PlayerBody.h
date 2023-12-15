//
//  PlayerBody.h
//  DemoAI
//
//  Created by Gail Harris on 2021-Dec-23.
//

#ifndef PLAYERBODY_H
#define PLAYERBODY_H

#include <stdio.h>
#include "Body.h"
#include "GameManager.h"

class PlayerBody : public Body
{
protected:
    class GameManager* game;
    SDL_Rect square;

public:
    bool hasWeapon = false;

    PlayerBody() : Body{}
    {
        game = nullptr;
        square = SDL_Rect();
    }

    PlayerBody(
        Vec3 pos_, Vec3 vel_, Vec3 accel_,
        float mass_,
        float radius_,
        float orientation_,
        float rotation_,
        float angular_,
        float maxSpeed_,
        float maxAcceleration_,
        float maxRotation_,
        float maxAngular_,
        GameManager *game_
    ) : Body{
          pos_
        , vel_
        , accel_
        , mass_
        , radius_
        , orientation_
        , rotation_
        , angular_
        , maxSpeed_
        , maxAcceleration_
        , maxRotation_
        , maxAngular_
    }
        , game{ game_ }
    {
        square = SDL_Rect();
    }
    
    // use the base class versions of getters

    bool OnCreate();
    void Render( float scale = 1.0f );
    void HandleEvents( const SDL_Event& event );
    void Update( float deltaTime );
    void resetToOrigin();
    void setTexture( SDL_Texture* texture_ ) { texture = texture_; }
    SDL_Rect* getSDL_Rect() { return &square; }  
    void setVelX(float x) { vel.x = x; }
    void setVelY(float y) { vel.y = y; }

    bool checkCollisionGhost(class Character* ghost_);
    bool checkCollisionHunter(class Character* enemy_);
};

#endif /* PLAYERBODY_H */
