/*                                                     ''~``
 * @(#)Traytree.h 1.1  2010/01/17 - 2010/03/05        ( o o )
 * +---------------------------------------------.oooO--(_)--Oooo.----+
 * |   ________        _________________.________                     |
 * |  /  _____/  ____ /   _____/   __   \   ____/                     |
 * | /   \  ___ /  _ \\_____  \\____    /____  \                      |
 * | \    \_\  (  <_> )        \  /    //       \                     |
 * |  \______  /\____/_______  / /____//______  /                     |
 * |         \/              \/               \/                      |
 * | Copyright (c) 2010 by                                            |
 * | Alessandro Fraschetti (gos95@gommagomma.net)                     |
 * |                                                                  |
 * | Project...: Traytree - A system-tray directories access utility  |
 * | Module....: Main Header File                                     |
 * | Author....: Alessandro Fraschetti                                |
 * | Notes.....:                                                      |
 * |                                              .oooO               |
 * |                                             (     )    Oooo.     |
 * +-----------------------------------------------\  (----(    )-----+
 *                                                  \_ )    )  /
 * For more information about Traytree visit:              ( _/
 *     http://gommagomma.net/gos95/Traytree
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as 
 *  published by the Free Software Foundation; either version 2 of the
 *  License, or (at your option) any later version. 
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 */


#include "resource.h"


/* constants */
#define MAX_LOADSTRING 200
#define TT_CONF_FILE   "Traytree.ini"
#define TT_MENU_SEP    "<separator>"
#define TT_CONF_SEP    '='
#define TT_MAX_SIZE    30


/* tt elements struct */
typedef struct tt_element
{
    TCHAR      alias[MAX_LOADSTRING];
    TCHAR      path[MAX_LOADSTRING];
} TTELEMENT;
