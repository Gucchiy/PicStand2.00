#if !defined(AFX_CUSTOMBUTTON_H__377C5073_2C4B_4109_8ACB_9B0EC382B76D__INCLUDED_)
#define AFX_CUSTOMBUTTON_H__377C5073_2C4B_4109_8ACB_9B0EC382B76D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomButton.h : �w�b�_�[ �t�@�C��
//
#include "Canvas.h"
#include "CanvasItem.h"
#include "IdeaTech.h"

/////////////////////////////////////////////////////////////////////////////
// CCustomButton �E�B���h�E
//
// -----------------------------------------------------------------------
// �r�b�g�}�b�v�{�^�������O�ōs���N���X�B
// �ʏ��ԁA�n�C���C�g��ԁA�v�b�V����ԂR�� Bitmap ��p�ӂ��A
// �R���X�g���N�^�ɓn���ăC���X�^���X�𐶐�����B
// ���̌�ACreate �����o�֐����Ăяo���ΐ��������B
// �����̃C�x���g�́ACreate �̈����Ƃ��ēn�����l���AIdeaTechMessage �Ƃ��āA
// �e Window �Ƀ|�X�g�����B

enum enumState{
	CBST_NUTORAL = 0,
	CBST_HIGHLIGHT,
	CBST_PUSH
};

class CCustomButton : public CWnd
{
// �R���X�g���N�V����
public:
	// -----------------------------------------------------------------------
	// �R���X�g���N�^
	// -----------------------------------------------------------------------
	// uCanvasBmpID		�ʏ��� Bitmap �̃��\�[�X ID
	// uHighlightBmpID	�n�C���C�g��� Bitmap �̃��\�[�X ID
	// uPushBmpID		�v�b�V����� Bitmap �̃��\�[�X ID
	// -----------------------------------------------------------------------
	CCustomButton( UINT uCanvasBmpID, UINT uHighlightBmpID, UINT uPushBmpID );

// �A�g���r���[�g
public:

protected:
	UINT			m_uCanvasBmpID;
	CCanvas*		m_pCanvas;
	
	UINT			m_uHighlightBmpID;
	CCanvasItem*	m_pHighlightItem;

	UINT			m_uPushBmpID;
	CCanvasItem*	m_pPushItem;

	enumState		m_State;

	UINT			m_uMessage;
	WPARAM			m_wParam;
	LPARAM			m_lParam;

	CWnd*			m_pParentWnd;

// �I�y���[�V����
public:
	// -----------------------------------------------------------------------
	// ����
	// -----------------------------------------------------------------------
	// pParent	�e Window �i�ʒm Window�j
	// nPosX	�����\���ʒu X
	// nPosY	�����\���ʒu Y
	// wParam	�������̒ʒm�ɂ����� wParam
	// lParam	�������̒ʒm�ɂ����� lParam
	BOOL Create( CWnd* pParent, int nPosX, int nPosY, WPARAM wParam = NULL, LPARAM lParam = NULL );

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CCustomButton)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CCustomButton();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CCustomButton)
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

#endif // !defined(AFX_CUSTOMBUTTON_H__377C5073_2C4B_4109_8ACB_9B0EC382B76D__INCLUDED_)
