// Picture.cpp: CPicture クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "picstand.h"
#include "Picture.h"
#include <vfw.h>
#include "Global.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CPicture::CPicture()
{
	m_lpBitmapInfoHeader = NULL;
	m_pDIB = NULL;
	m_dlWide = 1.0;
	m_pDefaultBitmap = NULL;
}

CPicture::~CPicture()
{
	if( m_pDIB ){

		DibFree( m_pDIB );
		m_pDIB = NULL;
	}

	if( m_lpBitmapInfoHeader ){

		delete []m_lpBitmapInfoHeader;
		m_lpBitmapInfoHeader = NULL;
	}

	if( m_pDefaultBitmap ){

		delete m_pDefaultBitmap;
		m_pDefaultBitmap = NULL;
	}
}

BOOL CPicture::Set(const CString &PathNameString)
{
	if( m_pDefaultBitmap ){

		delete m_pDefaultBitmap;
		m_pDefaultBitmap = NULL;
	}

	if( m_pDIB ){

		DibFree( m_pDIB );
		m_pDIB = NULL;
	}

	if( m_lpBitmapInfoHeader ){

		delete []m_lpBitmapInfoHeader;
		m_lpBitmapInfoHeader = NULL;
	}

	if( PathNameString.IsEmpty() ){

		m_pDefaultBitmap = new CBitmap;
		m_pDefaultBitmap->LoadBitmap( IDB_DEFAULT );
		m_dlWide = 1.0;

		m_FilePathString.Empty();

		return TRUE;
	}

	LPBITMAPINFOHEADER	lpBitmapInfoHeader = NULL;
	PDIB				pDIB = NULL;

	// 拡張子の抽出
	CString	ExtString;
	_splitpath( (LPCTSTR)PathNameString, NULL, NULL, NULL, ExtString.GetBuffer( _MAX_EXT ) );
	ExtString.ReleaseBuffer();

	ExtString.MakeUpper();

	if( ExtString == _T( ".JPG" ) ){

		CString	LoadFilePathString;
		
		if( !CopyPictureFile( PathNameString, LoadFilePathString ) ){

			return FALSE;
		}

		if( !DecodeJPGFileToDIB( LoadFilePathString, &lpBitmapInfoHeader ) ){

			return FALSE;
		}
		
		m_FilePathString = LoadFilePathString;

	}else if( ( ExtString == _T( ".DIB" ) ) || ( ExtString == _T( ".BMP" ) ) ){

		CString	LoadFilePathString;
		
		if( !CopyPictureFile( PathNameString, LoadFilePathString ) ){

			return FALSE;
		}

		pDIB = DibOpenFile( (LPSTR)(LPCTSTR)LoadFilePathString );

		if( !pDIB ){ return FALSE; }

		m_FilePathString = LoadFilePathString;

	}else{

		return FALSE;
	}

	m_pDIB = pDIB;
	m_lpBitmapInfoHeader = lpBitmapInfoHeader;

	m_dlWide = 1.0;

	return TRUE;
}

void CPicture::DrawTo(HDC hDC, int nX, int nY )
{
	int	nCX = GetBitmapWidth();
	int	nCY = GetBitmapHeight();

	if( m_pDefaultBitmap ){

		CDC	dc;
		CDC*	pDC = CDC::FromHandle( hDC );
		dc.CreateCompatibleDC( pDC );
		CBitmap*	pOldBitmap = dc.SelectObject( m_pDefaultBitmap );

		pDC->StretchBlt( nX, nY, (int)( nCX * m_dlWide ), (int)( nCY * m_dlWide ),
			&dc, 0, 0, nCX, nCY, SRCCOPY );


		dc.SelectObject( pOldBitmap );

		return;
	}

	HDRAWDIB	hDrawDIB = DrawDibOpen();

	LPBITMAPINFOHEADER	lpBitmapInfoHeader = GetBitmapInfoHeader();
	if( !lpBitmapInfoHeader ){ return; }

	LPVOID		lpBitmapBits = GetBitmapBits();

	DrawDibDraw( hDrawDIB, hDC, nX,nY, (int)( nCX * m_dlWide ), (int)( nCY * m_dlWide ),
		lpBitmapInfoHeader, lpBitmapBits,0, 0, nCX, nCY, DDF_HALFTONE );

	DrawDibClose(hDrawDIB);

}

