#if !defined(AFX_STATUSWND_H__66C8FE83_609E_4B70_8D20_BB696BB2BFCD__INCLUDED_)
#define AFX_STATUSWND_H__66C8FE83_609E_4B70_8D20_BB696BB2BFCD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatusWnd.h : �w�b�_�[ �t�@�C��
//

#include "Canvas.h"
#include "CanvasItem.h"
#include "IdeaTech.h"

/////////////////////////////////////////////////////////////////////////////
// CStatusWnd �E�B���h�E
enum enumSWState {
	SWST_NUTORAL = 0,
	SWST_HIGHLIGHT
};

class CStatusWnd : public CWnd
{
// �R���X�g���N�V����
public:
	CStatusWnd( UINT uCanvasBmpID, UINT uHighlightBmpID );

// �A�g���r���[�g
public:

protected:
	UINT			m_uCanvasBmpID;
	CCanvas*		m_pCanvas;
	
	UINT			m_uHighlightBmpID;
	CCanvasItem*	m_pHighlightItem;

	enumSWState		m_State;

	UINT			m_uMessage;
	WPARAM			m_wParam;
	LPARAM			m_lParam;

	CWnd*			m_pParentWnd;

	CFont*			m_pFont;

	CString			m_DispString;

// �I�y���[�V����
public:
	BOOL Create( CWnd* pParent, int nPosX, int nPosY, WPARAM wParam = NULL, LPARAM lParam = NULL );
	void SetDispString( const CString& DispString );

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CStatusWnd)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CStatusWnd();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CStatusWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_STATUSWND_H__66C8FE83_609E_4B70_8D20_BB696BB2BFCD__INCLUDED_)
