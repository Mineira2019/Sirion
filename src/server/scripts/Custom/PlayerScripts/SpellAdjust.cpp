#include "Player.h"
#include "AuxAccountSpell.h"

void CheckAndRemove(Player* player)
{
    for (AccountSpellDataTable::const_iterator itr = sFiltroSpells->GetAll().begin(); itr != sFiltroSpells->GetAll().end(); ++itr)
    {
        if (player->HasSpell(itr->first))
            player->RemoveSpell(itr->second.m_visualSpell);
    }
}


class SpellAdjust : public PlayerScript
{
public:
    SpellAdjust() : PlayerScript("SpellAdjust") {}

    void OnLogin(Player* player, bool /*bFirstLogin*/) override
    {
        CheckAndRemove(player);
    }

    void OnSpellLearn(Player* player, uint32 idSpell) override
    {
        auto item = sFiltroSpells->GetRow(idSpell);
        //En caso de que tenga un spell visual
        if (item.m_visualSpell != 0)
        {
            player->RemoveSpell(item.m_visualSpell);
        }
    }

};



void AddSC_SpellAdjust()
{
    new SpellAdjust();
}
