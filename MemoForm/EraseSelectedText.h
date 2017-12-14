//EraseSelectedText.h
#ifndef _ERASESELECTEDTEXT_H
#define _ERASESELECTEDTEXT_H
#include "Visitor.h"
#include <string>	
#pragma warning(disable:4996)
using namespace std;
typedef signed long int Long;
class CDC;
class Text;
class Row;
class SingleByteCharacter;
class DoubleByteCharacter;
class EraseSelectedText :public Visitor {
public:
	EraseSelectedText();
	EraseSelectedText( Long startRow, Long startColumn, Long endRow, Long endColumn);
	~EraseSelectedText();

	Long GetStartLine() const;
	Long GetStartColumn() const;
	Long GetEndLine() const;
	Long GetEndColumn() const;
	
public:
	void Visit(Text *text);
	void Visit(Row *row);
	void Visit(SingleByteCharacter *singleByteCharacter);
	void Visit(DoubleByteCharacter *doubleByteCharacter);

private:
	Long startRow;
	Long startColumn;
	Long endRow;
	Long endColumn;

	Long i;
	bool ifEraseRow;

	string str;
};
inline Long EraseSelectedText::GetStartLine() const {
	return this->startRow;
}
inline Long EraseSelectedText::GetStartColumn() const {
	return this->startColumn;
}
inline Long EraseSelectedText::GetEndLine() const {
	return this->endRow;
}
inline Long EraseSelectedText::GetEndColumn() const {
	return this->endColumn;
}
#endif // _ERASETEXT_H
