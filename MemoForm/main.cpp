#include "CopyToMemo.h"
#include "Page.h"	
#include "PageStack.h"
#include "Text.h"
#include "Row.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include <iostream>
#include <string>
//�׽�Ʈ�Ұ͵�
#include "SelectedText.h"
#include "GetString.h"
using namespace std;
int main(int argc, char *argv[]) {
	Page *page = new Page;
	PageStack *pageStack = new PageStack(2);
	Text *text = new Text;
	Row *row = new Row;
	DoubleByteCharacter *doubleByteCharacter1 = new DoubleByteCharacter("��");
	row->Add(doubleByteCharacter1);
	DoubleByteCharacter *doubleByteCharacter2 = new DoubleByteCharacter("��");
	row->Add(doubleByteCharacter2);
	DoubleByteCharacter *doubleByteCharacter3 = new DoubleByteCharacter("��");
	row->Add(doubleByteCharacter3);
	DoubleByteCharacter *doubleByteCharacter4 = new DoubleByteCharacter("��");
	row->Add(doubleByteCharacter4);
	DoubleByteCharacter *doubleByteCharacter5 = new DoubleByteCharacter("��");
	row->Add(doubleByteCharacter5);
	DoubleByteCharacter *doubleByteCharacter6 = new DoubleByteCharacter("��");
	row->Add(doubleByteCharacter6);
	SingleByteCharacter *singleByteCharacter1 = new SingleByteCharacter('\r');
	row->Add(singleByteCharacter1);
	SingleByteCharacter *singleByteCharacter2 = new SingleByteCharacter('\n');
	row->Add(singleByteCharacter2);
	text->Add(row);

	Row *row1 = new Row;
	DoubleByteCharacter *doubleByteCharacter11 = new DoubleByteCharacter("��");
	row1->Add(doubleByteCharacter11);
	DoubleByteCharacter *doubleByteCharacter21 = new DoubleByteCharacter("��");
	row1->Add(doubleByteCharacter21);
	DoubleByteCharacter *doubleByteCharacter31 = new DoubleByteCharacter("��");
	row1->Add(doubleByteCharacter31);
	DoubleByteCharacter *doubleByteCharacter41 = new DoubleByteCharacter("��{");
	row1->Add(doubleByteCharacter41);
	DoubleByteCharacter *doubleByteCharacter51 = new DoubleByteCharacter("��");
	row1->Add(doubleByteCharacter51);
	DoubleByteCharacter *doubleByteCharacter61 = new DoubleByteCharacter("��");
	row1->Add(doubleByteCharacter61);
	SingleByteCharacter *singleByteCharacter11 = new SingleByteCharacter('\r');
	row1->Add(singleByteCharacter11);
	SingleByteCharacter *singleByteCharacter21 = new SingleByteCharacter('\n');
	row1->Add(singleByteCharacter21);
	text->Add(row1);
	//cout << text->GetLength();
	row->Move(-1);

	pageStack->Push(page);
	cout << pageStack->GetTop() << endl;
	
	//�ϳ� �� �߰�
	Page *page1 = new Page;
	pageStack->Push(page1);
	cout << pageStack->GetTop() << endl;

	Page *page2 = new Page(*page1);
	

	return 0;
}