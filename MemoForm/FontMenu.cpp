//FontMenu.cpp
#include "FontMenu.h"
#include "MemoForm.h"
FontMenu::FontMenu() {}
FontMenu::~FontMenu() {}

void FontMenu::Implement(MemoForm *memoForm) {
	//�۲� ������ ���ٸ�
	if (memoForm->fontDlg == NULL) {
		memoForm->fontDlg = new CFontDialog(NULL, CF_SCREENFONTS);
	}
	if (memoForm->fontDlg->DoModal() == IDOK)
	{

	}

}