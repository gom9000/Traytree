/*                                                     ''~``
 * @(#)Traytree.cpp 1.1  2010/01/17 - 2010/03/05      ( o o )
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
 * | Module....: WinMain                                              |
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


#define STRICT
#define WIN32_LEAN_AND_MEAN


#include <process.h>
#include <windows.h>
#include <commctrl.h>
#include <shellapi.h>
#include <stdio.h>
#include "Traytree.h"


// Windows Application Function Prototypes
ATOM             RegisterTheClass(HINSTANCE hInstance);
BOOL             CreateTheWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK TheWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// TaskBar Function Prototypes
BOOL             AddTaskBarIcon(HINSTANCE hInstance, HWND hWnd, UINT uID, UINT icon, LPCSTR lpszTip);
BOOL             DeleteTaskBarIcon(HWND hWnd, UINT uID);
void             ShowTrayMenu(HINSTANCE hInstance, HWND hWnd);

// Configuration Function Prototypes
BOOL             loadTTElements(void);

// Dialog Function Prototypes
BOOL CALLBACK    AboutDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Global Variables
TCHAR szTitle[MAX_LOADSTRING];
TCHAR szWindowClass[MAX_LOADSTRING];
TCHAR szTrayToolTip[MAX_LOADSTRING];
TTELEMENT ttelem[TT_MAX_SIZE];

int flagButtonDown = 0;


/*
 * WinMain
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(hPrevInst);

	InitCommonControls();

    // Initialize Global Strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_APP_WCLASSNAME, szWindowClass, MAX_LOADSTRING);
	LoadString(hInstance, IDS_TRAY_TOOLTIP, szTrayToolTip, MAX_LOADSTRING);


	//Registering the Window Class
    if ( !RegisterTheClass(hInstance) )
	{
		MessageBox(NULL, "Window Registration Failed!", szTitle, MB_ICONSTOP | MB_OK);
        return FALSE;
    }

    // Creating the Window
	if ( !CreateTheWindow(hInstance, nCmdShow) )
	{
	    MessageBox(NULL, "Window Creation Failed!", szTitle, MB_ICONSTOP | MB_OK);
		return FALSE;
	}

    // The Message Loop
    while ( GetMessage(&msg, NULL, 0, 0) )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
    }

	return (int)msg.wParam;
}


ATOM RegisterTheClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize         = sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)TheWindowProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP_ICON));
	wcex.hCursor		= LoadCursor(hInstance, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm        = NULL;

	return RegisterClassEx(&wcex);
}


BOOL CreateTheWindow(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;

	hWnd = CreateWindowEx(
		WS_DISABLED,
        szWindowClass,
        szTitle,
		0,
        CW_USEDEFAULT, CW_USEDEFAULT, 0, 0,
        NULL, NULL, hInstance, NULL
	);

    if (!hWnd) return FALSE;

    return TRUE;
}


BOOL AddTaskBarIcon(HINSTANCE hInstance, HWND hWnd, UINT uID, UINT icon, LPCSTR lpszTip)
{
    BOOL res;
    NOTIFYICONDATA nId;
	HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(icon));

	nId.cbSize = sizeof(NOTIFYICONDATA); 
    nId.hWnd = hWnd; 
    nId.uID = uID; 
    nId.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP; 
    nId.uCallbackMessage = NOTIFYICON_MESSAGE;
	nId.hIcon = hIcon;
	wsprintf(nId.szTip, "%s", lpszTip);

	res = Shell_NotifyIcon(NIM_ADD, &nId); 
 
    if (hIcon) DestroyIcon(hIcon);

    return res;
}


BOOL DeleteTaskBarIcon(HWND hWnd, UINT uID)
{ 
    BOOL res; 
    NOTIFYICONDATA nId; 
 
    nId.cbSize = sizeof(NOTIFYICONDATA); 
    nId.hWnd = hWnd; 
    nId.uID = uID; 
         
    res = Shell_NotifyIcon(NIM_DELETE, &nId); 
    return res; 
}


void ShowTrayMenu(HINSTANCE hInstance, HWND hWnd)
{
    HMENU hMenu, hTrayPopupMenu;
    POINT point;

	hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_APP_MENU));
    hTrayPopupMenu = GetSubMenu(hMenu, 0);

	// add ttmenu items
	for (int ii=0; ii<TT_MAX_SIZE; ii++)
	{
	    MENUITEMINFO menuItemInfo;

		if (strlen(ttelem[ii].alias) == 0) continue;

		if (strncmp(ttelem[ii].alias, TT_MENU_SEP, strlen(TT_MENU_SEP)) != 0)
		{
	        menuItemInfo.cbSize = sizeof(MENUITEMINFO);
	        menuItemInfo.fMask = MIIM_STRING | MIIM_ID;
            menuItemInfo.fType = MIIM_STRING;
		    menuItemInfo.wID = ID_TT_ELEM_BASE + ii;
	        menuItemInfo.cch = strlen(ttelem[ii].alias);
	        menuItemInfo.dwTypeData = TEXT(ttelem[ii].alias);
        } else {
	        menuItemInfo.cbSize = sizeof(MENUITEMINFO);
		    menuItemInfo.fMask = MIIM_TYPE;
		    menuItemInfo.fType = MFT_SEPARATOR;
		}
		InsertMenuItem(hTrayPopupMenu, ii, TRUE, &menuItemInfo);
	}

	GetCursorPos(&point);
    SetForegroundWindow(hWnd);
    TrackPopupMenuEx(hTrayPopupMenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, hWnd, NULL);
    PostMessage(hWnd, WM_USER, 0, 0);
	DestroyMenu(hMenu);
}


BOOL loadTTElementsEx(void)
{
    FILE *fp;
	int nline = 0, ii = 0, jj = 0;
	char line[MAX_LOADSTRING];
	int left = 1, empty = 1;

	if( (fp = fopen(TT_CONF_FILE, "r+" )) == NULL)
	    return FALSE;

	while (fgets(line, MAX_LOADSTRING, fp) != NULL && nline < TT_MAX_SIZE)
    {
	    left = 1; empty = 1;
	    for (ii = 0, jj = 0; line[ii] != '\0' && line[ii] != '\n'; ii++)
		{
		    empty = 0;
		    if (line[ii] == TT_CONF_SEP) { left = 0; ttelem[nline].alias[jj-1] = '\0'; ii++; jj = 0; }
		    if (left)  ttelem[nline].alias[jj++] = line[ii];
			else       ttelem[nline].path[jj++] = line[ii];
		}
		ttelem[nline].path[jj] = '\0';
		if (!empty) nline++;
	}

	fclose(fp);

    while (nline<TT_MAX_SIZE)
	{
	    ttelem[nline].alias[0] = '\0';
		ttelem[nline++].path[0] = '\0';
	}

    return TRUE;
}


// The Window Procedure
LRESULT CALLBACK TheWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	switch ( msg )
    {
        case WM_CREATE:
			AddTaskBarIcon(hInstance, hWnd, NOTIFYICON_ID, IDI_APP_ICON, szTrayToolTip);
			if (loadTTElementsEx() != TRUE)
			{
			    MessageBox(NULL, "Unable to open configuration file.", szTitle, MB_ICONSTOP | MB_OK);
				DestroyWindow(hWnd);	
			}
        break;

        case WM_CLOSE:
            DestroyWindow(hWnd);
        break;

		case WM_DESTROY:
		    DeleteTaskBarIcon(hWnd, NOTIFYICON_ID);
		    PostQuitMessage(0);
        break;

        case NOTIFYICON_MESSAGE:
			if ( LOWORD(wParam) == NOTIFYICON_ID )
			{
			    switch ( lParam )
				{
	                case WM_LBUTTONDOWN:
					case WM_RBUTTONDOWN:
	  	                flagButtonDown = 1;
		            break;

					case WM_LBUTTONUP:
	                case WM_RBUTTONUP:
		                if ( flagButtonDown == 1 )
						{
						    flagButtonDown = 0;
						    ShowTrayMenu(hInstance, hWnd);
						}
		        }
			}
		break;

        case WM_COMMAND:
		    switch ( LOWORD(wParam) )
			{
				case ID_CMD_CONFIGURE:
					_spawnlp(_P_WAIT , "notepad", TT_CONF_FILE, TT_CONF_FILE, NULL, NULL);
					if (loadTTElementsEx() != TRUE)
			        {
			            MessageBox(NULL, "Unable to open configuration file.", szTitle, MB_ICONSTOP | MB_OK);
				        DestroyWindow(hWnd);	
			        }
                break;

                case ID_CMD_EXIT:
					PostMessage(hWnd, WM_CLOSE, (WPARAM)NULL, (LPARAM)NULL);
                break;

				case ID_CMD_ABOUT:
					DialogBox(hInstance, MAKEINTRESOURCE(IDD_ABOUT), hWnd, AboutDlgProc);
                break;

				default:
					if ( LOWORD(wParam) >= ID_TT_ELEM_BASE && LOWORD(wParam) < ID_TT_ELEM_BASE + TT_MAX_SIZE )
				    	_spawnlp(_P_NOWAIT, "explorer", "/e", ttelem[LOWORD(wParam) - ID_TT_ELEM_BASE].path, NULL, NULL);
		    }
        break;

		default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
    }

	return 0;
}
