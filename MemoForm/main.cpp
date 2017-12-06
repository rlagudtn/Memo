#include "CopyToMemo.h"
#include "Text.h"
#include "Row.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include <iostream>
#include <string>
//테스트할것들
#include "EraseSelectedText.h" 
#include "SelectedText.h"
#include "GetString.h"
using namespace std;
int main(int argc, char *argv[]) {
	Text *text = new Text;
	Row *row = new Row;
	DoubleByteCharacter *doubleByteCharacter1 = new DoubleByteCharacter("문");
	row->Add(doubleByteCharacter1);
	DoubleByteCharacter *doubleByteCharacter2 = new DoubleByteCharacter("제");
	row->Add(doubleByteCharacter2);
	DoubleByteCharacter *doubleByteCharacter3 = new DoubleByteCharacter("가");
	row->Add(doubleByteCharacter3);
	DoubleByteCharacter *doubleByteCharacter4 = new DoubleByteCharacter("생");
	row->Add(doubleByteCharacter4);
	DoubleByteCharacter *doubleByteCharacter5 = new DoubleByteCharacter("겼");
	row->Add(doubleByteCharacter5);
	DoubleByteCharacter *doubleByteCharacter6 = new DoubleByteCharacter("다");
	row->Add(doubleByteCharacter6);
	SingleByteCharacter *singleByteCharacter1 = new SingleByteCharacter('\r');
	row->Add(singleByteCharacter1);
	SingleByteCharacter *singleByteCharacter2 = new SingleByteCharacter('\n');
	row->Add(singleByteCharacter2);
	text->Add(row);

	Row *row1 = new Row;
	DoubleByteCharacter *doubleByteCharacter11 = new DoubleByteCharacter("문");
	row1->Add(doubleByteCharacter11);
	DoubleByteCharacter *doubleByteCharacter21 = new DoubleByteCharacter("제");
	row1->Add(doubleByteCharacter21);
	DoubleByteCharacter *doubleByteCharacter31 = new DoubleByteCharacter("가");
	row1->Add(doubleByteCharacter31);
	DoubleByteCharacter *doubleByteCharacter41 = new DoubleByteCharacter("없");
	row1->Add(doubleByteCharacter41);
	DoubleByteCharacter *doubleByteCharacter51 = new DoubleByteCharacter("었");
	row1->Add(doubleByteCharacter51);
	DoubleByteCharacter *doubleByteCharacter61 = new DoubleByteCharacter("다");
	row1->Add(doubleByteCharacter61);
	SingleByteCharacter *singleByteCharacter11 = new SingleByteCharacter('\r');
	row1->Add(singleByteCharacter11);
	SingleByteCharacter *singleByteCharacter21 = new SingleByteCharacter('\n');
	row1->Add(singleByteCharacter21);
	text->Add(row1);
	cout << text->GetLength();
	row->Move(-1);
	//test
	SelectedText selectedText;
	selectedText.SetTextPosition(0, row->GetCurrent()+1, 0, row->GetLength()-1);
	EraseSelectedText eraseSelectedText(selectedText.GetStartRow(), selectedText.GetStartColumn(), selectedText.GetEndRow(), selectedText.GetEndColumn());
	text->Accept(&eraseSelectedText);
	Long i = 0;
	string str;
	Character *character;
	while (i < text->GetLength() ) {
		Row *row_ = dynamic_cast<Row*>(text->GetAt(i));
		Long j = 0;
		while (j < row_->GetLength()) {
			character = dynamic_cast<Character*>(row_->GetAt(j));
			if (dynamic_cast<SingleByteCharacter*>(character)) {
				str += dynamic_cast<SingleByteCharacter*>(character)->GetAlphabet();
			}
			else if (dynamic_cast<DoubleByteCharacter*>(character)) {
				str += dynamic_cast<DoubleByteCharacter*>(character)->GetAlphabet();
			}
			j++;
		}
		cout << str<<endl;
		str = "";
		i++;
	}
	str = "";
	
	return 0;
}