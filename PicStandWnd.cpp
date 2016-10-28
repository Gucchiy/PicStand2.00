// CPicStandWnd.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "PicStand.h"
#include "PicStandWnd.h"
#include "ExpandShortcut.h"
#include "Global.h"
#include "IdeaTech.h"
#include "PictureFileDlg.h"
#include "VersionInfoDlg.h"

#include <sys/stat.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPicStandWnd

CPicStandWnd::CPicStandWnd()
{
	m_pPicMenuButton = NULL;
	m_pStatusWnd = NULL;
	m_pStayButton = NULL;
	m_bStay = FALSE;
	m_ZOrder = ZORDER_NORMAL;
	m_pMenu = NULL;
	m_bFixSize = FALSE;
	m_DragState = DRGST_NORMAL;
	m_hPrevCursor = NULL;
	m_pNextButton = NULL;
	m_pBackButton = NULL;
	m_pTrayIcon = NULL;
	m_pCustomizeWnd = NULL;
}

CPicStandWnd::~CPicStandWnd()
{
}

UINT	g_uIdeaTechMessage = ::RegisterWindowMessage( ITECH_MES_STRING );
UINT	g_uCustomizeWndMessage = ::RegisterWindowMessage( CUSTOMIZEWND_MES_STRING );

BEGIN_MESSAGE_MAP(CPicStandWnd, CWnd)
	//{{AFX_MSG_MAP(CPicStandWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_DROPFILES()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOVE()
	ON_COMMAND(IDM_CLOSE, OnMenuClose)
	ON_COMMAND(IDM_DIV2, OnDiv2)
	ON_COMMAND(IDM_MUL1, OnMul1)
	ON_COMMAND(IDM_MUL2, OnMul2)
	ON_COMMAND(IDM_TOPMOST, OnTopmost)
	ON_COMMAND(IDM_BOTTOMMOST, OnBottommost)
	ON_COMMAND(IDM_STAY, OnStay)
	ON_COMMAND(IDM_BARSTYLE, OnBarstyle)
	ON_COMMAND(IDM_HELP, OnHelp)
	ON_COMMAND(IDM_SUPPORT, OnSupport)
	ON_WM_ENDSESSION()
	ON_COMMAND(IDM_REG_STARTUP, OnRegStartup)
	ON_COMMAND(IDM_VERSIONDLG, OnVersiondlg)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(IDM_FIXSIZE, OnFixsize)
	ON_COMMAND(IDM_FIXSIZE2, OnFixsize2)
	ON_COMMAND(IDM_CASH_DELETE, OnCashDelete)
	ON_COMMAND(IDM_CASH_NEXT, OnCashNext)
	ON_COMMAND(IDM_CASH_PREV, OnCashPrev)
	ON_COMMAND(IDM_CUSTOMIZEWND, OnCustomizewnd)
	//}}AFX_MSG_MAP

	ON_REGISTERED_MESSAGE( g_uIdeaTechMessage, OnIdeaTechMessage )
	ON_REGISTERED_MESSAGE( g_uCustomizeWndMessage, OnCustomizeWndMessage )

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPicStandWnd メッセージ ハンドラ
int CPicStandWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 額縁幅の初期化
	CPicStandApp*	pApp = (CPicStandApp*) AfxGetApp();
	CX_FRAME = pApp->GetProfileInt( REG_SECTION_TOP, REG_KEY_EDGE, CX_FRAME );

	CString StartupAllPath;
	SHGetSpecialFolderPath(NULL, StartupAllPath.GetBuffer( _MAX_PATH + 1 ), CSIDL_COMMON_STARTUP, FALSE);
	StartupAllPath.ReleaseBuffer();
	StartupAllPath = StartupAllPath + _T( "\\" ) + STARTUP_SHORTCUT;

	CFile		File;
	CFileStatus	FileStatus;

	if( File.GetStatus( StartupAllPath, FileStatus ) ){

		if( !StartupShorcutExist() ){

			CreateStartupShortcut();
		}
		// All Users 向けは削除
		File.Remove( StartupAllPath );

	}
	
	pApp->SetHandleToSharedData( m_hWnd );

	// Picture の初期化
	m_pPicture = new CPicture;
	if( !m_pPicture->Set( pApp->GetProfileString( REG_SECTION_TOP, REG_KEY_FILENAME, "" ) ) ){

		m_pPicture->Set();
	}

	// 倍率の初期化
	CString	WideString;
	WideString = pApp->GetProfileString( REG_SECTION_TOP, REG_KEY_WIDE, "1.0" );
	m_pPicture->SetWide( atof( WideString ) );

	// 表示座標の初期化
	InitWindowParams();

	enumZOrder	ZOrder = (enumZOrder) pApp->GetProfileInt( REG_SECTION_TOP, REG_KEY_ZORDER, ZORDER_NORMAL );
	SetZOrder( ZOrder );

	// 写真初期サイズの設定
	m_bFixSize = (BOOL) pApp->GetProfileInt( REG_SECTION_TOP, REG_KEY_FIXSIZE, TRUE );

	CRect	WndRect;
	GetWindowRect( &WndRect );
	
	m_pPicMenuButton = new CCustomButton( IDB_MENU00, IDB_MENU01, IDB_MENU03 );
	m_pPicMenuButton->Create( this, LX_MENUBTN( WndRect.Width() ), LY_MENUBTN( WndRect.Height() ), ITMES_MENUBTN );

	m_pStatusWnd = new CStatusWnd( IDB_STATUS00, IDB_STATUS01 );
	m_pStatusWnd->Create( this, LX_STATUSWND( WndRect.Width() ), LY_STATUSWND( WndRect.Height() ), ITMES_STATUSWND );
	m_pStatusWnd->SetDispString( m_pPicture->GetFileNameString() );

	m_pStayButton = new CStayButton( IDB_STAYDOWN00, IDB_STAYDOWN01, IDB_STAYUP00, IDB_STAYUP01 );
	m_pStayButton->Create( this, LX_STAYBTN( WndRect.Width() ), LY_STAYBTN( WndRect.Height() ), ITMES_STAY );
	m_pStayButton->SetUpState( !m_bStay );

	m_pMenu = new CMenu;
	m_pMenu->LoadMenu( IDM_CONTEXT_MENU );

	m_pTrayIcon = new CTrayIcon( m_hWnd, IDI_DEFAULTICON, APP_NAME, ITMES_TASKTRAY );

	m_pNextButton = new CCustomButton( IDB_NEXT00, IDB_NEXT01, IDB_NEXT02 );
	m_pNextButton->Create( this, LX_NEXTBTN, LY_NEXTBTN, ITMES_NEXTBTN );

	m_pBackButton = new CCustomButton( IDB_BACK00, IDB_BACK01, IDB_BACK02 );
	m_pBackButton->Create( this, LX_BACKBTN, LY_BACKBTN, ITMES_BACKBTN );

	AdjustWindowSizePos();

	CreateCashList();

	m_ColorR = pApp->GetProfileInt( REG_SECTION_TOP, REG_KEY_COLOR_R, RGB_BACK_R );
	m_ColorG = pApp->GetProfileInt( REG_SECTION_TOP, REG_KEY_COLOR_G, RGB_BACK_G );
	m_ColorB = pApp->GetProfileInt( REG_SECTION_TOP, REG_KEY_COLOR_B, RGB_BACK_B );

	SetColors();

	return 0;
}

