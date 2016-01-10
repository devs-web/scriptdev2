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

bool GossipHello_npcAllTrainer_script(Player* player, Creature* _Creature)
{
    player->ADD_GOSSIP_ITEM(5, "Верховая езда" , GOSSIP_SENDER_MAIN, 1209);
    player->ADD_GOSSIP_ITEM(5, "Навыки оружия" , GOSSIP_SENDER_MAIN, 1207);
    player->ADD_GOSSIP_ITEM(5, "Тренировать классовые навыки" , GOSSIP_SENDER_MAIN, 1203);
    player->ADD_GOSSIP_ITEM(5, "MAX SKILL" , GOSSIP_SENDER_MAIN, 1204);
    player->ADD_GOSSIP_ITEM(7, "Профессии" , GOSSIP_SENDER_MAIN, 1210);
    player->ADD_GOSSIP_ITEM(6, "Сбросить таланты" , GOSSIP_SENDER_MAIN, 1208);


    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,_Creature->GetObjectGuid());
    return true;
}

void _LearnWeapon(Player* player, Creature* _Creature, int array[], int arraysize)
{
    for (int i = 0; i <= arraysize; i++)
        player->learnSpell(array[i], false);
}

void LearnWeapon(Player* player, Creature* _Creature)
{
    uint8 PlayerClass = ((Unit*)player)->getClass();

    int CLASS_WARRIOR_WEAPONS[11]     = {5011, 199, 202, 200, 198, 1180, 15590, 264, 2567, 266, 227};
    int CLASS_PALADIN_WEAPONS[6]      = {199, 197, 200, 198, 196};
    int CLASS_HUNTER_WEAPONS[9]       = {5011, 202, 200, 15590, 2567, 201, 266, 227, 196};
    int CLASS_ROGUE_WEAPONS[7]        = {5011, 198, 15590, 264, 201, 266, 196};
    int CLASS_PRIEST_WEAPONS[1]       = {1180};
    int CLASS_DEATH_KNIGHT_WEAPONS[2] = {199, 198};
    int CLASS_SHAMAN_WEAPONS[5]       = {199, 197, 1180, 15590, 196};
    int CLASS_MAGE_WEAPONS[2]         = {1180, 201};
    int CLASS_WARLOCK_WEAPONS[1]      = {201};
    int CLASS_DRUID_WEAPONS[4]        = {199, 200, 1180, 15590};
    
    switch(PlayerClass)
    {
        case CLASS_WARRIOR:      _LearnWeapon(player, _Creature, CLASS_WARRIOR_WEAPONS, 10); break;
        case CLASS_PALADIN:      _LearnWeapon(player, _Creature, CLASS_PALADIN_WEAPONS, 5); break;
        case CLASS_HUNTER:       _LearnWeapon(player, _Creature, CLASS_HUNTER_WEAPONS, 8); break;
        case CLASS_ROGUE:        _LearnWeapon(player, _Creature, CLASS_ROGUE_WEAPONS, 6); break;
        case CLASS_PRIEST:       _LearnWeapon(player, _Creature, CLASS_PRIEST_WEAPONS, 0); break;
        case CLASS_DEATH_KNIGHT: _LearnWeapon(player, _Creature, CLASS_DEATH_KNIGHT_WEAPONS, 1); break;
        case CLASS_SHAMAN:       _LearnWeapon(player, _Creature, CLASS_SHAMAN_WEAPONS, 4); break;
        case CLASS_MAGE:         _LearnWeapon(player, _Creature, CLASS_MAGE_WEAPONS, 1); break;
        case CLASS_WARLOCK:      _LearnWeapon(player, _Creature, CLASS_WARLOCK_WEAPONS, 0); break;
        case CLASS_DRUID:        _LearnWeapon(player, _Creature, CLASS_DRUID_WEAPONS, 3); break;
    }
    player->CLOSE_GOSSIP_MENU();
}


