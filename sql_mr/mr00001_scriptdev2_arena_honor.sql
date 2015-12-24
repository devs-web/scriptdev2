-- npc arena-honor exchange

DELETE FROM script_texts WHERE entry in (-1001007, -1001008);
INSERT INTO script_texts (entry,content_loc8, content_default, sound, type, language, emote, comment) VALUES
('-1001007','Недостаточно ХонорПойнтов!','Your not has enough HonorPoints!','0','0','0','0','Unsuccesfull - honorpoint.'),
('-1001008','Недостаточно АренаПойнтов!','Your not has enough AranaPoints!','0','0','0','0','Unsuccesfull - arenapoint.');

-- Gossips
DELETE FROM `gossip_texts` WHERE `entry` BETWEEN -3000773 AND -3000770;
INSERT INTO `gossip_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `comment`) VALUES
('-3000770', "Exchange 100 ArenaPoints to 6000 HonorPoints", NULL, NULL, NULL, NULL, NULL, NULL, NULL, "Обменять 100 АренаПойнтов на 6000 ХонорПойнтов", "npc_arena_honor gossip 1"),
('-3000771', "Exchange 1000 ArenaPoints to 60000 HonorPoints", NULL, NULL, NULL, NULL, NULL, NULL, NULL, "Обменять 1000 АренаПойнтов на 60000 ХонорПойнтов", "npc_arena_honor gossip 2"),
('-3000772', "Exchange 3000 HonorPoints to 50 ArenaPoints", NULL, NULL, NULL, NULL, NULL, NULL, NULL, "Обменять 3000 ХонорПойнтов на 50 АренаПойнтов", "npc_arena_honor gossip 3"),
('-3000773', "Exchange 30000 HonorPoints to 500 ArenaPoints", NULL, NULL, NULL, NULL, NULL, NULL, NULL, "Обменять 30000 ХонорПойнтов на 500 АренаПойнтов", "npc_arena_honor gossip 4");
