// TrayIcon.cpp: CTrayIcon クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TrayIcon.h"
#include "IdeaTech.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CTrayIcon::CTrayIcon( HWND hWnd, UINT uIconID, CString TipString, WPARAM wParam )
{
	m_NotifyIconData.cbSize = sizeof( NOTIFYICONDATA );
	m_NotifyIconData.hWnd = hWnd;
	m_NotifyIconData.hIcon = (HICON)::LoadImage( AfxGetApp()->m_hInstance, MAKEINTRESOURCE( uIconID ), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR );
	strcpy( m_NotifyIconData.szTip, TipString );
	m_NotifyIconData.uID = wParam;
	m_NotifyIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_NotifyIconData.uCallbackMessage = ITech_GetIdeaTechMessage();

	Shell_NotifyIcon( NIM_ADD, &m_NotifyIconData );

}

CTrayIcon::~CTrayIcon()
{
	Shell_NotifyIcon( NIM_DELETE, &m_NotifyIconData );
}

void CTrayIcon::OnMessage( LPARAM lParam)
{
	// lParam にはマウスイベントが入る
}