bool CheckNeedLearnSpell(Player* player, uint32 spellId, Creature* _Creature)
{
    if (player->HasSpell(spellId))
        return false;

    switch (spellId)
    {
        case 19238: return player->HasSpell(19236); break;  // Молитва отчаяния (жрец)
        case 19240: return player->HasSpell(19236); break;  // Молитва отчаяния (жрец)
        case 19241: return player->HasSpell(19236); break;  // Молитва отчаяния (жрец)
        case 19242: return player->HasSpell(19236); break;  // Молитва отчаяния (жрец)
        case 19243: return player->HasSpell(19236); break;  // Молитва отчаяния (жрец)
        case 25437: return player->HasSpell(19236); break;  // Молитва отчаяния (жрец)
        case 48172: return player->HasSpell(19236); break;  // Молитва отчаяния (жрец)
        case 48173: return player->HasSpell(19236); break;  // Молитва отчаяния (жрец)

        case 17311: return player->HasSpell(15407); break;  // Пытка разума (жрец)
        case 17312: return player->HasSpell(15407); break;  // Пытка разума (жрец)
        case 17313: return player->HasSpell(15407); break;  // Пытка разума (жрец)
        case 17314: return player->HasSpell(15407); break;  // Пытка разума (жрец)
        case 18807: return player->HasSpell(15407); break;  // Пытка разума (жрец)
        case 25387: return player->HasSpell(15407); break;  // Пытка разума (жрец)
        case 48155: return player->HasSpell(15407); break;  // Пытка разума (жрец)
        case 48156: return player->HasSpell(15407); break;  // Пытка разума (жрец)

        case 27870: return player->HasSpell(724); break;  // Колодец света (жрец)
        case 27871: return player->HasSpell(724); break;  // Колодец света (жрец)
        case 28275: return player->HasSpell(724); break;  // Колодец света (жрец)
        case 48086: return player->HasSpell(724); break;  // Колодец света (жрец)
        case 48087: return player->HasSpell(724); break;  // Колодец света (жрец)

        case 34863: return player->HasSpell(34861); break;  // Круг исцеления (жрец)
        case 34864: return player->HasSpell(34861); break;  // Круг исцеления (жрец)
        case 34865: return player->HasSpell(34861); break;  // Круг исцеления (жрец)
        case 34866: return player->HasSpell(34861); break;  // Круг исцеления (жрец)
        case 48088: return player->HasSpell(34861); break;  // Круг исцеления (жрец)
        case 48089: return player->HasSpell(34861); break;  // Круг исцеления (жрец)

        case 34916: return player->HasSpell(34914); break;  // Прикосновение вампира (жрец)
        case 34917: return player->HasSpell(34914); break;  // Прикосновение вампира (жрец)
        case 48159: return player->HasSpell(34914); break;  // Прикосновение вампира (жрец)
        case 48160: return player->HasSpell(34914); break;  // Прикосновение вампира (жрец)

        case 53005: return player->HasSpell(47540); break;  // Исповедь (жрец)
        case 53006: return player->HasSpell(47540); break;  // Исповедь (жрец)
        case 53007: return player->HasSpell(47540); break;  // Исповедь (жрец)

        case 21551: return player->HasSpell(12294); break;  // Смертельный удар (вар)
        case 21552: return player->HasSpell(12294); break;  // Смертельный удар (вар)
        case 21553: return player->HasSpell(12294); break;  // Смертельный удар (вар)
        case 25248: return player->HasSpell(12294); break;  // Смертельный удар (вар)
        case 30330: return player->HasSpell(12294); break;  // Смертельный удар (вар)
        case 47485: return player->HasSpell(12294); break;  // Смертельный удар (вар)
        case 47486: return player->HasSpell(12294); break;  // Смертельный удар (вар)

        case 30016: return player->HasSpell(20243); break;  // Сокрушение (вар)
        case 30022: return player->HasSpell(20243); break;  // Сокрушение (вар)
        case 47497: return player->HasSpell(20243); break;  // Сокрушение (вар)
        case 47498: return player->HasSpell(20243); break;  // Сокрушение (вар)

        case 20927: return player->HasSpell(20925); break;  // Щит небес (пал)
        case 20928: return player->HasSpell(20925); break;  // Щит небес (пал)
        case 27179: return player->HasSpell(20925); break;  // Щит небес (пал)
        case 48951: return player->HasSpell(20925); break;  // Щит небес (пал)
        case 48952: return player->HasSpell(20925); break;  // Щит небес (пал)

        case 32699: return player->HasSpell(31935); break;  // Щит мстителя (пал)
        case 32700: return player->HasSpell(31935); break;  // Щит мстителя (пал)
        case 48826: return player->HasSpell(31935); break;  // Щит мстителя (пал)
        case 48827: return player->HasSpell(31935); break;  // Щит мстителя (пал)

        case 20929: return player->HasSpell(20473); break;  // Шок небес (пал)
        case 20930: return player->HasSpell(20473); break;  // Шок небес (пал)
        case 27174: return player->HasSpell(20473); break;  // Шок небес (пал)
        case 33072: return player->HasSpell(20473); break;  // Шок небес (пал)
        case 48824: return player->HasSpell(20473); break;  // Шок небес (пал)
        case 48825: return player->HasSpell(20473); break;  // Шок небес (пал)

        case 25899: return player->HasSpell(20911); break;  // Благословение неприкосновенности (пал)

        case 60051: return player->HasSpell(53301); break;  // Разрывной выстрел (Хант)
        case 60052: return player->HasSpell(53301); break;  // Разрывной выстрел (Хант)
        case 60053: return player->HasSpell(53301); break;  // Разрывной выстрел (Хант)

        case 63668: return player->HasSpell(3674); break;  // Черная стрела (Хант)
        case 63669: return player->HasSpell(3674); break;  // Черная стрела (Хант)
        case 63670: return player->HasSpell(3674); break;  // Черная стрела (Хант)
        case 63671: return player->HasSpell(3674); break;  // Черная стрела (Хант)
        case 63672: return player->HasSpell(3674); break;  // Черная стрела (Хант)

        case 20900: return player->HasSpell(19434); break;  // Прицельный выстрел (Хант)
        case 20901: return player->HasSpell(19434); break;  // Прицельный выстрел (Хант)
        case 20902: return player->HasSpell(19434); break;  // Прицельный выстрел (Хант)
        case 20903: return player->HasSpell(19434); break;  // Прицельный выстрел (Хант)
        case 20904: return player->HasSpell(19434); break;  // Прицельный выстрел (Хант)
        case 27065: return player->HasSpell(19434); break;  // Прицельный выстрел (Хант)
        case 49049: return player->HasSpell(19434); break;  // Прицельный выстрел (Хант)
        case 49050: return player->HasSpell(19434); break;  // Прицельный выстрел (Хант)

        case 20909: return player->HasSpell(19306); break;  // Контратака (Хант)
        case 20910: return player->HasSpell(19306); break;  // Контратака (Хант)
        case 27067: return player->HasSpell(19306); break;  // Контратака (Хант)
        case 48998: return player->HasSpell(19306); break;  // Контратака (Хант)
        case 48999: return player->HasSpell(19306); break;  // Контратака (Хант)

        case 24132: return player->HasSpell(19386); break;  // Укус виверны (Хант)
        case 24133: return player->HasSpell(19386); break;  // Укус виверны (Хант)
        case 27068: return player->HasSpell(19386); break;  // Укус виверны (Хант)
        case 49011: return player->HasSpell(19386); break;  // Укус виверны (Хант)
        case 49012: return player->HasSpell(19386); break;  // Укус виверны (Хант)

        case 34411: return player->HasSpell(1329); break;  // Расправа (Рога)
        case 34412: return player->HasSpell(1329); break;  // Расправа (Рога)
        case 34413: return player->HasSpell(1329); break;  // Расправа (Рога)
        case 48663: return player->HasSpell(1329); break;  // Расправа (Рога)
        case 48666: return player->HasSpell(1329); break;  // Расправа (Рога)

        case 17347: return player->HasSpell(16511); break;  // Кровоизлияние (Рога)
        case 17348: return player->HasSpell(16511); break;  // Кровоизлияние (Рога)
        case 26864: return player->HasSpell(16511); break;  // Кровоизлияние (Рога)
        case 48660: return player->HasSpell(16511); break;  // Кровоизлияние (Рога)

        case 57720: return player->HasSpell(30706); break;  // Тотем гнева (Шам)
        case 57721: return player->HasSpell(30706); break;  // Тотем гнева (Шам)
        case 57722: return player->HasSpell(30706); break;  // Тотем гнева (Шам)

        case 32593: return player->HasSpell(974); break;  // Щит земли (Шам)
        case 32594: return player->HasSpell(974); break;  // Щит земли (Шам)
        case 49283: return player->HasSpell(974); break;  // Щит земли (Шам)
        case 49284: return player->HasSpell(974); break;  // Щит земли (Шам)

        case 61299: return player->HasSpell(61295); break;  // Щит земли (Шам)
        case 61300: return player->HasSpell(61295); break;  // Щит земли (Шам)
        case 61301: return player->HasSpell(61295); break;  // Щит земли (Шам)

        case 59156: return player->HasSpell(51490); break;  // Гром и молния (Шам)
        case 59158: return player->HasSpell(51490); break;  // Гром и молния (Шам)
        case 59159: return player->HasSpell(51490); break;  // Гром и молния (Шам)

        case 55359: return player->HasSpell(44457); break;  // Живая бомба (Маг)
        case 55360: return player->HasSpell(44457); break;  // Живая бомба (Маг)

        case 13031: return player->HasSpell(11429); break;  // Ледяная преграда (Маг)
        case 13032: return player->HasSpell(11429); break;  // Ледяная преграда (Маг)
        case 13033: return player->HasSpell(11429); break;  // Ледяная преграда (Маг)
        case 27134: return player->HasSpell(11429); break;  // Ледяная преграда (Маг)
        case 33405: return player->HasSpell(11429); break;  // Ледяная преграда (Маг)
        case 43038: return player->HasSpell(11429); break;  // Ледяная преграда (Маг)
        case 43039: return player->HasSpell(11429); break;  // Ледяная преграда (Маг)

        case 12505: return player->HasSpell(11366); break;  // Огненая глыба (Маг)
        case 12522: return player->HasSpell(11366); break;  // Огненая глыба (Маг)
        case 12523: return player->HasSpell(11366); break;  // Огненая глыба (Маг)
        case 12524: return player->HasSpell(11366); break;  // Огненая глыба (Маг)
        case 12525: return player->HasSpell(11366); break;  // Огненая глыба (Маг)
        case 12526: return player->HasSpell(11366); break;  // Огненая глыба (Маг)
        case 18809: return player->HasSpell(11366); break;  // Огненая глыба (Маг)
        case 27132: return player->HasSpell(11366); break;  // Огненая глыба (Маг)
        case 33938: return player->HasSpell(11366); break;  // Огненая глыба (Маг)
        case 42890: return player->HasSpell(11366); break;  // Огненая глыба (Маг)
        case 42891: return player->HasSpell(11366); break;  // Огненая глыба (Маг)

        case 33041: return player->HasSpell(31661); break;  // Дыхание дракона (Маг)
        case 33042: return player->HasSpell(31661); break;  // Дыхание дракона (Маг)
        case 33043: return player->HasSpell(31661); break;  // Дыхание дракона (Маг)
        case 42949: return player->HasSpell(31661); break;  // Дыхание дракона (Маг)
        case 42950: return player->HasSpell(31661); break;  // Дыхание дракона (Маг)

        case 44780: return player->HasSpell(44425); break;  // Чародейский обстрел (Маг)
        case 44781: return player->HasSpell(44425); break;  // Чародейский обстрел (Маг)

        case 13018: return player->HasSpell(11113); break;  // Взрывная волна (Маг)
        case 13019: return player->HasSpell(11113); break;  // Взрывная волна (Маг)
        case 13020: return player->HasSpell(11113); break;  // Взрывная волна (Маг)
        case 13021: return player->HasSpell(11113); break;  // Взрывная волна (Маг)
        case 27133: return player->HasSpell(11113); break;  // Взрывная волна (Маг)
        case 33933: return player->HasSpell(11113); break;  // Взрывная волна (Маг)
        case 42944: return player->HasSpell(11113); break;  // Взрывная волна (Маг)
        case 42945: return player->HasSpell(11113); break;  // Взрывная волна (Маг)

        case 30413: return player->HasSpell(30283); break;  // Неистовство Тьмы (лок)
        case 30414: return player->HasSpell(30283); break;  // Неистовство Тьмы (лок)
        case 47846: return player->HasSpell(30283); break;  // Неистовство Тьмы (лок)
        case 47847: return player->HasSpell(30283); break;  // Неистовство Тьмы (лок)

        case 59161: return player->HasSpell(48181); break;  // Блуждающий дух (лок)
        case 59163: return player->HasSpell(48181); break;  // Блуждающий дух (лок)
        case 59164: return player->HasSpell(48181); break;  // Блуждающий дух (лок)

        case 18867: return player->HasSpell(17877); break;  // Ожог Тьмы (лок)
        case 18868: return player->HasSpell(17877); break;  // Ожог Тьмы (лок)
        case 18869: return player->HasSpell(17877); break;  // Ожог Тьмы (лок)
        case 18870: return player->HasSpell(17877); break;  // Ожог Тьмы (лок)
        case 18871: return player->HasSpell(17877); break;  // Ожог Тьмы (лок)
        case 27263: return player->HasSpell(17877); break;  // Ожог Тьмы (лок)
        case 30546: return player->HasSpell(17877); break;  // Ожог Тьмы (лок)
        case 47826: return player->HasSpell(17877); break;  // Ожог Тьмы (лок)
        case 47827: return player->HasSpell(17877); break;  // Ожог Тьмы (лок)

        case 30404: return player->HasSpell(30108); break;  // Нестабильное колдовство (лок)
        case 30405: return player->HasSpell(30108); break;  // Нестабильное колдовство (лок)
        case 47841: return player->HasSpell(30108); break;  // Нестабильное колдовство (лок)
        case 47843: return player->HasSpell(30108); break;  // Нестабильное колдовство (лок)

        case 59170: return player->HasSpell(50796); break;  // Стрела Хаоса (лок)
        case 59171: return player->HasSpell(50796); break;  // Стрела Хаоса (лок)
        case 59172: return player->HasSpell(50796); break;  // Стрела Хаоса (лок)

        case 18937: return player->HasSpell(18220); break;  // Темный союз (лок)
        case 18938: return player->HasSpell(18220); break;  // Темный союз (лок)
        case 27265: return player->HasSpell(18220); break;  // Темный союз (лок)
        case 59092: return player->HasSpell(18220); break;  // Темный союз (лок)

        case 55265: return player->HasSpell(55090); break;  // Удар Плети (ДК)
        case 55270: return player->HasSpell(55090); break;  // Удар Плети (ДК)
        case 55271: return player->HasSpell(55090); break;  // Удар Плети (ДК)

        case 51325: return player->HasSpell(49158); break;  // Взрыв трупа (ДК)
        case 51326: return player->HasSpell(49158); break;  // Взрыв трупа (ДК)
        case 51327: return player->HasSpell(49158); break;  // Взрыв трупа (ДК)
        case 51328: return player->HasSpell(49158); break;  // Взрыв трупа (ДК)

        case 51416: return player->HasSpell(49143); break;  // Ледяной удар (ДК)
        case 51417: return player->HasSpell(49143); break;  // Ледяной удар (ДК)
        case 51418: return player->HasSpell(49143); break;  // Ледяной удар (ДК)
        case 51419: return player->HasSpell(49143); break;  // Ледяной удар (ДК)
        case 55268: return player->HasSpell(49143); break;  // Ледяной удар (ДК)

        case 51409: return player->HasSpell(49184); break;  // Воющий ветер (ДК)
        case 51410: return player->HasSpell(49184); break;  // Воющий ветер (ДК)
        case 51411: return player->HasSpell(49184); break;  // Воющий ветер (ДК)

        case 55258: return player->HasSpell(55050); break;  // Удар в сердце (ДК)
        case 55259: return player->HasSpell(55050); break;  // Удар в сердце (ДК)
        case 55260: return player->HasSpell(55050); break;  // Удар в сердце (ДК)
        case 55261: return player->HasSpell(55050); break;  // Удар в сердце (ДК)
        case 55262: return player->HasSpell(55050); break;  // Удар в сердце (ДК)

        case 53248: return player->HasSpell(48438); break;  // Буйный рост (Дру)
        case 53249: return player->HasSpell(48438); break;  // Буйный рост (Дру)
        case 53251: return player->HasSpell(48438); break;  // Буйный рост (Дру)

        case 24974: return player->HasSpell(5570); break;  // Рой насекомых (Дру)
        case 24975: return player->HasSpell(5570); break;  // Рой насекомых (Дру)
        case 24976: return player->HasSpell(5570); break;  // Рой насекомых (Дру)
        case 24977: return player->HasSpell(5570); break;  // Рой насекомых (Дру)
        case 27013: return player->HasSpell(5570); break;  // Рой насекомых (Дру)
        case 48468: return player->HasSpell(5570); break;  // Рой насекомых (Дру)

        case 53223: return player->HasSpell(50516); break;  // Тайфун (Дру)
        case 53225: return player->HasSpell(50516); break;  // Тайфун (Дру)
        case 53226: return player->HasSpell(50516); break;  // Тайфун (Дру)
        case 61384: return player->HasSpell(50516); break;  // Тайфун (Дру)

        case 53199: return player->HasSpell(48505); break;  // Звездопад (Дру)
        case 53200: return player->HasSpell(48505); break;  // Звездопад (Дру)
        case 53201: return player->HasSpell(48505); break;  // Звездопад (Дру)

        case 33982: return player->HasSpell(33876); break;  // Увечье (кошка) (Дру)
        case 33983: return player->HasSpell(33876); break;  // Увечье (кошка) (Дру)
        case 48565: return player->HasSpell(33876); break;  // Увечье (кошка) (Дру)
        case 48566: return player->HasSpell(33876); break;  // Увечье (кошка) (Дру)

        case 33986: return player->HasSpell(33878); break;  // Увечье (медведь) (Дру)
        case 33987: return player->HasSpell(33878); break;  // Увечье (медведь) (Дру)
        case 48563: return player->HasSpell(33878); break;  // Увечье (медведь) (Дру)
        case 48564: return player->HasSpell(33878); break;  // Увечье (медведь) (Дру)

        default: return true;
    }
}

