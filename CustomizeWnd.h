#if !defined(AFX_CUSTOMIZEWND_H__EF667974_C2E1_41B6_BD2B_363B13004BDA__INCLUDED_)
#define AFX_CUSTOMIZEWND_H__EF667974_C2E1_41B6_BD2B_363B13004BDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomizeWnd.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CCustomizeWnd �_�C�A���O

class CCustomizeWnd : public CDialog
{
// �f�[�^
	UINT	m_uRedTemp;
	UINT	m_uGreenTemp;
	UINT	m_uBlueTemp;
	UINT	m_uWidthTemp;

// �R���X�g���N�V����
public:
	CCustomizeWnd(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CCustomizeWnd)
	enum { IDD = IDD_CUSTOMIZE_WND };
	CScrollBar	m_WidthScrollBar;
	CScrollBar	m_BlueScrollBar;
	CScrollBar	m_GreenScrollBar;
	CScrollBar	m_RedScrollBar;
	UINT	m_uBlueValue;
	UINT	m_uGreenValue;
	UINT	m_uRedValue;
	UINT	m_uWidthValue;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CCustomizeWnd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CCustomizeWnd)
	afx_msg void OnDestroy();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnDefault();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_CUSTOMIZEWND_H__EF667974_C2E1_41B6_BD2B_363B13004BDA__INCLUDED_)
