/*                                                     ''~``
 * @(#)resource.h 1.0  2010/01/17                     ( o o )
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
 * | Module....: Resource Header File                                 |
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


// application constants
#define IDC_APP_WCLASSNAME   		100
#define IDS_APP_TITLE				101
#define IDS_TRAY_TOOLTIP			110
#define IDS_ABOUT_TEXT              151
#define IDS_ABOUT_WEB	            152


// icon constants
#define IDI_APP_ICON				200


// bitmap constants
#define IDB_LOGO_GOS95				300
#define IDB_ABOUT_BACKGROUND		301


// notifyicon constants
#define NOTIFYICON_ID				400
#define NOTIFYICON_MESSAGE			WM_USER+1


// main menu constants
#define IDR_APP_MENU				1000
#define ID_CMD_CONFIGURE			3000
#define ID_CMD_EXIT					4000
#define ID_CMD_ABOUT	    		5000

// tt menu constants
#define ID_TT_ELEM_BASE				2000

// menu about dialog constants
#define IDD_ABOUT					5001
#define ID_LICENSE					5011
#define ID_WEB						5012
#define IDD_LICENSE					5101
