#include "Player.h"
#include "AuxAccountMount.h"

void CheckAndRemove(Player* player)
{
    for (Account_mount_data_Table::const_iterator itr = sFiltroMonturas->GetAll().begin(); itr != sFiltroMonturas->GetAll().end(); ++itr)
    {
        if (player->HasSpell(itr->first))
            player->RemoveSpell(itr->second.m_visualSpell);
    }
}


class MountsAdjust : public PlayerScript
{
public:
    MountsAdjust() : PlayerScript("SpellsMover") {}

    void OnLogin(Player* player, bool /*bFirstLogin*/) override
    {
        CheckAndRemove(player);
    }

    void OnSpellLearn(Player* player, uint32 idSpell) override
    {
        auto item = sFiltroMonturas->GetRow(idSpell);
        //En caso de que tenga un spell visual
        if (item.m_visualSpell != 0)
        {
            player->RemoveSpell(item.m_visualSpell);
        }
    }

};



void AddSC_MountsAdjust()
{
    new MountsAdjust();
}