uint32 CheckSpellIdForFaction (Player* player, uint32 spellId)
{
    Team team = player->GetTeam();
    
    switch (spellId)
    {
        case 31801: return team == ALLIANCE ? 31801 : 53736; break;
        case 53736: return team == ALLIANCE ? 31801 : 53736; break;
        default: return spellId;
    }
}

void LearnSpellsFromEntry (Player* player, uint32 TrainerID, bool talents, Creature* _Creature)
{
    uint8 PlayerClass = ((Unit*)player)->getClass();
    if (PlayerClass == CLASS_DEATH_KNIGHT)
    {
        player->learnSpell(53431, false);
    }

    TrainerSpellData const* cSpells = sObjectMgr.GetNpcTrainerSpells(TrainerID);
    for (TrainerSpellMap::const_iterator itr = cSpells->spellList.begin(); itr != cSpells->spellList.end(); itr++)
    {
        uint32 spellId = itr->first;
        if (CheckNeedLearnSpell(player, spellId, _Creature))
        {
            spellId = CheckSpellIdForFaction(player, spellId);
            player->learnSpell(spellId, false);
        }
    }
    player->CLOSE_GOSSIP_MENU();
}

void HandleLearnSkillRecipesHelper(Player* player, uint32 skill_id)
{
    uint32 classmask = player->getClassMask();

    for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
    {
        SkillLineAbilityEntry const* skillLine = sSkillLineAbilityStore.LookupEntry(j);
        if (!skillLine)
            continue;

        // wrong skill
        if (skillLine->skillId != skill_id)
            continue;

        // not high rank
        if (skillLine->forward_spellid)
            continue;

        // skip racial skills
        if (skillLine->racemask != 0)
            continue;

        // skip wrong class skills
        if (skillLine->classmask && (skillLine->classmask & classmask) == 0)
            continue;

        SpellEntry const* spellInfo = sSpellStore.LookupEntry(skillLine->spellId);
        if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo, player, false))
            continue;

        player->learnSpell(skillLine->spellId, false);
    }
    player->CLOSE_GOSSIP_MENU();
}

