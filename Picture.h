// Picture.h: CPicture クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PICTURE_H__BF4B7942_87E9_45C1_9331_F8ED886CC75B__INCLUDED_)
#define AFX_PICTURE_H__BF4B7942_87E9_45C1_9331_F8ED886CC75B__INCLUDED_

#include "Dibutils.h"	// ClassView によって追加されました。
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Dibutils.h"
#include "IJLWrapper.h"

class CPicture  
{
public:
	CString GetFileNameString();
	CString GetFilePathString();
	int GetHeight();
	int GetWidth();
	void DrawTo( HDC hDC, int nX, int nY );
	BOOL Set( const CString& PathNameString = "" );
	double GetWide(){ return m_dlWide; }
	void SetWide( double dlWide ){ m_dlWide = dlWide; }
	int GetBitmapWidth();
	int GetBitmapHeight();

public:
	CPicture();
	virtual ~CPicture();

protected:
	CString		m_FilePathString;
	LPBITMAPINFOHEADER m_lpBitmapInfoHeader;	// for JPEG
	PDIB		m_pDIB;							// for DIB
	double		m_dlWide;						// Wide
	CBitmap*	m_pDefaultBitmap;

protected:
	BOOL CopyPictureFile( const CString& PathNameString, CString& CopiedPathNameString );
	LPVOID GetBitmapBits();
	LPBITMAPINFOHEADER GetBitmapInfoHeader();
};

#endif // !defined(AFX_PICTURE_H__BF4B7942_87E9_45C1_9331_F8ED886CC75B__INCLUDED_)
