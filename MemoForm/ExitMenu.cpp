//ExitMenu.cpp
#include "ExitMenu.h"
#include "MemoForm.h"
#include "Save.h"
ExitMenu::ExitMenu() {}
ExitMenu::~ExitMenu() {}

void ExitMenu::Implement(MemoForm *memoForm) {
	CFrameWnd *form = (CFrameWnd*)memoForm;
	if (memoForm->isChanged == true) {
		//�����ϱ�
		//�޼����ڽ� ���
		int ret =memoForm-> MessageBox(_T("���泻���� ��������� �����Ͻðڽ��ϱ�?"), _T("�޸���"), MB_YESNOCANCEL);
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