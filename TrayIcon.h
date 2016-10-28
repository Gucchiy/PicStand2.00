// TrayIcon.h: CTrayIcon �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRAYICON_H__C23E4397_151C_48D8_83E9_AFCB5304AC6D__INCLUDED_)
#define AFX_TRAYICON_H__C23E4397_151C_48D8_83E9_AFCB5304AC6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTrayIcon
//
// -----------------------------------------------------------------------
// �^�X�N�g���C��� Icon ��\�����AIdea Tech ���b�Z�[�W��Ⴄ�悤�ɂ���

class CTrayIcon  
{
protected:
	// Notyfy Icon Data ��
	NOTIFYICONDATA	m_NotifyIconData;

public:
	// -----------------------------------------------------------------------
	// �R���X�g���N�^
	// -----------------------------------------------------------------------
	// hWnd			IdeaTech Message ��Ⴄ Window
	// uIconID		�^�X�N�g���C�ɕ\������ Icon �ւ̃��\�[�X ID
	// TipString	Tip �p������i�}�E�X�������Ă����ƕ\�������j
	// wParam		�C�x���g�������ɓ������� wParam ���b�Z�[�W�p�����[�^�̒l
	// -----------------------------------------------------------------------
	CTrayIcon( HWND hWnd, UINT uIconID, CString TipString, WPARAM wParam );
	virtual ~CTrayIcon();

	virtual void OnMessage( LPARAM lParam);

};

#endif // !defined(AFX_TRAYICON_H__C23E4397_151C_48D8_83E9_AFCB5304AC6D__INCLUDED_)