void LearnSkillTest(Player* player, Creature* _Creature, uint32 skill_id)
{
    HandleLearnSkillRecipesHelper(player, skill_id);
    uint16 maxLevel = player->GetPureMaxSkillValue(skill_id);
    player->SetSkill(skill_id, maxLevel, maxLevel);
    
    if (skill_id == 165)
    {
        player->learnSpell(57683, false);
    }
    player->CLOSE_GOSSIP_MENU();
}

void SendDefaultMenu_npcAllTrainer_script(Player* player, Creature* _Creature, uint32 action)
{
    if (player->IsInCombat())
    {
        player->CLOSE_GOSSIP_MENU();
        _Creature->MonsterWhisper("Ты находишься в бою!", player);
        return;
    }

    uint8 PlayerClass = ((Unit*)player)->getClass();
    uint32 TrainerID = 0;

    switch (PlayerClass)
    {
        case CLASS_WARRIOR:      player->GetTeam() == ALLIANCE ? TrainerID = 914 : TrainerID = 3353; break;
        case CLASS_PALADIN:      player->GetTeam() == ALLIANCE ? TrainerID = 928 : TrainerID = 23128; break; // С печатью беда. (Проверить фикс...)
        case CLASS_HUNTER:       player->GetTeam() == ALLIANCE ? TrainerID = 5515 : TrainerID = 3407; break;
        case CLASS_ROGUE:        player->GetTeam() == ALLIANCE ? TrainerID = 918 : TrainerID = 3327; break;
        case CLASS_PRIEST:       player->GetTeam() == ALLIANCE ? TrainerID = 376 : TrainerID = 6018; break;
        case CLASS_DEATH_KNIGHT: TrainerID = 31084; break;
        case CLASS_SHAMAN:       player->GetTeam() == ALLIANCE ? TrainerID = 20407 : TrainerID = 3403; break;
        case CLASS_MAGE:         player->GetTeam() == ALLIANCE ? TrainerID = 5497 : TrainerID = 5882; break;
        case CLASS_WARLOCK:      player->GetTeam() == ALLIANCE ? TrainerID = 461 : TrainerID = 3324; break; // отловить, что учиться скрытое
        case CLASS_DRUID:        player->GetTeam() == ALLIANCE ? TrainerID = 5506 : TrainerID = 3036; break;  // Тут полная жопа...
        default: return;
    }

    switch (action)
    {
        case 1203: LearnSpellsFromEntry(player, TrainerID, true, _Creature); break;
        case 1204: player->UpdateSkillsToMaxSkillsForLevel(); player->CLOSE_GOSSIP_MENU(); break;
        case 1207: LearnWeapon(player, _Creature); break;
        case 1208: player->resetTalents(true); player->SendTalentsInfoData(false); break;
        case 1209: LearnSpellsFromEntry(player, 31238, false, _Creature); break;
        case 1210:
        {
            player->ADD_GOSSIP_ITEM(5, "Первая помощь" , GOSSIP_SENDER_MAIN, 1211);  // Первая помощь
            player->ADD_GOSSIP_ITEM(5, "Кузнечное дело" , GOSSIP_SENDER_MAIN, 1212);  // Кузнечное дело
            player->ADD_GOSSIP_ITEM(5, "Кожевничество" , GOSSIP_SENDER_MAIN, 1213);  // Кожевничество
            player->ADD_GOSSIP_ITEM(5, "Алхимия" , GOSSIP_SENDER_MAIN, 1214);  // Алхимия
            player->ADD_GOSSIP_ITEM(5, "Кулинария" , GOSSIP_SENDER_MAIN, 1215);  // Кулинария
            player->ADD_GOSSIP_ITEM(5, "Протяжное дело" , GOSSIP_SENDER_MAIN, 1216);  // Протяжное дело
            player->ADD_GOSSIP_ITEM(5, "Инженерное дело" , GOSSIP_SENDER_MAIN, 1217);  // Инженерное дело
            player->ADD_GOSSIP_ITEM(5, "Наложение чар" , GOSSIP_SENDER_MAIN, 1218);  // Наложение чар
            player->ADD_GOSSIP_ITEM(5, "Ювелирное дело" , GOSSIP_SENDER_MAIN, 1219);  // Ювелирное дело
            player->ADD_GOSSIP_ITEM(5, "Начертание" , GOSSIP_SENDER_MAIN, 1220);  // Начертание
            player->ADD_GOSSIP_ITEM(5, "Горное" , GOSSIP_SENDER_MAIN, 1221);  // Горное
            player->ADD_GOSSIP_ITEM(5, "Травничество" , GOSSIP_SENDER_MAIN, 1222);  // Травничество
            player->ADD_GOSSIP_ITEM(5, "Снятие шкур" , GOSSIP_SENDER_MAIN, 1223);  // Снятие шкур
            player->ADD_GOSSIP_ITEM(5, "Рыбная ловля" , GOSSIP_SENDER_MAIN, 1224);  // Рыбная ловля
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,_Creature->GetObjectGuid());

        } break;

        case 1211: LearnSkillTest(player, _Creature, 129); break;
        case 1212: LearnSkillTest(player, _Creature, 164); break;
        case 1213: LearnSkillTest(player, _Creature, 165); break;
        case 1214: LearnSkillTest(player, _Creature, 171); break;
        case 1215: LearnSkillTest(player, _Creature, 185); break;
        case 1216: LearnSkillTest(player, _Creature, 197); break;
        case 1217: LearnSkillTest(player, _Creature, 202); break;
        case 1218: LearnSkillTest(player, _Creature, 333); break;
        case 1219: LearnSkillTest(player, _Creature, 755); break;
        case 1220: LearnSkillTest(player, _Creature, 773); break;
        case 1221: LearnSkillTest(player, _Creature, 186); break;
        case 1222: LearnSkillTest(player, _Creature, 182); break;
        case 1223: LearnSkillTest(player, _Creature, 393); break;
        case 1224: LearnSkillTest(player, _Creature, 356); break;
        
    }
}

bool GossipSelect_npcAllTrainer_script(Player* player, Creature* _Creature, uint32 sender, uint32 action)
{
    if (sender == GOSSIP_SENDER_MAIN)
    {
        player->PlayerTalkClass->ClearMenus();
        SendDefaultMenu_npcAllTrainer_script(player, _Creature, action);
    }
    return true;
}

void AddSC_npcAllTrainer_script()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_alltrainer";
    pNewScript->pGossipHello = &GossipHello_npcAllTrainer_script;
    pNewScript->pGossipSelect = &GossipSelect_npcAllTrainer_script;
    pNewScript->RegisterSelf();
}