#pragma once

#include "Decision.h"
class PlayerHasWeapon :
	public Decision
{
private:
	

public:
	PlayerHasWeapon() : Decision()
	{
		
	}
	PlayerHasWeapon(DecisionTreeNode* trueBranch_, DecisionTreeNode* falseBranch_, Character* owner_) : Decision(trueBranch_, falseBranch_, owner_)
	{
		owner = owner_;
	}
	~PlayerHasWeapon() {}

	bool testValue();
};