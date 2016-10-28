// PicStand.h : PICSTAND アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_PICSTAND_H__F3F485E9_8836_4AC0_90AD_CAC345ABBF92__INCLUDED_)
#define AFX_PICSTAND_H__F3F485E9_8836_4AC0_90AD_CAC345ABBF92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CPicStandApp:
// このクラスの動作の定義に関しては PicStand.cpp ファイルを参照してください。
//

#define	MAPPED_FILE_NAME	_T( "PicStandMappedFile" )

typedef struct {
	HWND	hWnd;
}SharedData;

class CPicStandApp : public CWinApp
{
protected:
	BOOL		m_bSharedFileExist;
	SharedData*	m_pSharedData;
	HANDLE		m_hMap;

public:
	void SetHandleToSharedData( HWND hWnd );
	CPicStandApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CPicStandApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CPicStandApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_PICSTAND_H__F3F485E9_8836_4AC0_90AD_CAC345ABBF92__INCLUDED_)
