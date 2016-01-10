/* Copyright (C) 2006 - 2013 ScriptDev2 <http://www.scriptdev2.com/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: npc_arena_honor
SD%Complete: 100%
SDComment: by tempura, corrected by /dev/rsa
SDCategory: custom
EndScriptData */
#include "precompiled.h"
#include "sc_creature.h"
#include "sc_gossip.h"
#include "Database/DatabaseEnv.h"

#define GOSSIP_ITEM_ARENA_TO_HONOR  -3000770
#define GOSSIP_ITEM_ARENA_TO_HONOR1 -3000771
#define GOSSIP_ITEM_HONOR_TO_ARENA  -3000772
#define GOSSIP_ITEM_HONOR_TO_ARENA1 -3000773

#define UNSUCCESSFUL_HONOR  -1001007
#define UNSUCCESSFUL_ARENA  -1001008

bool GossipHello_npc_arena_honor(Player* pPlayer, Creature *pCreature)
{
    QueryResult *result = LoginDatabase.PQuery("select `EventBonus` from account where `id` = '%u'", pPlayer->GetSession()->GetAccountId());
    if (result)
    {
        Field* fields = result->Fetch();
        uint32 ev = fields[0].GetUInt32();
        
        char buff_text[100];
        sprintf(buff_text, "You have %u EV", ev);
        pCreature->MonsterWhisper(buff_text, pPlayer);
    }

#ifdef SD2_WORLD_WOTLK
    pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_HONOR_TO_ARENA, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_HONOR_TO_ARENA1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ARENA_TO_HONOR, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ARENA_TO_HONOR1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, "1 EV -> 200 AP", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, "1 EV -> 10000 HP", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->SEND_GOSSIP_MENU(3961,pCreature->GetObjectGuid());
#endif
    return true;
}

bool GossipSelect_npc_arena_honor(Player *pPlayer, Creature *pCreature, uint32 sender, uint32 action)
{

#ifdef SD2_WORLD_WOTLK
    if (action == GOSSIP_ACTION_INFO_DEF + 1)
    {
        if (pPlayer->GetHonorPoints() >= 3000)
        {
            pPlayer->ModifyHonorPoints(-3000);
            pPlayer->ModifyArenaPoints(+50);
        }
        else
            DoScriptText(UNSUCCESSFUL_HONOR, pCreature);
    }
    if (action == GOSSIP_ACTION_INFO_DEF + 2)
    {
        if (pPlayer->GetHonorPoints() >= 30000)
        {
            pPlayer->ModifyHonorPoints(-30000);
            pPlayer->ModifyArenaPoints(+500);
        }
        else
            DoScriptText(UNSUCCESSFUL_HONOR, pCreature);
    }
    if (action == GOSSIP_ACTION_INFO_DEF + 3)
    {
        if (pPlayer->GetArenaPoints() >= 100)
        {
            pPlayer->ModifyArenaPoints(-100);
            pPlayer->ModifyHonorPoints(+6000);
        }
        else
            DoScriptText(UNSUCCESSFUL_ARENA, pCreature);
    }
    if (action == GOSSIP_ACTION_INFO_DEF + 4)
    {
        if (pPlayer->GetArenaPoints() >= 1000)
        {
            pPlayer->ModifyArenaPoints(-1000);
            pPlayer->ModifyHonorPoints(+60000);
        }
        else
            DoScriptText(UNSUCCESSFUL_ARENA, pCreature);
    }
    if (action == GOSSIP_ACTION_INFO_DEF + 5)
    {
        QueryResult *result = LoginDatabase.PQuery("select `EventBonus` from account where `id` = '%u'", pPlayer->GetSession()->GetAccountId());
        if (result)
        {
            Field* fields = result->Fetch();
            uint32 ev = fields[0].GetUInt32();
            
            if (ev >= 1)
            {
                LoginDatabase.PExecute("UPDATE  account SET `EventBonus`=(`EventBonus` - 1) WHERE `id` = '%u'", pPlayer->GetSession()->GetAccountId());
                pPlayer->ModifyArenaPoints(+200);
                pCreature->MonsterWhisper("Add +200 Arena Points", pPlayer);
                pPlayer->SaveToDB();
            }
            else
            {
                pCreature->MonsterWhisper("Enough Event bonuses", pPlayer);
            }
        }
    }
    if (action == GOSSIP_ACTION_INFO_DEF + 6)
    {
        QueryResult *result = LoginDatabase.PQuery("select `EventBonus` from account where `id` = '%u'", pPlayer->GetSession()->GetAccountId());
        if (result)
        {
            Field* fields = result->Fetch();
            uint32 ev = fields[0].GetUInt32();
            
            if (ev >= 1)
            {
                LoginDatabase.PExecute("UPDATE  account SET `EventBonus`=(`EventBonus` - 1) WHERE `id` = '%u'", pPlayer->GetSession()->GetAccountId());
                pPlayer->ModifyHonorPoints(+10000);
                pCreature->MonsterWhisper("Add +10000 Honor Points", pPlayer);
                pPlayer->SaveToDB();
            }
            else
            {
                pCreature->MonsterWhisper("Enough Event bonuses", pPlayer);
            }
        }
    }
#endif
    pPlayer->CLOSE_GOSSIP_MENU();
    return true;
}

void AddSC_npc_arena_honor()
{
    Script *pNewScript;
    pNewScript = new Script;
    pNewScript->Name="npc_arena_honor";
    pNewScript->pGossipHello =  &GossipHello_npc_arena_honor;
    pNewScript->pGossipSelect = &GossipSelect_npc_arena_honor;
    pNewScript->RegisterSelf();
}
