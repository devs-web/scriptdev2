/*
 * Copyright (C) 2005-2012 MaNGOS <http://getmangos.com/>
 *
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

#ifndef SC_CONFIG_H
#define SC_CONFIG_H

#include "../../../config.h"
#include "Platform/CompilerDefs.h"
#include "revision.h"
#include "sd2_revision_nr.h"
#include "sd2_revision_R2.h"

// Format is YYYYMMDDRR where RR is the change in the conf file
// for that day.
#define SD2_CONF_VERSION    2012112301

// The path to config files
#ifndef SYSCONFDIR
#  define SYSCONFDIR        ""
#endif

#ifdef WIN32
  #define MANGOS_DLL_EXPORT extern "C" __declspec(dllexport)
#elif defined( __GNUC__ )
  #define MANGOS_DLL_EXPORT extern "C"
#else
  #define MANGOS_DLL_EXPORT extern "C" export
#endif

#ifndef SD2_VERSION
  #define SD2_VERSION "Revision [" SD2_REVISION_NR "] Revision R2 [" SD2_REVISION_R2 "] (" REVISION_ID ") " REVISION_DATE " " REVISION_TIME
#endif

// The path to config files
#ifndef SYSCONFDIR
  #define SYSCONFDIR ""
#endif

#if PLATFORM == PLATFORM_WINDOWS
  #ifdef _WIN64
    #define SD2_FULLVERSION SD2_VERSION " (Win64)"
  #else
    #define SD2_FULLVERSION SD2_VERSION " (Win32)"
  #endif
  #define _SCRIPTDEV2_CONFIG   SYSCONFDIR"scriptdev2.conf"
#else
  #define SD2_FULLVERSION SD2_VERSION " (Unix)"
  #define _SCRIPTDEV2_CONFIG  SYSCONFDIR"scriptdev2.conf"
#endif

#if CLIENT_VERSION >= 16057
    #define MAX_EXPANSION 4
    #define SD2_WORLD_MOP 1
    #undef  SD2_WORLD_CATA
    #undef  SD2_WORLD_WOTLK
    #undef  SD2_WORLD_TBC
    #undef  SD2_WORLD_CLASSIC
#elif CLIENT_VERSION >= 13623
    #define MAX_EXPANSION 3
    #undef  SD2_WORLD_MOP
    #define SD2_WORLD_CATA 1
    #undef  SD2_WORLD_WOTLK
    #undef  SD2_WORLD_TBC
    #undef  SD2_WORLD_CLASSIC
#elif CLIENT_VERSION > 8606
    #define MAX_EXPANSION 2
    #undef  SD2_WORLD_MOP
    #undef  SD2_WORLD_CATA
    #define SD2_WORLD_WOTLK 1
    #undef  SD2_WORLD_TBC
    #undef  SD2_WORLD_CLASSIC
#elif CLIENT_VERSION > 6005
    #define MAX_EXPANSION 1
    #undef  SD2_WORLD_MOP
    #undef  SD2_WORLD_CATA
    #undef  SD2_WORLD_WOTLK
    #define SD2_WORLD_TBC 1
    #undef  SD2_WORLD_CLASSIC
#else
    #define MAX_EXPANSION 0
    #define SD2_WORLD_MOP 1
    #undef  SD2_WORLD_CATA
    #undef  SD2_WORLD_WOTLK
    #undef  SD2_WORLD_TBC
    #define SD2_WORLD_CLASSIC 1
#endif

#if (COMPILER == COMPILER_MICROSOFT)
#  define LOCATION StaticLocation
#  define EVENTLOCATION EventLocations
#  define SPAWNLOCATION SpawnLocation
#else
#  define LOCATION Location
#  define EVENTLOCATION EventLocations
#  define SPAWNLOCATION SpawnLocation
#endif

#endif