int CPicture::GetWidth()
{
	int nReturn = 0;
	if( m_pDIB ){ nReturn = (int)( DibWidth( m_pDIB ) * m_dlWide ); }
	if( m_lpBitmapInfoHeader ){ nReturn = (int)( DibWidth( m_lpBitmapInfoHeader ) * m_dlWide ); }
	if( m_pDefaultBitmap ){

		BITMAP	Bitmap;
		m_pDefaultBitmap->GetBitmap( &Bitmap );
		nReturn = (int)( Bitmap.bmWidth * m_dlWide );
	}

	return nReturn;
}

int CPicture::GetHeight()
{
	if( m_pDIB ){ return (int)( DibHeight( m_pDIB ) * m_dlWide ); }
	if( m_lpBitmapInfoHeader ){ return (int)( DibHeight( m_lpBitmapInfoHeader ) * m_dlWide ); }
	if( m_pDefaultBitmap ){

		BITMAP	Bitmap;
		m_pDefaultBitmap->GetBitmap( &Bitmap );
		return (int)( Bitmap.bmHeight * m_dlWide );
	}

	return 0;
}

int CPicture::GetBitmapWidth()
{
	if( m_pDIB ){ return DibWidth( m_pDIB ); }
	if( m_lpBitmapInfoHeader ){ return DibWidth( m_lpBitmapInfoHeader ); }
	if( m_pDefaultBitmap ){

		BITMAP	Bitmap;
		m_pDefaultBitmap->GetBitmap( &Bitmap );
		return Bitmap.bmWidth;

	}

	return 0;
}

int CPicture::GetBitmapHeight()
{
	if( m_pDIB ){ return DibHeight( m_pDIB ); }
	if( m_lpBitmapInfoHeader ){ return DibHeight( m_lpBitmapInfoHeader ); }
	if( m_pDefaultBitmap ){

		BITMAP	Bitmap;
		m_pDefaultBitmap->GetBitmap( &Bitmap );
		return Bitmap.bmHeight;
	}

	return 0;
}

LPBITMAPINFOHEADER CPicture::GetBitmapInfoHeader()
{
	if( m_pDIB ){ return m_pDIB; }
	if( m_lpBitmapInfoHeader ){ return m_lpBitmapInfoHeader; }
/*	if( m_pDefaultBitmap ){

		BITMAP	Bitmap;
		m_pDefaultBitmap->GetBitmap( &Bitmap );
		return (LPBITMAPINFOHEADER) &Bitmap;
	}
*/
	return NULL;

}

LPVOID CPicture::GetBitmapBits()
{
	if( m_pDIB ){ return DibPtr( m_pDIB ); }
	if( m_lpBitmapInfoHeader ){ return DibPtr( m_lpBitmapInfoHeader ); }
/*	if( m_pDefaultBitmap ){

		HBITMAP	hBitmap;
		m_pDefaultBitmap->GetBitmap( &hBitmap );
		return hBitmap.bmBits;
	}
*/
	return NULL;
}

BOOL CPicture::CopyPictureFile(const CString &PathNameString, CString &CopiedPathNameString)
{

	// カレントフォルダを取得
	CString	CurrentDirString = Global_GetCurrentDir();

	// ファイル名と拡張子、フォルダを取得
	CString	FileNameString;
	CString	ExtString;
	_splitpath( (LPCTSTR)PathNameString,
		NULL, NULL,
		FileNameString.GetBuffer( _MAX_FNAME ), ExtString.GetBuffer( _MAX_EXT ) );
	FileNameString.ReleaseBuffer();
	ExtString.ReleaseBuffer();

	// フォルダの作成とファイルのコピー
	CopiedPathNameString = Global_GetPictureDataDir();

	CopiedPathNameString = CopiedPathNameString + FileNameString + ExtString;

	// 同じフォルダであった場合
	if( PathNameString == CopiedPathNameString ){ return TRUE; }

	return CopyFile( PathNameString, CopiedPathNameString, FALSE );
}

CString CPicture::GetFilePathString()
{
	return	m_FilePathString;
}

CString CPicture::GetFileNameString()
{
	CString	FileNameString;
	CString	ExtNameString;
	_splitpath( m_FilePathString, NULL, NULL, FileNameString.GetBuffer( _MAX_FNAME ), ExtNameString.GetBuffer( _MAX_EXT ) );
	FileNameString.ReleaseBuffer();
	ExtNameString.ReleaseBuffer();

	return FileNameString + ExtNameString;
}
