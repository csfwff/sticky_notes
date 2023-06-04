#pragma once
#include <winrt/Windows.UI.ViewManagement.h>
using namespace Windows::UI::ViewManagement;

inline bool IsColorLight(Windows::UI::Color& clr)
{
	return (((5 * clr.G) + (2 * clr.R) + clr.B) > (8 * 128));
}

typedef struct _NoteItem
{
	ULONG uId;
	CString sContent;
	bool bFinished;

	_NoteItem()
	{
		bFinished = false;
	}

}NoteItem, *PNoteItem;

typedef struct NoteGroup
{
	CString sName;
	CRect rect;
	COLORREF bgColor;
	int nOpacity;
	bool bOpacity;
	bool bVisible;
	bool bTopMost;
	std::vector<NoteItem> vNotes;

	NoteGroup()
	{
		auto settings = UISettings();
		auto foreground = settings.GetColorValue(UIColorType::Foreground);
		bgColor = IsColorLight(foreground) ? RGB(11, 15, 20) : RGB(255,255,255);
		rect = CRect(100, 100, 530, 530);
		// ʹ��ʱ�����ΪĬ������
		sName = CTime::GetCurrentTime().Format(_T("%Y%m%d%H%M%S"));
		bOpacity = false;
		nOpacity = 50;
		bTopMost = bVisible = true;
	}

	CString toHex() {
		return Cvt::ToHex(bgColor);
	}
};

typedef struct _Setting
{
	DWORD dwEditHotKey;
	DWORD dwNewHotKey;
	DWORD dwUnActiveHotKey;
	CString sNoteDir;

	_Setting() {
		dwEditHotKey = ((CHotKeyEdit::WIN | CHotKeyEdit::SHIFT) << 8) | VK_F7;
		dwNewHotKey = ((CHotKeyEdit::WIN | CHotKeyEdit::SHIFT) << 8) | VK_F8;
		dwUnActiveHotKey = ((CHotKeyEdit::WIN | CHotKeyEdit::SHIFT) << 8) | VK_F9;
		sNoteDir = Path::GetCurDirectory(_T("notes"));
	}
}Setting, *PSetting;
