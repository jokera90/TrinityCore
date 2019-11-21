/*
 * Copyright (C) 2008-2017 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

// This is where scripts' loading functions should be declared:
void AddSC_GOMove_commandscript();
void AddSC_GMSTONE2();
void AddSC_multi_gem();
void AddSC_PlayerHelper();
void AddSC_DoubleXP();
void AddSC_REFORGER_NPC();
void AddSC_DBCexplorer();
void AddSC_GuildHouse();
void AddSC_NPC_TransmogDisplayVendor();



// The name of this function should match:
// void Add${NameOfDirectory}Scripts()
void AddCustomScripts()
{
    AddSC_GOMove_commandscript();
	AddSC_GMSTONE2();
	AddSC_multi_gem();
	AddSC_PlayerHelper();
	AddSC_DoubleXP();
	AddSC_REFORGER_NPC();
	AddSC_DBCexplorer();
	AddSC_GuildHouse();
	AddSC_NPC_TransmogDisplayVendor();
}
