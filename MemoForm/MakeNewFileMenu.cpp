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
	//�ٲ� ���� �ִ��� Ȯ��
	if (memoForm->isChanged == true) {
		//�����ϱ�
		//�޼����ڽ� ���
		int ret = memoForm->MessageBox(_T("���泻���� ��������� �����Ͻðڽ��ϱ�?"), _T("�޸���"), MB_YESNOCANCEL);
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
	//������ ���� �����
	delete memoForm->page;
	memoForm->page = new Page;
	memoForm->text = new Text;
	memoForm->row = new Row;
	memoForm->text->Add(memoForm->row);
	memoForm->page->Add(memoForm->text);

	//ĳ���̵�
	memoForm->caret->MoveToCurrent(memoForm);

	//��ũ�� ����
	memoForm->paper->MoveToY(0);
	memoForm->scrollInfo.nPos = memoForm->paper->GetY();

	//������� ����
	memoForm->originalPathName = "";

	memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);

}