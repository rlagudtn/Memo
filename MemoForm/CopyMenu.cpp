//CopyMenu.cpp
#include "CopyMenu.h"
#include "MemoForm.h"
#include "SelectedText.h"
CopyMenu::CopyMenu() {}
CopyMenu::~CopyMenu() {}

void CopyMenu::Implement(MemoForm *memoForm) {
	if (memoForm->selectedText != NULL) {

	}
	else {
		CMenu menu;
		menu.EnableMenuItem(209, MF_GRAYED);
	}
}