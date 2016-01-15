/* Copyright (C) 2006 - 2013 ScriptDev2 <http://www.scriptdev2.com/>
 * Copyright (C) 2011 - 2013 MangosR2 <http://github.com/mangosR2/>
 * Copyright (C) 2015 - 2016 Mangos devs-web <http://github.com/devs-web/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

/* ScriptData
SDName: npc_alltrainer
SD%Complete: 100%
SDComment: by Thermaltake
SDCategory: custom
EndScriptData */

#include "precompiled.h"
#include "ObjectMgr.h"
#include "Log.h"
#include "SpellMgr.h"
#include "Language.h"
#include "Database/DatabaseEnv.h"


void BufsAdd (Player* player)
{
    int SpellsBufs[17] = {
        48102,
        20911,
        23737,
        23766,
        23736,
        23735,
        23738,
        25898,
        43223,
        36880,
        467,
        69994,
        48469,

        69381,
        48162,
        48170,
        48074};
    
    for (int i = 0; i <= 16; i++)
        player->_AddAura(SpellsBufs[i], 3600000);
}

void Changefaction (Player* player)
{
        ChatHandler(player).PSendSysMessage(LANG_CUSTOMIZE_PLAYER, player->GetName());
        player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
        player->SetAtLoginFlag(AT_LOGIN_CHECK_TITLES);
        CharacterDatabase.PExecute("UPDATE characters SET at_login = at_login | '320' WHERE guid = '%u'", player->GetGUIDLow());
}

void Changerace (Player* player)
{
        ChatHandler(player).PSendSysMessage(LANG_CUSTOMIZE_PLAYER, player->GetName());
        player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
        CharacterDatabase.PExecute("UPDATE characters SET at_login = at_login | '128' WHERE guid = '%u'", player->GetGUIDLow());
}

void Changecust (Player* player)
{
        ChatHandler(player).PSendSysMessage(LANG_CUSTOMIZE_PLAYER, player->GetName());
        player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
        CharacterDatabase.PExecute("UPDATE characters SET at_login = at_login | '8' WHERE guid = '%u'", player->GetGUIDLow());
}

bool GossipHello_npc_vip_script(Player* player, Creature* _Creature)
{
    player->ADD_GOSSIP_ITEM(5, "Бафы" , GOSSIP_SENDER_MAIN, 1209);
    player->ADD_GOSSIP_ITEM(5, "Смена фракции" , GOSSIP_SENDER_MAIN, 1210);
    player->ADD_GOSSIP_ITEM(5, "Смена расы" , GOSSIP_SENDER_MAIN, 1211);
    player->ADD_GOSSIP_ITEM(5, "Смена вида" , GOSSIP_SENDER_MAIN, 1212);

    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,_Creature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_vip_script(Player* player, Creature* _Creature, uint32 sender, uint32 action)
{
    if (player->GetSession()->GetSecurity() < SEC_VIP)
    {
        player->CLOSE_GOSSIP_MENU();
        _Creature->MonsterWhisper("Ты не VIP игрок!", player);
        return false;
    }

    switch (action)
    {
        case 1209: BufsAdd (player); break;
        case 1210: Changefaction (player); break;
        case 1211: Changerace (player); break;
        case 1212: Changecust (player); break;

        default: "";
    }

    player->CLOSE_GOSSIP_MENU();
    return true;
}

void AddSC_npc_vip_script()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_vip";
    pNewScript->pGossipHello = &GossipHello_npc_vip_script;
    pNewScript->pGossipSelect = &GossipSelect_npc_vip_script;
    pNewScript->RegisterSelf();
}