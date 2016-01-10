#include "precompiled.h"
#include "CustomVendor.h"

void IterateCategory(Player* player, Creature* creature, int category = 0)
{
    player->PlayerTalkClass->ClearMenus();
    VendorEntryList *result = CustomVendorMgr.GetItemsForEntry(creature->GetCreatureInfo()->Entry, 0);
    int oldAction = 0;
    bool breaked  = false;
    
    for (VendorEntryList::iterator i = result->begin(); i != result->end(); ++i)
    {
        VendorEntry *vendorEntry = *i;
        
        if (vendorEntry->guid + 1205 == category)
            oldAction = vendorEntry->daug_guid;
        
        if (category == 0 && vendorEntry->daug_guid == 0)
        {
            player->ADD_GOSSIP_ITEM(vendorEntry->icon, vendorEntry->desc, GOSSIP_SENDER_MAIN, vendorEntry->guid + 1205);
        }
        else if (vendorEntry->group == 1 && vendorEntry->daug_guid == category - 1205 && vendorEntry->vendor_entry == 0)
        {
            player->ADD_GOSSIP_ITEM(vendorEntry->icon, vendorEntry->desc, GOSSIP_SENDER_MAIN, vendorEntry->guid + 1205);
        }
        else if (vendorEntry->daug_guid == category - 1205 && vendorEntry->vendor_entry != 0)
        {
            player->ADD_GOSSIP_ITEM(vendorEntry->icon, vendorEntry->desc, GOSSIP_SENDER_MAIN, vendorEntry->guid + 1205);
        }
        else if (vendorEntry->vendor_entry != 0 && category - 1205 == vendorEntry->guid)
        {
            breaked = true;
            player->currentVendorEntry = vendorEntry->vendor_entry;
            player->GetSession()->_SendListInventory(creature->GetObjectGuid(), vendorEntry->vendor_entry);
            break;
        }
    }
    
    if (breaked)
        return;
    
    if (category > 0)
        player->ADD_GOSSIP_ITEM(0, "<- [Назад]", GOSSIP_SENDER_MAIN, oldAction + 1205);
    
    player->PlayerTalkClass->SendGossipMenu(907, creature->GetObjectGuid());
}

bool OnGossipHello_npc_vendor_multi(Player* player, Creature* creature)
{
    IterateCategory(player, creature);
    return true;
}

bool GossipSelect_npc_vendor_multi(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
{
    IterateCategory(player, creature, uiAction);
    return true;
}

void AddSC_vendor_multi()
{
    Script *pNewScript;
    pNewScript = new Script;
    pNewScript->Name="npc_vendor_multi";
    pNewScript->pGossipHello =  &OnGossipHello_npc_vendor_multi;
    pNewScript->pGossipSelect = &GossipSelect_npc_vendor_multi;
    pNewScript->RegisterSelf();
}
