#include "PlayerInRange.h"
#include "Character.h"

bool PlayerInRange::testValue()
{
    //test if player is in range
    //get player pos and this characters pos
	if (VMath::distance(owner->getPos(), owner->getPlayerPos()) < 5.0f)
	{
		return true;
	}
	return false;}
