// PicStandDlg.h : �w�b�_�[ �t�@�C��
//

#if !defined(AFX_PICSTANDDLG_H__948FABC4_5039_45B6_B08C_66C86A8AC391__INCLUDED_)
#define AFX_PICSTANDDLG_H__948FABC4_5039_45B6_B08C_66C86A8AC391__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPicStandDlg �_�C�A���O

class CPicStandDlg : public CDialog
{
// �\�z
public:
	CPicStandDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CPicStandDlg)
	enum { IDD = IDD_PICSTAND_DIALOG };
		// ����: ���̈ʒu�� ClassWizard �ɂ���ăf�[�^ �����o���ǉ�����܂��B
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CPicStandDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	HICON m_hIcon;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CPicStandDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_PICSTANDDLG_H__948FABC4_5039_45B6_B08C_66C86A8AC391__INCLUDED_)