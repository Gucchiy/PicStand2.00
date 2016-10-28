// TrayIconPicStand.cpp: CTrayIconPicStand �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "picstand.h"
#include "TrayIconPicStand.h"
#include "Global.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CTrayIconPicStand::CTrayIconPicStand( HWND hWnd )
:CTrayIcon( hWnd, IDI_DEFAULTICON, APP_NAME, ITMES_TASKTRAY )
{

}

CTrayIconPicStand::~CTrayIconPicStand()
{

}

void CTrayIconPicStand::OnMessage( LPARAM lParam )
{
	switch( lParam ){
	case WM_LBUTTONDOWN:

		SetWindowPos( &CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE );
		SetZOrder( m_ZOrder );
		break;

	case WM_LBUTTONDBLCLK:

		if( m_WndStyle == WNDSTYLE_BAR ){

			SetNormalStyle();
		}
		break;

	case WM_RBUTTONDOWN:

		{
			// ���j���[�������Ȃ��Ȃ錏�� Workaround
			SetForegroundWindow();

			CPoint	MousePoint;
			::GetCursorPos( &MousePoint );

			ActivateMenu( MousePoint.x, MousePoint.y );

		}
		break;
	}
	break;

}
