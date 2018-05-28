#include "AuxAccountSpell.h"


void FiltroSpells::Load_Account_Spell_Data()
{
	m_SpellsAccount.clear();
	QueryResult resultado = WorldDatabase.Query("Select idSpell,raceMask,classMask,learn,idSpellVisual,spellType from account_spell_data");
	if (resultado)
	{
		int count = 0;
		do
		{
			count++;
			Field* fields = resultado->Fetch();
            AccountSpellDataRow row
            {
                fields[1].GetUInt32(),
                fields[2].GetUInt32(),
                fields[3].GetBool(),
                fields[4].GetUInt32(),
                (AccountSpellType)fields[5].GetInt32()
			};
			m_SpellsAccount.insert(AccountSpellDataTable::value_type(fields[0].GetUInt32(), row));
		} while (resultado->NextRow());

		TC_LOG_INFO("server.loading", "Loaded %u AccountSpellData Rows.", count);
	}
	else
		TC_LOG_ERROR("misc", "WARNING >> Loaded 0 AccountSpellData Rows.");
}

AccountSpellDataRow FiltroSpells::GetRow(uint32 SpellID)
{
	AccountSpellDataRow ret;
	AccountSpellDataTable::const_iterator itr = m_SpellsAccount.find(SpellID);
	if (itr != m_SpellsAccount.end())
	{
		ret.m_maskRace = itr->second.m_maskRace;
		ret.m_maskClass = itr->second.m_maskClass;
		ret.m_learn = itr->second.m_learn;
		ret.m_visualSpell = itr->second.m_visualSpell;
        ret.m_SpellType = itr->second.m_SpellType;
	}
	else
	{
		ret.m_learn = 0;
		ret.m_maskClass = 0;
		ret.m_maskRace = 0;	
		ret.m_visualSpell = 0;
        ret.m_SpellType = AccountSpellTypeNONE;
	}
	return ret;	
	
}

FiltroSpells* FiltroSpells::instance()
{
	static FiltroSpells instance;
	return &instance;
}
