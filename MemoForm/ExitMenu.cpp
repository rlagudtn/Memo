//ExitMenu.cpp
#include "ExitMenu.h"
#include "MemoForm.h"
#include "Save.h"
ExitMenu::ExitMenu() {}
ExitMenu::~ExitMenu() {}

void ExitMenu::Implement(MemoForm *memoForm) {
	CFrameWnd *form = (CFrameWnd*)memoForm;
	if (memoForm->isChanged == true) {
		//저장하기
		//메세지박스 출력
		int ret =memoForm-> MessageBox(_T("변경내용을 제목없음에 저장하시겠습니까?"), _T("메모장"), MB_YESNOCANCEL);
		if (ret == IDYES) {
			CString savePath = memoForm->originalPathName;
			if (memoForm->originalPathName == "") {
				CFileDialog dlg(FALSE, "*.txt", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "text Files(*.txt)|*.txt|");
				if (dlg.DoModal() == IDOK) {
					savePath = dlg.GetPathName();
				}
			}
			Save save;
			save.SaveMemo(memoForm, (LPCTSTR)savePath);
			memoForm->PostMessageA(WM_CLOSE);

		}
		else if (ret == IDNO) {
			if (memoForm->page != NULL) {
				delete memoForm->page;
			}
			memoForm->PostMessageA(WM_CLOSE);
		}
	}
	else {
		memoForm->PostMessageA(WM_CLOSE);
	}
}