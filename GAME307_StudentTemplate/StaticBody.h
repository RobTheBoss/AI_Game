#ifndef STATIC_BODY_H
#define STATIC_BODY_H
#include "Body.h"
#include "KinematicSteeringOutput.h"

class StaticBody :
    public Body
{
private:

public:
    StaticBody() : Body()
    {
    }

    StaticBody(Vec3 pos_, float orientation_, float maxSpeed_, float maxRotation_) :
        Body(pos_, Vec3(), Vec3(), 1.0, 1.0, orientation_, 0.0, 0.0, maxSpeed_, 0.0f, maxRotation_, 0.0f)
    {
    }

    void Update(float deltaTime_, KinematicSteeringOutput* steering_);

    void NewOrientation();
};

#endif