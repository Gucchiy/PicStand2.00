// TrayIconPicStand.h: CTrayIconPicStand クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRAYICONPICSTAND_H__4D738323_E3BB_43E0_8EDF_6504FD1FCA29__INCLUDED_)
#define AFX_TRAYICONPICSTAND_H__4D738323_E3BB_43E0_8EDF_6504FD1FCA29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TrayIcon.h"

class CTrayIconPicStand : public CTrayIcon  
{
public:
	CTrayIconPicStand( HWND hWnd, UINT uIconID, CString TipString, WPARAM wParam );
	virtual ~CTrayIconPicStand();

	virtual void OnMessage( LPARAM lParam);

};

#endif // !defined(AFX_TRAYICONPICSTAND_H__4D738323_E3BB_43E0_8EDF_6504FD1FCA29__INCLUDED_)