void CPicStandWnd::OnDestroy() 
{
	CWnd::OnDestroy();

	delete m_pTrayIcon;

	CRect	MyRect;
	GetWindowRect( MyRect );

	CWinApp*	pApp = AfxGetApp();
	pApp->WriteProfileInt( REG_SECTION_TOP, REG_KEY_LX, MyRect.left );
	pApp->WriteProfileInt( REG_SECTION_TOP, REG_KEY_LY, MyRect.top );
	pApp->WriteProfileString( REG_SECTION_TOP, REG_KEY_FILENAME, m_pPicture->GetFilePathString() );

	CString	WideString;
	WideString.Format( "%f", m_pPicture->GetWide() );
	pApp->WriteProfileString( REG_SECTION_TOP, REG_KEY_WIDE, WideString );

	pApp->WriteProfileInt( REG_SECTION_TOP, REG_KEY_ZORDER, m_ZOrder );

	pApp->WriteProfileInt( REG_SECTION_TOP, REG_KEY_STAY, m_bStay );

	pApp->WriteProfileInt( REG_SECTION_TOP, REG_KEY_FIXSIZE, m_bFixSize );

	pApp->WriteProfileInt( REG_SECTION_TOP, REG_KEY_COLOR_R, m_ColorR );
	pApp->WriteProfileInt( REG_SECTION_TOP, REG_KEY_COLOR_G, m_ColorG );
	pApp->WriteProfileInt( REG_SECTION_TOP, REG_KEY_COLOR_B, m_ColorB );

	pApp->WriteProfileInt( REG_SECTION_TOP, REG_KEY_EDGE, CX_FRAME );

	delete m_pPicture;

	m_pMenu->DestroyMenu();
	delete m_pMenu;

	int nSize = m_CashFilePathArray.GetSize();

	if( nSize ){

		for( int nPos = 0; nPos < nSize; nPos++ ){

			delete m_CashFilePathArray[ nPos ];
		}
		m_CashFilePathArray.RemoveAll();
	}
}

void CPicStandWnd::PostNcDestroy() 
{
	CWnd::PostNcDestroy();

	delete this;
}

BOOL CPicStandWnd::Create()
{
	
	return CreateEx(
		WS_EX_ACCEPTFILES | WS_EX_CONTROLPARENT | WS_EX_TOOLWINDOW,
		AfxRegisterWndClass( CS_DBLCLKS, ::LoadCursor(NULL, IDC_ARROW), NULL, AfxGetApp()->LoadIcon( IDI_DEFAULTICON ) ),
		_T( "CPicStandWnd" ),
		WS_VISIBLE | WS_POPUP | WS_CLIPCHILDREN, CRect( 100, 100, 200, 200 ), NULL, 0, NULL );
}


