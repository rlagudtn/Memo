//CtrlSaveKey.cpp
#include "CtrlSaveKey.h"
#include "MemoForm.h"
#include "Save.h"
#include <afxwin.h>
CtrlSaveKey::CtrlSaveKey() {

}
CtrlSaveKey::CtrlSaveKey(const CtrlSaveKey& source) {

}
CtrlSaveKey::~CtrlSaveKey() {

}

void CtrlSaveKey::Implement(MemoForm *memoForm) {
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