/* ScriptData
Name: Transmogrify Npc
%Complete: 100
Category: Custom Script
EndScriptData
Кодировка... */

#include "precompiled.h"
enum 
{
    CAST_SPELL_TRANS = 63491,
};

bool GossipHello_transmogrify_script(Player* player, Creature* _Creature)
{
    _Creature->MonsterWhisper("Если хочешь убрать модель предмета, положи в первый слот. В первый слот сумки положи вещь, которой хочешь изменить вид. Во второй слот положи вещь, с которой ты хочешь взять модель.", player);

    player->ADD_GOSSIP_ITEM(0, "Сделать обмен!" , GOSSIP_SENDER_MAIN, 1203);
    player->ADD_GOSSIP_ITEM(0, "Очистить модель." , GOSSIP_SENDER_MAIN, 1204);

    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,_Creature->GetObjectGuid());
    return true;

}

void TransmogrifyItem(Player* player, Creature* _Creature)
{
    Item *trItem      = player->GetItemByPos(INVENTORY_SLOT_BAG_0, INVENTORY_SLOT_ITEM_START);
    Item *displayItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, INVENTORY_SLOT_ITEM_START + 1);
    
    if (!trItem || !displayItem)
    {
        _Creature->MonsterWhisper("Первый или второй слот главной сумки - ПУСТЫ!", player);
        return;
    }

    uint8 result = trItem->SetFakeDisplay(displayItem->GetEntry());

    switch (result)
    {
        case FAKE_ERR_CANT_FIND_ITEM:
            _Creature->MonsterWhisper("Cant find item!", player);
        break;

        case FAKE_ERR_WRONG_QUALITY:
            _Creature->MonsterWhisper("Item has wrong quality!", player);
        break;

        case FAKE_ERR_DIFF_SLOTS:
            _Creature->MonsterWhisper("Items has different types!", player);
        break;
        case FAKE_ERR_DIFF_CLASS:
        case FAKE_ERR_DIFF_RACE:
            _Creature->MonsterWhisper("Items require different options!", player);
        //break;

        case FAKE_ERR_OK:
        {
            WorldPacket data;
            data << uint8(INVENTORY_SLOT_BAG_0);
            data << uint8(trItem->GetSlot());
            player->GetSession()->HandleAutoEquipItemOpcode(data);

            _Creature->CastSpell(_Creature, CAST_SPELL_TRANS, true);
        }
        break;
    }
}

void ClearItem(Player *player, Creature* _Creature)
{
    Item *trItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, INVENTORY_SLOT_ITEM_START);
    if (!trItem)
    {
        _Creature->MonsterWhisper("Первый слот пуст!", player);
        return;
    }

    trItem->RemoveFakeDisplay();

    WorldPacket data;
    data << uint8(INVENTORY_SLOT_BAG_0);
    data << uint8(trItem->GetSlot());
    player->GetSession()->HandleAutoEquipItemOpcode(data);

    _Creature->CastSpell(_Creature, CAST_SPELL_TRANS, true);
}

void SendDefaultMenu_transmogrify_script(Player* player, Creature* _Creature, uint32 action)
{
    if (player->IsInCombat())
    {
        player->CLOSE_GOSSIP_MENU();
        _Creature->MonsterWhisper("Ты находишься в бою!", player);
        return;
    }

    switch (action)
    {
        case 1203:
        {
            player->CLOSE_GOSSIP_MENU();
            TransmogrifyItem(player, _Creature);
        }
        break;
        case 1204:
        {
            player->CLOSE_GOSSIP_MENU();
            ClearItem(player, _Creature);
        }
        break;


    }
}

bool GossipSelect_transmogrify_script(Player* player, Creature* _Creature, uint32 sender, uint32 action)
{
    if (sender == GOSSIP_SENDER_MAIN)
    {
        player->PlayerTalkClass->ClearMenus();
        SendDefaultMenu_transmogrify_script(player, _Creature, action);
    }
    return true;
}

void AddSC_transmogrify_script()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_transmogrify";
    pNewScript->pGossipHello = &GossipHello_transmogrify_script;
    pNewScript->pGossipSelect = &GossipSelect_transmogrify_script;
    pNewScript->RegisterSelf();
}