void CPicStandWnd::OnPaint() 
{
	CPaintDC dc(this); // 描画用のデバイス コンテキスト

	CRect	WndRect;
	GetWindowRect( &WndRect );

	CDC		MemDC;
	CBitmap	MemBitmap;

	MemDC.CreateCompatibleDC( &dc );
	MemBitmap.CreateCompatibleBitmap( &dc, WndRect.Width(), WndRect.Height() );

	CBitmap*	pOldBitmap = (CBitmap*)MemDC.SelectObject( &MemBitmap );
	
	// Picture の大きさ
	int	nPicCX = m_pPicture->GetWidth();
	int	nPicCY = m_pPicture->GetHeight();
	
	// Window の終端位置
	int	nPosEX = WndRect.Width() - 1;
	int	nPosEY = WndRect.Height() - 1;


	MemDC.FillSolidRect( CRect( 0, 0, nPosEX, nPosEY ), m_Color );
	CPen	LightPen( PS_SOLID, 1, m_LightColor );
	CPen	ShadowPen( PS_SOLID, 1, m_DarkColor );

	CPen*	pOldPen = ( CPen* )MemDC.SelectObject( &LightPen );

	int	nCount;

	for( nCount = 0; nCount < 3; nCount++ ){

		MemDC.MoveTo( nCount, nCount );
		MemDC.LineTo( nCount, nPosEY - nCount );
	}

	for( nCount = 0; nCount < 3; nCount++ ){

		MemDC.MoveTo( nCount, nCount );
		MemDC.LineTo( nPosEX + 1, nCount );
	}

	for( nCount = 0; nCount < 3; nCount++ ){

		MemDC.MoveTo( LEX_PICTURE( nPicCX ) + 1 + nCount, LY_PICTURE - nCount );
		MemDC.LineTo( LEX_PICTURE( nPicCX ) + 1 + nCount, LEY_PICTURE( nPicCY ) + 1 + nCount );
	}

	for( nCount = 0; nCount < 3; nCount++ ){

		MemDC.MoveTo( LX_PICTURE - nCount, LEY_PICTURE( nPicCY ) + 1 + nCount );
		MemDC.LineTo( LEX_PICTURE( nPicCX ) + 4, LEY_PICTURE( nPicCY ) + 1 + nCount );
	}

	if( m_WndStyle == WNDSTYLE_NORMAL ){

		CPen	Light2Pen( PS_SOLID, 1, m_Light2Color );

		MemDC.SelectObject( &Light2Pen );

		for( nCount = 1; nCount < 4; nCount++ ){
			MemDC.MoveTo( nPosEX, nPosEY - 32 + nCount * 7);
			MemDC.LineTo( nPosEX - 32 + nCount * 7, nPosEY );
		}
	}

	MemDC.SelectObject( &ShadowPen );

	for( nCount = 0; nCount < 3; nCount++ ){

		MemDC.MoveTo( nPosEX - nCount, nCount );
		MemDC.LineTo( nPosEX - nCount, nPosEY - nCount + 1 );

	}

	for( nCount = 0; nCount < 3; nCount++ ){

		MemDC.MoveTo( nCount, nPosEY - nCount );
		MemDC.LineTo( nPosEX + 3, nPosEY - nCount );

	}

	for( nCount = 0; nCount < 3; nCount++ ){

		MemDC.MoveTo( nCount, LY_PICTURE - 1 - nCount );
		MemDC.LineTo( nPosEX + 1, LY_PICTURE - 1 - nCount );

	}

	for( nCount = 0; nCount < 3; nCount++ ){

		MemDC.MoveTo( LX_PICTURE - 1 - nCount, LY_PICTURE );
		MemDC.LineTo( LX_PICTURE - 1 - nCount, LEY_PICTURE( nPicCY ) + 1 + nCount );
	}

	if( m_WndStyle == WNDSTYLE_NORMAL ){

		for( nCount = 1; nCount < 4; nCount++ ){
			MemDC.MoveTo( nPosEX, nPosEY - 32 + 3 + nCount * 7);
			MemDC.LineTo( nPosEX - 32 + 3 + nCount * 7, nPosEY );
		}
	}

	MemDC.SelectObject( pOldPen );

	m_pPicture->DrawTo( MemDC.GetSafeHdc(), LX_PICTURE, LY_PICTURE );
	dc.BitBlt( 0, 0, WndRect.Width(), WndRect.Height(), &MemDC, 0, 0, SRCCOPY );

	MemDC.SelectObject( pOldBitmap );
}

void CPicStandWnd::OnDropFiles(HDROP hDropInfo) 
{
	// Get the number of pathnames that have been dropped
	WORD wNumFilesDropped = DragQueryFile(hDropInfo, -1, NULL, 0);

	CString firstFile="";
	CString*	FileNameArray = new CString[ wNumFilesDropped ];

	// get all file names. but we'll only need the first one.
	for (WORD x = 0 ; x < wNumFilesDropped; x++) {

		// Get the number of bytes required by the file's full pathname
		WORD wPathnameSize = DragQueryFile(hDropInfo, x, NULL, 0);

		// Allocate memory to contain full pathname & zero byte
		char * npszFile = (char *) LocalAlloc(LPTR, wPathnameSize += 1);

		// If not enough memory, skip this one
		if (npszFile == NULL) continue;

		// Copy the pathname into the buffer
		DragQueryFile(hDropInfo, x, npszFile, wPathnameSize);

		FileNameArray[ x ] = npszFile;

		// clean up
		LocalFree(npszFile);
	}

	// Free the memory block containing the dropped-file information
	DragFinish(hDropInfo);

	// if this was a shortcut, we need to expand it to the target path
//	CString expandedFile = ExpandShortcut(firstFile);

	// if that worked, we should have a real file name
//	if (expandedFile!="") 
//		firstFile=expandedFile;

	

	for( x = 0; x < wNumFilesDropped; x++ ){
	
		struct _stat buf;
		// get some info about that file
		int result = _stat( FileNameArray[x], &buf );
		if( result == 0 ) {

			if ((buf.st_mode & _S_IFREG) == _S_IFREG) {

				m_pPicture->Set( FileNameArray[x] );
				m_pStatusWnd->SetDispString( m_pPicture->GetFileNameString() );
				SetPictureWide( TRUE );
				AdjustWindowSizePos();
				InvalidateRect( NULL );
			}
		}
	}
	CreateCashList();

	delete []FileNameArray;

	CWnd::OnDropFiles(hDropInfo);
}

void CPicStandWnd::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	if( point.y <= CY_BARSTAND ){

		if( m_WndStyle == WNDSTYLE_NORMAL ){

			SetBarStyle();

		}else{

			SetNormalStyle();
		}

	}
	
	CWnd::OnLButtonDblClk(nFlags, point);
}

void CPicStandWnd::SetPosition( int nPosX, int nPosY )
{
	CRect	WndRect;
	GetWindowRect( &WndRect );

	CRect	DesktopRect;
	::SystemParametersInfo( SPI_GETWORKAREA, 0, &DesktopRect, NULL );

	if( abs( nPosY - DesktopRect.top ) < 10 ){

		nPosY = DesktopRect.top;
	}

	if( abs( nPosY + WndRect.Height() - DesktopRect.bottom ) < 10 ){

		nPosY = DesktopRect.bottom - WndRect.Height();
	}

	if( abs( nPosX - DesktopRect.left ) < 10 ){

		nPosX = DesktopRect.left;
	}

	if( abs( nPosX + WndRect.Width() - DesktopRect.Width() ) < 10 ){

		nPosX = DesktopRect.right - WndRect.Width();
	}

	SetWindowPos( NULL,
		nPosX, nPosY,
		0, 0, SWP_NOZORDER | SWP_NOSIZE );

}

