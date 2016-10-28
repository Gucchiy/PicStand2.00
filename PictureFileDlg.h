#if !defined(AFX_PICTUREFILEDLG_H__34140F08_9EF5_4AC5_AFC1_BAABEEEDDBF3__INCLUDED_)
#define AFX_PICTUREFILEDLG_H__34140F08_9EF5_4AC5_AFC1_BAABEEEDDBF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PictureFileDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CPictureFileDlg �_�C�A���O

class CPictureFileDlg : public CFileDialog
{
	DECLARE_DYNAMIC(CPictureFileDlg)

public:
	CPictureFileDlg(BOOL bOpenFileDialog, // TRUE �Ȃ�� FileOpen�A FALSE �Ȃ�� FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

	CPictureFileDlg( LPCTSTR lpszFileName, CWnd* pParentWnd );

protected:

protected:
	//{{AFX_MSG(CPictureFileDlg)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_PICTUREFILEDLG_H__34140F08_9EF5_4AC5_AFC1_BAABEEEDDBF3__INCLUDED_)
