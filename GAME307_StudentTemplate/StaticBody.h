#ifndef STATIC_BODY_H
#define STATIC_BODY_H
#include "Body.h"
#include "KinematicSteeringOutput.h"
#include "Scene.h"

using namespace std;

class StaticBody :
    public Body
{
private:
    Scene* scene;

public:
    StaticBody() : Body()
    {
        scene = NULL;
    }

    StaticBody(Vec3 pos_, float orientation_, float maxSpeed_, float maxRotation_) :
        Body(pos_, Vec3(), Vec3(), 1.0, 1.0, orientation_, 0.0, 0.0, maxSpeed_, 0.0f, maxRotation_, 0.0f)
    {
        scene = NULL;
    }

    bool OnCreate(Scene* scene_);

    void Update(float deltaTime_);

    void Render(float scale = 1.0f);

    bool setTextureWith(string file);

    void NewOrientation();
};

#endif