void CPicStandWnd::InitWindowParams()
{
	CWinApp*	pApp = AfxGetApp();
	CRect	DesktopRect;
	::SystemParametersInfo( SPI_GETWORKAREA, 0, &DesktopRect, NULL );

	int	nLX = pApp->GetProfileInt( REG_SECTION_TOP, REG_KEY_LX, 0 );
	int	nLY = pApp->GetProfileInt( REG_SECTION_TOP, REG_KEY_LY, 0 );
	int	nCX = CX_PICSTAND( m_pPicture->GetWidth() );
	int	nCY = CY_PICSTAND( m_pPicture->GetHeight() );

	SetWindowPos( &CWnd::wndTop, nLX, nLY, nCX, nCY, 0 );
	m_WndStyle = WNDSTYLE_NORMAL;
	
	m_bStay = pApp->GetProfileInt( REG_SECTION_TOP, REG_KEY_STAY, FALSE );
}

void CPicStandWnd::SetBarStyle()
{
	CRect	WndRect;
	GetWindowRect( &WndRect );
	CRect	DesktopRect;
	::SystemParametersInfo( SPI_GETWORKAREA, 0, &DesktopRect, NULL );

	int	nCY = CY_BARSTAND;

	// 下に張り付いていた場合の処理
	if( WndRect.top > DesktopRect.top + 5 ){
		if( WndRect.bottom == DesktopRect.bottom ){

			WndRect.top = DesktopRect.bottom - nCY;

		}
	}

	SetWindowPos( NULL, WndRect.left, WndRect.top, WndRect.Width(), nCY, SWP_NOZORDER );
	m_WndStyle = WNDSTYLE_BAR;
}

void CPicStandWnd::SetNormalStyle()
{
	CRect	WndRect;
	GetWindowRect( &WndRect );
	CRect	DesktopRect;
	::SystemParametersInfo( SPI_GETWORKAREA, 0, &DesktopRect, NULL );

	int	nCY = CY_PICSTAND( m_pPicture->GetHeight() );
	if( nCY < MCY_PICSTAND ){ nCY = MCY_PICSTAND; }

	// 下に張り付いていた場合の処理
	if( WndRect.bottom == DesktopRect.bottom ){

		WndRect.top = DesktopRect.bottom - nCY;

	}

	SetWindowPos( NULL, WndRect.left, WndRect.top, WndRect.Width(), nCY, SWP_NOZORDER );
	m_WndStyle = WNDSTYLE_NORMAL;

}

void CPicStandWnd::AdjustWindowSizePos()
{
	CRect	WndRect;
	GetWindowRect( &WndRect );
	CRect	DesktopRect;
	::SystemParametersInfo( SPI_GETWORKAREA, 0, &DesktopRect, NULL );

	// デスクトップからはみ出さないサイズを取得
	GetPossibleWide();

	int nCX = CX_PICSTAND( m_pPicture->GetWidth() );
	int nCY = CY_PICSTAND( m_pPicture->GetHeight() );

	if( nCX < MCX_PICSTAND ){ nCX = MCX_PICSTAND; }
	if( nCY < MCY_PICSTAND ){ nCY = MCY_PICSTAND; }

	SetWindowPos( NULL, WndRect.left, WndRect.top, nCX, nCY, SWP_NOZORDER );
	m_pStatusWnd->SetWindowPos( NULL, LX_STATUSWND( nCX ), LY_STATUSWND( nCY ), 0, 0, SWP_NOZORDER | SWP_NOSIZE );
	
	m_pPicMenuButton->SetWindowPos( NULL, LX_MENUBTN( nCX ), LY_MENUBTN( nCY ), 0, 0, SWP_NOZORDER | SWP_NOSIZE );
	m_pBackButton->SetWindowPos( NULL, LX_BACKBTN, LY_BACKBTN, 0, 0, SWP_NOZORDER | SWP_NOSIZE );
	m_pNextButton->SetWindowPos( NULL, LX_NEXTBTN, LY_NEXTBTN, 0, 0, SWP_NOZORDER | SWP_NOSIZE );
	m_pStayButton->SetWindowPos( NULL, LX_STAYBTN( nCX ), LY_STAYBTN( nCY ), 0, 0, SWP_NOZORDER | SWP_NOSIZE );

	// デスクトップからはみ出して表示している場合は修正
	GetWindowRect( &WndRect );
	int	nLX = WndRect.left;
	int	nLY = WndRect.top;

	if( nLX < DesktopRect.left ){ nLX = DesktopRect.left; }
	if( WndRect.right > DesktopRect.right ){ nLX = DesktopRect.right - WndRect.Width(); }
	if( nLY < DesktopRect.top ){ nLY = DesktopRect.top; }
	if( WndRect.bottom > DesktopRect.bottom ){ nLY = DesktopRect.bottom - WndRect.Height(); }

	SetPosition( nLX, nLY );

	// WNDSTYLE は通常サイズ
	m_WndStyle = WNDSTYLE_NORMAL;
}

void CPicStandWnd::AdjustWindowFromWnd()
{
	CRect	WndRect;
	GetWindowRect( &WndRect );

	double	dlXWide = (double)( WndRect.Width() - CX_FRAME * 2 ) / (double)m_pPicture->GetBitmapWidth();
	double	dlYWide = (double)( WndRect.Height() - CY_FRAME * 2 ) / (double)m_pPicture->GetBitmapHeight();

	m_pPicture->SetWide( ( dlXWide < dlYWide ) ? dlXWide : dlYWide );

	GetPossibleWide();

	int nCX = WndRect.Width();
	int nCY = WndRect.Height();
	m_pStatusWnd->SetWindowPos( NULL, LX_STATUSWND( nCX ), LY_STATUSWND( nCY ), 0, 0, SWP_NOZORDER | SWP_NOSIZE );

	m_pPicMenuButton->SetWindowPos( NULL, LX_MENUBTN( nCX ), LY_MENUBTN( nCY ), 0, 0, SWP_NOZORDER | SWP_NOSIZE );
	m_pBackButton->SetWindowPos( NULL, LX_BACKBTN, LY_BACKBTN, 0, 0, SWP_NOZORDER | SWP_NOSIZE );
	m_pNextButton->SetWindowPos( NULL, LX_NEXTBTN, LY_NEXTBTN, 0, 0, SWP_NOZORDER | SWP_NOSIZE );
	m_pStayButton->SetWindowPos( NULL, LX_STAYBTN( nCX ), LY_STAYBTN( nCY ), 0, 0, SWP_NOZORDER | SWP_NOSIZE );
}

void CPicStandWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect	WndRect;
	GetWindowRect( &WndRect );

	if( ( point.x > LX_DRAG( WndRect.Width() ) ) &&
		( point.y > LY_DRAG( WndRect.Height() ) ) ){

		if( m_WndStyle == WNDSTYLE_NORMAL ){

			m_DragState = DRGST_SIZING;

			// マウスイベントをキャプチャー
			if( GetCapture() == this ){
				ReleaseCapture();
			}
			SetCapture();

			m_hPrevCursor = GetCursor();
			SetCursor( LoadCursor( NULL, IDC_SIZENWSE ) );
		}
	
	}else{
	
		if( !m_bStay ){

			// マウスによる移動をサポート

			m_DragState = DRGST_DRAGGING;

			// マウスイベントをキャプチャー
			if( GetCapture() == this ){
				ReleaseCapture();
			}
			SetCapture();

			// 現在の Window スクリーン座標を保存
			GetWindowRect( &m_MoveStartWndRect );

			// 現在のマウス位置座標をスクリーン座標系で保存
			m_MoveStartMousePoint = point;
			ClientToScreen( &m_MoveStartMousePoint );
		}
	}
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CPicStandWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// マウスによる移動が終了
	if( GetCapture() == this ){

		ReleaseCapture();
		if( m_hPrevCursor ){

			SetCursor( m_hPrevCursor );
			m_hPrevCursor = NULL;
		}
		switch( m_DragState ){
		case DRGST_SIZING:

			AdjustWindowSizePos();
			// 以下は関数化しましょう…
			m_pStayButton->InvalidateRect( NULL );
			m_pNextButton->InvalidateRect( NULL );
			m_pBackButton->InvalidateRect( NULL );
			m_pPicMenuButton->InvalidateRect( NULL );
			InvalidateRect( NULL );

			break;
		}
		m_DragState = DRGST_NORMAL;
	}
	
	CWnd::OnLButtonUp(nFlags, point);
}

void CPicStandWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	switch( m_DragState ){
	case DRGST_DRAGGING:

		if( m_bStay ){

			if( GetCapture() == this ){

				ReleaseCapture();
			}

		}else{

			// マウスによる移動のサポート
			// キャプチャー状態 を念のためチェック
			if( GetCapture() == this ){

				// 保存されたマウス座標からの距離を算出
				CPoint	DeltaPoint = point;
				ClientToScreen( &DeltaPoint );
				DeltaPoint -= m_MoveStartMousePoint;

				// 保存されたWindow座標に距離を加算して移動
				SetPosition( m_MoveStartWndRect.left + DeltaPoint.x,
							m_MoveStartWndRect.top + DeltaPoint.y );

				// 念のため、Redraw
				InvalidateRect( NULL );
			}
		}
		break;

	case DRGST_SIZING:

		if( GetCapture() == this ){

			CPoint	CurPos = point;
			BOOL	bCurPosChange = FALSE;

			if( CurPos.x < MCX_PICSTAND ){

				CurPos.x = MCX_PICSTAND;
				bCurPosChange = TRUE;
			}

			if( CurPos.y < MCY_PICSTAND ){

				CurPos.y = MCY_PICSTAND;
				bCurPosChange = TRUE;
			}

			SetWindowPos( NULL, 0, 0, CurPos.x, CurPos.y, SWP_NOMOVE|SWP_NOZORDER );
			AdjustWindowFromWnd();
			InvalidateRect( NULL );

			if( bCurPosChange ){
				ClientToScreen( &CurPos );
				SetCursorPos( CurPos.x, CurPos.y );
			}
		}
	}
	
	CWnd::OnMouseMove(nFlags, point);
}

void CPicStandWnd::OnMove(int x, int y) 
{
	CWnd::OnMove(x, y);
}

LRESULT CPicStandWnd::OnIdeaTechMessage( WPARAM wParam, LPARAM lParam )
{
	switch( wParam ){
	case ITMES_MENUBTN:
		{
			CRect	WndRect;
			m_pPicMenuButton->GetWindowRect( &WndRect );

			ActivateMenu( WndRect.right, WndRect.bottom + 1 );
		}			

		break;

	case ITMES_STATUSWND:
		{

			CPictureFileDlg	PictureFileDlg( m_pPicture->GetFilePathString(), this );

			if( PictureFileDlg.DoModal() == IDOK ){

				m_pPicture->Set( PictureFileDlg.GetPathName() );
				m_pStatusWnd->SetDispString( m_pPicture->GetFileNameString() );
				SetPictureWide( TRUE );
				AdjustWindowSizePos();
				InvalidateRect( NULL );

			}
			CreateCashList();
			CheckCurrentPicture();
		}

		break;

	case ITMES_STAY:
		m_bStay = lParam;
		InvalidateRect( NULL );
		break;

	case ITMES_TASKTRAY:

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
				// メニューが消えなくなる件の Workaround
				SetForegroundWindow();

				CPoint	MousePoint;
				::GetCursorPos( &MousePoint );

				ActivateMenu( MousePoint.x, MousePoint.y );

			}
			break;
		}
		m_pTrayIcon->OnMessage( lParam );
		break;

	case ITMES_BACKBTN:
		{
			if( m_CashFilePathArray.GetSize() <= 1 ){ break; }

			for( int nPos = 0; nPos < m_CashFilePathArray.GetSize(); nPos++ ){

				CString	Test = m_pPicture->GetFilePathString();

				if( * (m_CashFilePathArray[nPos]) == m_pPicture->GetFilePathString() ){

					break;
				}
			}

			nPos--;
			if( nPos < 0 ){

				nPos = m_CashFilePathArray.GetSize() - 1;
			}

			m_pPicture->Set( * (m_CashFilePathArray[nPos] ) );
			m_pStatusWnd->SetDispString( m_pPicture->GetFileNameString() );
			SetPictureWide( TRUE );
			AdjustWindowSizePos();
			// RedrawWindow();
			InvalidateRect( NULL );
		}
		break;

	case ITMES_NEXTBTN:
		{
			if( m_CashFilePathArray.GetSize() <= 1 ){ break; }

			for( int nPos = 0; nPos < m_CashFilePathArray.GetSize(); nPos++ ){

				if( * (m_CashFilePathArray[nPos]) == m_pPicture->GetFilePathString() ){

					break;
				}
			}

			nPos++;
			if( nPos >= m_CashFilePathArray.GetSize() ){

				nPos = 0;
			}
			m_pPicture->Set( * (m_CashFilePathArray[nPos] ) );
			m_pStatusWnd->SetDispString( m_pPicture->GetFileNameString() );
			SetPictureWide( TRUE );
			AdjustWindowSizePos();
			InvalidateRect( NULL );
		}

		break;

	}

	return -1;
}

