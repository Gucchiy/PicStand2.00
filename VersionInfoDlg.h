#if !defined(AFX_VERSIONINFODLG_H__D0D5016A_0B27_4CD5_A5EE_53D964595530__INCLUDED_)
#define AFX_VERSIONINFODLG_H__D0D5016A_0B27_4CD5_A5EE_53D964595530__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VersionInfoDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CVersionInfoDlg �_�C�A���O

class CVersionInfoDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CVersionInfoDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CVersionInfoDlg)
	enum { IDD = IDD_VERSION_INFO };
		// ����: ClassWizard �͂��̈ʒu�Ƀf�[�^ �����o��ǉ����܂��B
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CVersionInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CVersionInfoDlg)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_VERSIONINFODLG_H__D0D5016A_0B27_4CD5_A5EE_53D964595530__INCLUDED_)
