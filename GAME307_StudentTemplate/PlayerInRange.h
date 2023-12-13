#ifndef PLAYERINRANGE_H
#define PLAYERINRANGE_H

#include "Decision.h"
class PlayerInRange :
    public Decision
{
private:
	float distance;
public:
	PlayerInRange(float distance_) : Decision() 
	{
		distance = distance_;
	}
	PlayerInRange(DecisionTreeNode* trueBranch_, DecisionTreeNode* falseBranch_, float distance_, Character* owner_) : Decision(trueBranch_, falseBranch_, owner_) 
	{
		distance = distance_;
	}
	~PlayerInRange() {}

	bool testValue();
};

#endif // !PLAYERINRANGE_H