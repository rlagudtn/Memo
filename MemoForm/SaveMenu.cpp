//SaveMenu.cpp
#include "SaveMenu.h"
#include "MemoForm.h"
#include "Save.h"
SaveMenu::SaveMenu() {}
SaveMenu::~SaveMenu() {}

void SaveMenu::Implement(MemoForm *memoForm) {
		CString savePath = memoForm->originalPathName;
		if (memoForm->originalPathName == "") {
			CFileDialog dlg(FALSE, "*.txt", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "text Files(*.txt)|*.txt|");
			if (dlg.DoModal() == IDOK) {
				savePath = dlg.GetPathName();
				memoForm->originalPathName = dlg.GetPathName();
				
			}
		}
		Save save;
		save.SaveMemo(memoForm, (LPCTSTR)savePath);
		memoForm->isChanged = false;
}