void CPicStandWnd::OnMenuClose() 
{
	PostMessage( WM_CLOSE );
}

void CPicStandWnd::OnDiv2() 
{
	m_pPicture->SetWide( 1.0 / 2.0 );
	AdjustWindowSizePos();
	RedrawWindow();
}

void CPicStandWnd::OnMul1() 
{
	m_pPicture->SetWide( 1.0 );
	AdjustWindowSizePos();
	RedrawWindow();
}

void CPicStandWnd::OnMul2() 
{
	m_pPicture->SetWide( 2.0 );
	AdjustWindowSizePos();
	RedrawWindow();
}

BOOL CPicStandWnd::GetPossibleWide()
{
	BOOL	bRetVal = FALSE;

	CRect	DesktopRect;
	::SystemParametersInfo( SPI_GETWORKAREA, 0, &DesktopRect, NULL );
	
	int	nCX = CX_PICSTAND( m_pPicture->GetWidth() );
	int	nCY = CY_PICSTAND( m_pPicture->GetHeight() );

	double	dlWide = m_pPicture->GetWide();

	if( nCX > DesktopRect.Width() ){

		nCX = DesktopRect.Width() - CX_FRAME * 2;
		dlWide = (double) nCX / (double) m_pPicture->GetBitmapWidth(); 
		bRetVal = TRUE;

	}

	if( nCY > DesktopRect.Height() ){

		nCY = DesktopRect.Height() - CY_FRAME * 2;
		double	dlCYWide;
		dlCYWide = (double) nCY / (double) m_pPicture->GetBitmapHeight(); 

		dlWide = ( dlCYWide < dlWide ) ? dlCYWide : dlWide;
		bRetVal = TRUE;
	}

	m_pPicture->SetWide( dlWide );

	return bRetVal;
}

void CPicStandWnd::SetZOrder(enumZOrder ZOrder)
{
	m_ZOrder = ZOrder;

	switch( ZOrder ){

	case ZORDER_TOPMOST:

		SetWindowPos( &CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE );
		break;

	case ZORDER_BOTTOMMOST:

		SetWindowPos( &CWnd::wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE );
		SetWindowPos( &CWnd::wndBottom, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE );
		m_ZOrder = ZORDER_NORMAL;
		break;

	default:

		SetWindowPos( &CWnd::wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE );
		break;
	}
}

void CPicStandWnd::OnTopmost() 
{
	SetZOrder( ( m_ZOrder == ZORDER_TOPMOST ) ? ZORDER_NORMAL : ZORDER_TOPMOST );	
}

void CPicStandWnd::OnBottommost() 
{
	SetZOrder( ZORDER_BOTTOMMOST );	
}

void CPicStandWnd::OnStay() 
{
	m_bStay = ( m_bStay ) ? FALSE:TRUE;	
	m_pStayButton->SetUpState( ( m_bStay ) ? FALSE:TRUE );
	m_pStayButton->RedrawWindow();
}

void CPicStandWnd::OnBarstyle() 
{
	switch( m_WndStyle ){
	
	case WNDSTYLE_NORMAL:
		SetBarStyle();
		break;

	default:
		SetNormalStyle();
		break;
	}
}

void CPicStandWnd::OnHelp() 
{
	CString	HelpString = Global_GetCurrentDir() + "Help\\PicStand.html";

	ShellExecute( m_hWnd, "Open", HelpString, NULL,
				Global_GetCurrentDir(), SW_SHOWNORMAL );
}

void CPicStandWnd::OnSupport() 
{
	ShellExecute( m_hWnd, "Open",
		HP_URL,
		NULL, Global_GetCurrentDir(), SW_SHOWNORMAL );
	
}


void CPicStandWnd::OnEndSession(BOOL bEnding) 
{
	CWnd::OnEndSession(bEnding);
	
	SendMessage( WM_CLOSE );	
}

void CPicStandWnd::OnRegStartup() 
{
	if( StartupShorcutExist() ){

		CFile::Remove( Global_GetStartupShorcutPath() );
	
	}else{
	
		CreateStartupShortcut();
	}
}

void CPicStandWnd::OnVersiondlg() 
{
	CVersionInfoDlg	VersionInfoDlg;

	VersionInfoDlg.DoModal();
	
}

void CPicStandWnd::CreateStartupShortcut()
{
	ITech_CreateShorcut(
		Global_GetStartupShorcutPath(), ITech_GetModuleFileName(),
		Global_GetCurrentDir(), APP_NAME );
}

BOOL CPicStandWnd::StartupShorcutExist()
{
	return ITech_IsTheFileExist( Global_GetStartupShorcutPath() );
}

