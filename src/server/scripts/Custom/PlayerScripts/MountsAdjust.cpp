#include "Player.h"

void CheckAndRemove(Player* player)
{
	//Alatemible corrupto
	if (player->HasSpell(123974))
		player->RemoveSpell(5600004);
}


class MountsAdjust : public PlayerScript
{
public:
	MountsAdjust() : PlayerScript("SpellsMover") {}

	void OnLogin(Player* player, bool /*bFirstLogin*/) override
	{
		CheckAndRemove(player);
	}	

};



void AddSC_MountsAdjust()
{
	new MountsAdjust();
}
