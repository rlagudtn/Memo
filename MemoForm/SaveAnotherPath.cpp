//SaveAnotherPathMenu.cpp
#include "SaveAnotherPathMenu.h"
#include "MemoForm.h"
#include "Save.h"
SaveAnotherPathMenu::SaveAnotherPathMenu() {}
SaveAnotherPathMenu::~SaveAnotherPathMenu() {}

void SaveAnotherPathMenu::Implement(MemoForm *memoForm) {
	CFileDialog dlg(FALSE, "*.txt", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "text Files(*.txt)|*.txt|");
	if (dlg.DoModal() == IDOK) {
		Save save;
		save.SaveMemo(memoForm, (LPCTSTR)dlg.GetPathName());
	}
}

