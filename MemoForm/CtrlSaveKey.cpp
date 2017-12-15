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
	CFileDialog dlg(FALSE, "*.txt", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "text Files(*.txt)|*.txt|");
	if (dlg.DoModal() == IDOK) {
		Save save;
		save.SaveMemo(memoForm, (LPCTSTR)dlg.GetPathName());
	}
}