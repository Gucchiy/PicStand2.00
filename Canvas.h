/*----------------------------------------------------------------
	CCanvas Definition
  ----------------------------------------------------------------
	Description:
		���z DC �N���X�B
		���̃N���X�ō쐬����� DC �ɕ`�悵�A
		���̏�ŕ\�� DC ��ɓ]��(CCanvass::DrawTo)���邱�ƂŁA
		�������}�����`�悪�\�ɂȂ�܂��B
  
	Auther:
		Yoshihiro Yamaguchi MPD 2-2-4

	Define:
		Canvas.h

	Implement:
		Canvas.cpp

	History:

	00/06/23	Initial Check-in
  ----------------------------------------------------------------*/

#if !defined(AFX_CANVAS_H__C51AC50A_DFEA_4FDB_BD9C_3BDEA43972FF__INCLUDED_)
#define AFX_CANVAS_H__C51AC50A_DFEA_4FDB_BD9C_3BDEA43972FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCanvas  
{
protected:

	// �\������ DC ������ Window �ւ̃|�C���^
	CWnd*	m_pAppWnd;

	// ���z DC 
	CDC		m_CanvasDC;
	CBitmap	m_CanvasBitmap;

	// ��ƂȂ�t���[��
	CDC		m_FrameDC;
	CBitmap	m_FrameBitmap;

	// ���z DC �� Size
	CRect	m_CanvasRect;

public:

	// ���z DC �̎擾
	CDC* GetCanvasDC(){ return &m_CanvasDC; }

public:
	CCanvas( CWnd* pAppWnd, UINT uFrameBitmapID );
	virtual ~CCanvas();

	// ���z DC �� m_FrameBitmap �ŏ�����
	virtual void ClearCanvas();

	// ���z DC �� pDC �Ŏ������ DC ��ɓW�J
	virtual void DrawTo( CDC* pDC );
	virtual void DrawTo( CDC* pDC, int nX, int nY );

	// �T�C�Y�̎擾
	CRect GetCanvasRect(){ return m_CanvasRect; }

};

#endif // !defined(AFX_CANVAS_H__C51AC50A_DFEA_4FDB_BD9C_3BDEA43972FF__INCLUDED_)
