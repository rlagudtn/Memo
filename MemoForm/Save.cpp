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
	CStdioFile file;
	CString str;
	if (file.Open(CString(pathName.c_str()), CFile::modeCreate | CFile::modeWrite | CFile::typeText)) {
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