void CPicStandWnd::ActivateMenu(int nX, int nY)
{
	if( m_ZOrder == ZORDER_TOPMOST ){
	
		m_pMenu->CheckMenuItem( IDM_TOPMOST, MF_BYCOMMAND|MF_CHECKED );

	}else{
	
		m_pMenu->CheckMenuItem( IDM_TOPMOST, MF_BYCOMMAND|MF_UNCHECKED );
	}

	double	dlWide = m_pPicture->GetWide();

	if( dlWide == 1.0 ){

		m_pMenu->CheckMenuItem( IDM_MUL1, MF_BYCOMMAND|MF_CHECKED );
		m_pMenu->CheckMenuItem( IDM_MUL2, MF_BYCOMMAND|MF_UNCHECKED );
		m_pMenu->CheckMenuItem( IDM_DIV2, MF_BYCOMMAND|MF_UNCHECKED );
		m_pMenu->CheckMenuItem( IDM_SIZESETTING, MF_BYCOMMAND|MF_UNCHECKED );

	}else if( dlWide == 2.0 ){

		m_pMenu->CheckMenuItem( IDM_MUL1, MF_BYCOMMAND|MF_UNCHECKED );
		m_pMenu->CheckMenuItem( IDM_MUL2, MF_BYCOMMAND|MF_CHECKED );
		m_pMenu->CheckMenuItem( IDM_DIV2, MF_BYCOMMAND|MF_UNCHECKED );
		m_pMenu->CheckMenuItem( IDM_SIZESETTING, MF_BYCOMMAND|MF_UNCHECKED );

	}else if( dlWide == 0.5 ){

		m_pMenu->CheckMenuItem( IDM_MUL1, MF_BYCOMMAND|MF_UNCHECKED );
		m_pMenu->CheckMenuItem( IDM_MUL2, MF_BYCOMMAND|MF_UNCHECKED );
		m_pMenu->CheckMenuItem( IDM_DIV2, MF_BYCOMMAND|MF_CHECKED );
		m_pMenu->CheckMenuItem( IDM_SIZESETTING, MF_BYCOMMAND|MF_UNCHECKED );

	}else{

		m_pMenu->CheckMenuItem( IDM_MUL1, MF_BYCOMMAND|MF_UNCHECKED );
		m_pMenu->CheckMenuItem( IDM_MUL2, MF_BYCOMMAND|MF_UNCHECKED );
		m_pMenu->CheckMenuItem( IDM_DIV2, MF_BYCOMMAND|MF_UNCHECKED );
		m_pMenu->CheckMenuItem( IDM_SIZESETTING, MF_BYCOMMAND|MF_CHECKED );
	}

	if( m_bStay ){

		m_pMenu->CheckMenuItem( IDM_STAY, MF_BYCOMMAND|MF_CHECKED );

	}else{

		m_pMenu->CheckMenuItem( IDM_STAY, MF_BYCOMMAND|MF_UNCHECKED );
	}

	if( m_WndStyle == WNDSTYLE_BAR ){

		m_pMenu->CheckMenuItem( IDM_BARSTYLE, MF_BYCOMMAND|MF_CHECKED );

	}else{

		m_pMenu->CheckMenuItem( IDM_BARSTYLE, MF_BYCOMMAND|MF_UNCHECKED );
	}

	if( StartupShorcutExist() ){

		m_pMenu->CheckMenuItem( IDM_REG_STARTUP, MF_BYCOMMAND|MF_CHECKED );
	
	}else{

		m_pMenu->CheckMenuItem( IDM_REG_STARTUP, MF_BYCOMMAND|MF_UNCHECKED );
	}

	if( !m_bFixSize ){

		m_pMenu->CheckMenuItem( IDM_FIXSIZE, MF_BYCOMMAND|MF_CHECKED );
		m_pMenu->CheckMenuItem( IDM_FIXSIZE2, MF_BYCOMMAND|MF_UNCHECKED );
	
	}else{

		m_pMenu->CheckMenuItem( IDM_FIXSIZE, MF_BYCOMMAND|MF_UNCHECKED );
		m_pMenu->CheckMenuItem( IDM_FIXSIZE2, MF_BYCOMMAND|MF_CHECKED );
	}

	if( m_pCustomizeWnd ){

		m_pMenu->CheckMenuItem( IDM_CUSTOMIZEWND, MF_BYCOMMAND|MF_CHECKED );

	}else{

		m_pMenu->CheckMenuItem( IDM_CUSTOMIZEWND, MF_BYCOMMAND|MF_UNCHECKED );
	}

	m_pMenu->GetSubMenu(0)->TrackPopupMenu( TPM_RIGHTALIGN | TPM_RIGHTBUTTON,
		nX, nY, this, NULL );
}

void CPicStandWnd::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CPoint	MousePoint;
	::GetCursorPos( &MousePoint );

	ActivateMenu( MousePoint.x, MousePoint.y );
	
	CWnd::OnRButtonDown(nFlags, point);
}

void CPicStandWnd::OnFixsize() 
{
	m_bFixSize = FALSE;
	InvalidateRect( NULL );
}

void CPicStandWnd::OnFixsize2() 
{
	m_bFixSize = TRUE;	
	InvalidateRect( NULL );
}

void CPicStandWnd::SetPictureWide( BOOL bCXFix )
{
	if( m_bFixSize ){
		
		CRect	WndRect;
		GetWindowRect( &WndRect );

		double	dlXWide = (double)( WndRect.Width() - CX_FRAME * 2 ) / (double)m_pPicture->GetBitmapWidth();
		double	dlYWide = (double)( WndRect.Height() - CY_FRAME * 2 ) / (double)m_pPicture->GetBitmapHeight();
		if( bCXFix ){

			m_pPicture->SetWide( dlXWide );
			
		}else{
			m_pPicture->SetWide( ( dlXWide < dlYWide ) ? dlXWide : dlYWide );
		}

	}else{

		m_pPicture->SetWide(1);
	}

}

