#if !defined(AFX_STAYBUTTON_H__C062C18C_8923_404F_AF14_75510479DA3F__INCLUDED_)
#define AFX_STAYBUTTON_H__C062C18C_8923_404F_AF14_75510479DA3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StayButton.h : �w�b�_�[ �t�@�C��
//
#include "CanvasItem.h"
#include "IdeaTech.h"

/////////////////////////////////////////////////////////////////////////////
// CStayButton �E�B���h�E

class CStayButton : public CWnd
{
// �R���X�g���N�V����
public:
	CStayButton( UINT uDownBmpID, UINT uDownHighlightBmpID,
		UINT uUpBmpID, UINT uUpHighlightBmpID );

// �A�g���r���[�g
public:

protected:
	UINT			m_uDownBmpID;
	CCanvasItem*	m_pDownItem;

	UINT			m_uDownHighlightBmpID;
	CCanvasItem*	m_pDownHighlightItem;

	UINT			m_uUpBmpID;
	CCanvasItem*	m_pUpItem;

	UINT			m_uUpHighlightBmpID;
	CCanvasItem*	m_pUpHighlightItem;

	BOOL			m_bIsNowUp;
	BOOL			m_bIsNowHighlight;

	UINT			m_uMessage;
	WPARAM			m_wParam;
	LPARAM			m_lParam;

	CWnd*			m_pParentWnd;

// �I�y���[�V����
public:
	BOOL Create( CWnd* pParent, int nPosX, int nPosY, WPARAM wParam = NULL, LPARAM lParam = NULL );
	BOOL IsNowUp(){ return m_bIsNowUp; }
	void SetUpState( BOOL bUp = TRUE ){ m_bIsNowUp = bUp; }
	BOOL GetUpState(){ return m_bIsNowUp; }

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CStayButton)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CStayButton();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CStayButton)
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

#endif // !defined(AFX_STAYBUTTON_H__C062C18C_8923_404F_AF14_75510479DA3F__INCLUDED_)
