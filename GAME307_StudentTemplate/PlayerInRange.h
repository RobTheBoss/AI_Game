#ifndef PLAYER_IN_RANGE_H
#define PLAYER_IN_RANGE_H

#include "Decision.h"
class PlayerInRange :
    public Decision
{
private:
	//float distance;
public:
	PlayerInRange(float distance_) : Decision() 
	{
		
	}
	PlayerInRange(DecisionTreeNode* trueBranch_, DecisionTreeNode* falseBranch_, Character* owner_) : Decision(trueBranch_, falseBranch_, owner_) 
	{
		owner = owner_;
	}
	~PlayerInRange() {}

	bool testValue();
};

#endif  PLAYER_IN_RANGE_H