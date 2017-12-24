//OpenMenu.cpp
#include "OpenMenu.h"
#include "MemoForm.h"
#include < afxdlgs.h>
#include "Page.h"
#include "Text.h"
#include "Row.h"
#include "Load.h"
OpenMenu::OpenMenu() {}
OpenMenu::~OpenMenu() {}

void OpenMenu::Implement(MemoForm *memoForm) {
	//불러오기
	CFileDialog dlg(true, "*.txt", NULL, OFN_FILEMUSTEXIST, "text Files(*.txt)|*.txt|", NULL);
	if (dlg.DoModal() == IDOK) {
		if (memoForm->page != NULL) {
			delete memoForm->page;
		}
		memoForm->page = new Page;
		memoForm->text = new Text;
		memoForm->page->Add(memoForm->text);
		CStdioFile file;
		CString str;
		CClientDC dc(memoForm);
		memoForm->originalPathName = dlg.GetPathName();
		if (file.Open(dlg.GetPathName(), CFile::modeRead)) {
			while (file.ReadString(str)) {
				if (str != '\f') {

					Load load(&dc, memoForm->screenWidth, (LPCTSTR)str);
					memoForm->text->Accept(&load);
				}
				else {
					memoForm->text->Move(0);
					Text *text = new Text;
					memoForm->page->Add(text);
					memoForm->text = dynamic_cast<Text*>(memoForm->page->GetAt(memoForm->page->GetCurrent()));
				}
			}
			file.Close();
		}
		memoForm->text = dynamic_cast<Text*>(memoForm->page->Move(0));
		memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(0));
		memoForm->row->Move(-1);
		memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
	}
}