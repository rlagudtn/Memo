//OpenMenu.cpp
#include "OpenMenu.h"
#include "MemoForm.h"
#include < afxdlgs.h>
#include "Page.h"
#include "Text.h"
#include "Row.h"
#include "Load.h"
#include "Save.h"
OpenMenu::OpenMenu() {}
OpenMenu::~OpenMenu() {}

void OpenMenu::Implement(MemoForm *memoForm) {
	//바뀐부분있다면
	if (memoForm->isChanged == true) {
			//저장하기
			//메세지박스 출력
			int ret =memoForm->MessageBox(_T("변경내용을 제목없음에 저장하시겠습니까?"), _T("메모장"), MB_YESNOCANCEL);
			if (ret == IDYES) {
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
			}
			
	}
	//불러오기
	Load load;
	load.WriteToMemo(memoForm);
}