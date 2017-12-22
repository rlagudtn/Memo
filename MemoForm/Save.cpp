//Save.cpp
#include "Save.h"
#include "MemoForm.h"
#include "Page.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"

#include "GetString.h"

Save::Save() {

}
Save::~Save(){}

void Save::SaveMemo(MemoForm *memoForm,string pathName) {
	CString savePath = CString(pathName.c_str());
	if (savePath== "") {
		CFileDialog dlg(FALSE, "*.txt", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "text Files(*.txt)|*.txt|");
		if (dlg.DoModal() == IDOK) {
			savePath = dlg.GetPathName();
		}
	}
	CStdioFile file;
	CString str;
	if (file.Open(savePath, CFile::modeCreate | CFile::modeWrite | CFile::typeText)) {
		Long i = 0;
		Text *text;
		Row *row;
		CString str;
		while (i < memoForm->page->GetLength()) {
			text = dynamic_cast<Text*>(memoForm->page->GetAt(i));
			Long j = 0;
			while (j <text->GetLength()) {
				row = dynamic_cast<Row*>(text->GetAt(j));
				GetString getString;
				str = CString(getString.SubString(row, 0, row->GetLength() - 1).c_str());
				file.WriteString(str + "\n");
				j++;
			}
			if (i <memoForm->page->GetLength() - 1) {
				file.WriteString("\f\n");
			}
			i++;
		}
		file.Close();
	}
}
