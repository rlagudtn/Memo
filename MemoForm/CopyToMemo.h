//CopyToMemo.h
#ifndef _COPYTOMEMO_H
#define _COPYTOMEMO_H
#include "Visitor.h"
#include <string>	
#pragma warning(disable:4996)
using namespace std;
typedef signed long int Long;
class Text;
class Row;
class SingleByteCharacter;
class DoubleByteCharacter;
class CDC;
class CopyToMemo :public Visitor {
public:
	CopyToMemo();
	CopyToMemo(CDC *pdc, Long screenWidth,string str);
	~CopyToMemo();
	void Visit(Text *text);
	void Visit(Row *row);
	void Visit(SingleByteCharacter *singleByteCharacter);
	void Visit(DoubleByteCharacter *doubleByteCharacter);
	string& GetStr() const;
	bool GetIfMakeRow() const;
private:
	CDC *pdc;
	Long screenWidth;

	string str;//���� ���ڿ�
	string currentString;//���� ���� ���ڿ�
	string tempChar;//�ڵ����� �ٹٲ� �Ҷ� �ӽ������ϴ°�
	bool ifMakeRow;//\r\nó��
	bool ifChangeRow;//�ڵ����� �ٹٲ� ó��

	Long stringIndex;
};
inline string& CopyToMemo::GetStr() const {
	return const_cast<string&>(this->str);
}
inline bool CopyToMemo::GetIfMakeRow() const {
	return this->ifMakeRow;
}

#endif // !_COPYTOMEMO_H
