//MakeNewFileMenu.cpp
#include "MakeNewFileMenu.h"
#include "MemoForm.h"
#include "Page.h"
#include "Text.h"
#include "Row.h"
#include "SingleByteCharacter.h"
#include "Caret.h"
#include "Paper.h"
#include "Save.h"
MakeNewFileMenu::MakeNewFileMenu() {}
MakeNewFileMenu::~MakeNewFileMenu() {}

void MakeNewFileMenu::Implement(MemoForm *memoForm) {
	//바뀐 것이 있는지 확인
	if (memoForm->isChanged == true) {
		//저장하기
		//메세지박스 출력
		int ret = memoForm->MessageBox(_T("변경내용을 제목없음에 저장하시겠습니까?"), _T("메모장"), MB_YESNOCANCEL);
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
		}
	}
	//페이지 새로 만들기
	delete memoForm->page;
	memoForm->page = new Page;
	memoForm->text = new Text;
	memoForm->row = new Row;
	memoForm->text->Add(memoForm->row);
	memoForm->page->Add(memoForm->text);

	//캐럿이동
	memoForm->caret->MoveToCurrent(memoForm);

	//스크롤 갱신
	memoForm->paper->MoveToY(0);
	memoForm->scrollInfo.nPos = memoForm->paper->GetY();

	//저장장소 갱신
	memoForm->originalPathName = "";

	memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);

}