void CPicStandWnd::CreateCashList()
{
	int nSize = m_CashFilePathArray.GetSize();

	if( nSize ){

		for( int nPos = 0; nPos < nSize; nPos++ ){

			delete m_CashFilePathArray[ nPos ];
		}
		m_CashFilePathArray.RemoveAll();
	}

	CString	PicturePath = Global_GetPictureDataDir();
	PicturePath += _T( "*.*" );

	CFileFind finder;
	BOOL bWorking = finder.FindFile(PicturePath);
	while (bWorking){

		bWorking = finder.FindNextFile();
		
		CString	FilePath( finder.GetFilePath() );
		CString	ExtString;
		_splitpath( (LPCTSTR)FilePath,
			NULL, NULL, NULL, ExtString.GetBuffer( _MAX_EXT ) );
		ExtString.ReleaseBuffer();
		ExtString.MakeUpper();
		if( ( ExtString == _T( ".JPG" ) ) || ( ExtString == _T( ".BMP" ) ) ){

			m_CashFilePathArray.Add( new CString( FilePath ) );
		}
	}

}

void CPicStandWnd::OnCashDelete() 
{
	DeletePicture();
	CheckCurrentPicture();
}

void CPicStandWnd::OnCashNext() 
{
	PostMessage( g_uIdeaTechMessage, ITMES_NEXTBTN, NULL );	
}

void CPicStandWnd::OnCashPrev() 
{
	PostMessage( g_uIdeaTechMessage, ITMES_BACKBTN, NULL );		
}

void CPicStandWnd::DeletePicture()
{
	CString	DeletePictureFileName = m_pPicture->GetFileNameString();
	if( DeletePictureFileName == FIXEDPIC_FILENAME ){ return; }

	CString	DeletePicturePath = m_pPicture->GetFilePathString();	
	SendMessage( g_uIdeaTechMessage, ITMES_BACKBTN, NULL );		

	DWORD	dwAttr = GetFileAttributes( DeletePicturePath );
	dwAttr &= ~FILE_ATTRIBUTE_READONLY;
	SetFileAttributes( DeletePicturePath, dwAttr );
	DeleteFile( DeletePicturePath.GetBuffer(0) );
	CreateCashList();
}

void CPicStandWnd::OnCustomizewnd() 
{
	if( m_pCustomizeWnd ){
		m_pCustomizeWnd->SetForegroundWindow();
		return;
	}

	m_pCustomizeWnd = new CCustomizeWnd( this );

	// 位置補正処理
	// Y座標がデスクトップにはみ出している場合の処理が不十分

	CRect	WndRect;
	GetWindowRect( &WndRect );

	CRect	CustomizeWndRect;
	m_pCustomizeWnd->GetWindowRect( &CustomizeWndRect );
	
	CRect	DesktopRect;
	::SystemParametersInfo( SPI_GETWORKAREA, 0, &DesktopRect, NULL );

	int	nStartX = WndRect.right;
	int	nStartY = WndRect.bottom - CustomizeWndRect.Height();
	if( WndRect.right + CustomizeWndRect.Width() > DesktopRect.right ){

		nStartX = WndRect.left - CustomizeWndRect.Width();
	}
	if( nStartY < 0 ){

		nStartY = 0;
	}
	if( nStartY + CustomizeWndRect.Height() > DesktopRect.bottom ){

		nStartY = DesktopRect.bottom - CustomizeWndRect.Height();
	}
	
	m_pCustomizeWnd->SetWindowPos( NULL,
		nStartX, nStartY,
		0, 0, SWP_NOZORDER | SWP_NOSIZE ); 
	m_pCustomizeWnd->ShowWindow( SW_SHOW );
}

void CPicStandWnd::SetColors()
{
	m_Color = RGB( m_ColorR, m_ColorG, m_ColorB );
	m_DarkColor = RGB( 
		CREATE_DARK_COLOR_R( m_ColorR ),
		CREATE_DARK_COLOR_G( m_ColorG ),
		CREATE_DARK_COLOR_B( m_ColorB ) );

	UINT	uRed = CREATE_LIGHT_COLOR_R( m_ColorR );
	uRed = ( uRed > 255 ) ? 255 : uRed;

	UINT	uGreen = CREATE_LIGHT_COLOR_G( m_ColorG );
	uGreen = ( uGreen > 255 ) ? 255 : uGreen;

	UINT	uBlue = CREATE_LIGHT_COLOR_B( m_ColorB );
	uBlue = ( uBlue > 255 ) ? 255 : uBlue;
	
	m_LightColor = RGB( uRed, uGreen, uBlue );

	uRed = CREATE_LIGHT_2_COLOR_R( m_ColorR );
	uRed = ( uRed > 255 ) ? 255 : uRed;

	uGreen = CREATE_LIGHT_2_COLOR_G( m_ColorG );
	uGreen = ( uGreen > 255 ) ? 255 : uGreen;

	uBlue = CREATE_LIGHT_2_COLOR_B( m_ColorB );
	uBlue = ( uBlue > 255 ) ? 255 : uBlue;

	m_Light2Color = RGB( uRed, uGreen, uBlue );
	
}

LRESULT CPicStandWnd::OnCustomizeWndMessage( WPARAM wParam, LPARAM lParam )
{
	switch( wParam ){
	case CWM_SET_DEFAULT:

		m_ColorR = RGB_BACK_R;
		m_ColorG = RGB_BACK_G;
		m_ColorB = RGB_BACK_B;
		SetColors();

		CX_FRAME = 32;
		AdjustWindowSizePos();
		InvalidateRect( NULL );
		break;
	default:
		break;
	}

	return -1;
}

void CPicStandWnd::CheckCurrentPicture()
{
	if( !ITech_IsTheFileExist( m_pPicture->GetFilePathString() ) ){

		if( !m_CashFilePathArray.GetSize() ){

			m_pPicture->Set();		

		}else{

			m_pPicture->Set( *( m_CashFilePathArray[0] ) );
		}
		m_pStatusWnd->SetDispString( m_pPicture->GetFileNameString() );
		SetPictureWide( TRUE );
		AdjustWindowSizePos();
		InvalidateRect( NULL );
	}
}