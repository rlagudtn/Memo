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
	//�ٲ�κ��ִٸ�
	if (memoForm->isChanged == true) {
			//�����ϱ�
			//�޼����ڽ� ���
			int ret =memoForm->MessageBox(_T("���泻���� ��������� �����Ͻðڽ��ϱ�?"), _T("�޸���"), MB_YESNOCANCEL);
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
	//�ҷ�����
	Load load;
	load.WriteToMemo(memoForm);
}