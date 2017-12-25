//ExitMenu.cpp
#include "ExitMenu.h"
#include "MemoForm.h"
#include "Save.h"
ExitMenu::ExitMenu() {}
ExitMenu::~ExitMenu() {}

void ExitMenu::Implement(MemoForm *memoForm) {
	memoForm->PostMessageA(WM_CLOSE);

}