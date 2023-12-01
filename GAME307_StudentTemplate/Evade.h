#ifndef EVADE_H
#define EVADE_H


#include "SteeringBehaviour.h"
class Evade :
    public SteeringBehaviour
{
protected:
    Body* target;
    

public:
    Evade(Body* npc_, Body* target_);
    virtual ~Evade();
    SteeringOutput* GetSteering();
};

#endif // !EVADE_H
