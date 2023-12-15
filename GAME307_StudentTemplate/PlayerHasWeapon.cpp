#include "PlayerHasWeapon.h"
#include "Character.h"

bool PlayerHasWeapon::testValue()
{
	if (owner->getScene()->game->getPlayer()->hasWeapon)
		return true;
	else
		return false;
}
