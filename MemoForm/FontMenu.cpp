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
		LOGFONT lf;
		memoForm->fontDlg->GetCurrentFont(&lf);
		memoForm->font->DeleteObject();
		memoForm->font->CreateFontIndirectA(&lf);
		memoForm->SetFont(memoForm->font, 1);
		memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
	}

}