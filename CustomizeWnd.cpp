// CustomizeWnd.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "picstand.h"
#include "CustomizeWnd.h"
#include "PicStandWnd.h"
#include "Global.h"
#include "PicStandWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomizeWnd ダイアログ


CCustomizeWnd::CCustomizeWnd(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomizeWnd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomizeWnd)
	m_uBlueValue = 0;
	m_uGreenValue = 0;
	m_uRedValue = 0;
	m_uWidthValue = 0;
	//}}AFX_DATA_INIT

	Create(CCustomizeWnd::IDD, pParent );
}


void CCustomizeWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomizeWnd)
	DDX_Control(pDX, IDC_SCROLLBAR_WIDTH, m_WidthScrollBar);
	DDX_Control(pDX, IDC_SCROLLBAR_BLUE, m_BlueScrollBar);
	DDX_Control(pDX, IDC_SCROLLBAR_GREEN, m_GreenScrollBar);
	DDX_Control(pDX, IDC_SCROLLBAR_RED, m_RedScrollBar);
	DDX_Text(pDX, IDC_EDIT_BLUE, m_uBlueValue);
	DDX_Text(pDX, IDC_EDIT_GREEN, m_uGreenValue);
	DDX_Text(pDX, IDC_EDIT_RED, m_uRedValue);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_uWidthValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomizeWnd, CDialog)
	//{{AFX_MSG_MAP(CCustomizeWnd)
	ON_WM_DESTROY()
	ON_WM_HSCROLL()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_DEFAULT, OnDefault)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomizeWnd メッセージ ハンドラ

void CCustomizeWnd::OnDestroy() 
{
	CDialog::OnDestroy();
	
	CPicStandWnd*	pParent = (CPicStandWnd*) GetParent();
	pParent->CustomizeWndDestroyInd();
}

void CCustomizeWnd::OnOK() 
{
	CDialog::OnOK();
	DestroyWindow();

}

void CCustomizeWnd::OnCancel() 
{
	CPicStandWnd*	pParent = (CPicStandWnd* )AfxGetMainWnd();

	pParent->SetColor( m_uRedTemp, m_uGreenTemp, m_uBlueTemp );
	CX_FRAME = m_uWidthTemp;
	pParent->AdjustWindowSizePos();
	pParent->InvalidateRect( NULL );
	SetFocus();

	CDialog::OnCancel();
	DestroyWindow();
}

void CCustomizeWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	UpdateData( TRUE );      //データの取得

	UINT	uNextPos;
	UINT*	puCurrentValue;

	if( pScrollBar == &m_RedScrollBar ){

		uNextPos = m_uRedValue;
		puCurrentValue = &m_uRedValue;

	}else if( pScrollBar == &m_GreenScrollBar ){

		uNextPos = m_uGreenValue;
		puCurrentValue = &m_uGreenValue;

	}else if( pScrollBar == &m_BlueScrollBar ){

		uNextPos = m_uBlueValue;
		puCurrentValue = &m_uBlueValue;
	
	}else{

		uNextPos = m_uWidthValue;
		puCurrentValue = &m_uWidthValue;
	}

	switch(nSBCode){
	case SB_LINELEFT:                    //左矢印ボタンクリック
		uNextPos--;                          //１減らす
		break;
	case SB_LINERIGHT:                   //右矢印ボタンクリック
		uNextPos++;                          //１増やす
		break;
	case SB_PAGELEFT:                    //左頁領域クリック
		uNextPos -= 10;                      //１０減らす
		break;
	case SB_PAGERIGHT:                   //右頁領域クリック
		uNextPos += 10;                      //１０増やす 
		break;
	case SB_THUMBPOSITION:               //つまみドラッグで目的地に達した
		uNextPos = nPos;                     //現在の位置に変更
		break;
	case SB_THUMBTRACK:                  //つまみドラッグ中
		uNextPos = nPos;                     //現在の位置に変更
		break;
	default:
		break;
	}

	int	nMaxPos;
	int	nMinPos;
	pScrollBar->GetScrollRange( &nMinPos, &nMaxPos );

	if( (int)uNextPos > nMaxPos ){

		uNextPos = nMaxPos;
	}
	if( (int)uNextPos < nMinPos ){

		uNextPos = nMinPos;
	}

	*puCurrentValue = uNextPos;
	UpdateData( FALSE );			//データを設定する
	pScrollBar->SetScrollPos( uNextPos );	//スクロールバー(スライダー)の位置を設定する

	CPicStandWnd*	pParent = (CPicStandWnd* )AfxGetMainWnd();

	if( puCurrentValue == &m_uWidthValue ){

		CX_FRAME = m_uWidthValue;
		pParent->AdjustWindowSizePos();

		if( nSBCode != SB_THUMBTRACK ) SetFocus();
	
	}else{

		pParent->SetColor( m_uRedValue, m_uGreenValue, m_uBlueValue );
	}

	pParent->InvalidateRect( NULL );

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

int CCustomizeWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	
	return 0;
}

BOOL CCustomizeWnd::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CPicStandWnd*	pParent = (CPicStandWnd* )AfxGetMainWnd();
	pParent->GetColor( m_uRedValue, m_uGreenValue, m_uBlueValue );

	m_uWidthValue = CX_FRAME;

	m_RedScrollBar.SetScrollRange( MIN_RGB, MAX_RGB );
	m_RedScrollBar.SetScrollPos( m_uRedValue );
	m_GreenScrollBar.SetScrollRange( MIN_RGB, MAX_RGB );
	m_GreenScrollBar.SetScrollPos( m_uGreenValue );
	m_BlueScrollBar.SetScrollRange( MIN_RGB, MAX_RGB );
	m_BlueScrollBar.SetScrollPos( m_uBlueValue );
	m_WidthScrollBar.SetScrollRange( MIN_WIDTH, MAX_WIDTH );
	m_WidthScrollBar.SetScrollPos( CX_FRAME );

	UpdateData( FALSE );

	m_uWidthTemp = m_uWidthValue;
	m_uRedTemp = m_uRedValue;
	m_uGreenTemp = m_uGreenValue;
	m_uBlueTemp = m_uBlueValue;
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CCustomizeWnd::OnDefault() 
{
	::SendMessage( AfxGetMainWnd()->m_hWnd, g_uCustomizeWndMessage, CWM_SET_DEFAULT, NULL );

	CPicStandWnd*	pParent = (CPicStandWnd* )AfxGetMainWnd();
	pParent->GetColor( m_uRedValue, m_uGreenValue, m_uBlueValue );

	m_uWidthValue = CX_FRAME;

	m_RedScrollBar.SetScrollRange( MIN_RGB, MAX_RGB );
	m_RedScrollBar.SetScrollPos( m_uRedValue );
	m_GreenScrollBar.SetScrollRange( MIN_RGB, MAX_RGB );
	m_GreenScrollBar.SetScrollPos( m_uGreenValue );
	m_BlueScrollBar.SetScrollRange( MIN_RGB, MAX_RGB );
	m_BlueScrollBar.SetScrollPos( m_uBlueValue );
	m_WidthScrollBar.SetScrollRange( MIN_WIDTH, MAX_WIDTH );
	m_WidthScrollBar.SetScrollPos( CX_FRAME );

	UpdateData( FALSE );
	SetFocus();
}

void CCustomizeWnd::OnPaint() 
{
	CPaintDC dc(this); // 描画用のデバイス コンテキスト
}
