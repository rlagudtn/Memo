//Save.cpp
#include "Save.h"
#include "MemoForm.h"
#include "Page.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "ConnectedInfo.h"
#include "GetString.h"

Save::Save() {

}
Save::~Save(){}

void Save::SaveMemo(MemoForm *memoForm,string pathName) {
	
	CStdioFile file;
	CString saveString;
	if (file.Open(CString(pathName.c_str()), CFile::modeCreate | CFile::modeWrite )) {
			Long i = 0;
			CString saveString;
			while (i < memoForm->page->GetLength()) {
				Text *text = dynamic_cast<Text*>(memoForm->page->GetAt(i));
				Long j = 0;
				while (j < text->GetLength()) {
					Row *row = dynamic_cast<Row*>(text->GetAt(j));
					ConnectedInfo connectedInfo;
					Long lastConnectedLine = connectedInfo.GetEndOfConnected(text, j);
					Long k = j;
					saveString = "";
					while (k <= lastConnectedLine) {
						Row *connectedRow = dynamic_cast<Row*>(text->GetAt(k));
						GetString getString;
						saveString += CString(getString.SubString(connectedRow, 0, connectedRow->GetLength() - 1).c_str());
						k++;
					}
					file.WriteString(saveString + "\n");
					j = lastConnectedLine + 1;
				}
				//해당 페이지의 텍스트를 다 저장하고,,
				if (i < memoForm->page->GetLength() - 1) {
					file.WriteString("\f\n");
				}
				i++;
			}
		file.Close();
	}
}
