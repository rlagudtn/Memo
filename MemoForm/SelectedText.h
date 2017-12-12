//SelectedText.h
#ifndef _SELECTEDTEXT_H
#define _SELECTEDTEXT_H
#include "Visitor.h"
#include <string>	
using namespace std;
typedef signed long int Long;
class CDC;
class Text;
class Row;
class SingleByteCharacter;
class DoubleByteCharacter;
class SelectedText:public Visitor {
public:
	SelectedText();
	SelectedText(CDC *pdc,Long paperX,Long paperY);
	~SelectedText();
	void SetTextPosition(Long startRow, Long startColumn, Long endRow, Long endColumn);
	void SetInfoPosition(CDC *dc,bool isPaint,Long paperX, Long paperY);
	Long GetStartRow() const;
	Long GetStartColumn() const;
	Long GetEndRow() const;
	Long GetEndColumn() const;
	Long GetStartX() const;
	Long GetStartY() const;
	Long GetEndX() const;
	Long GetEndY() const;
	string& GetStr() const;
	string& GetBuffer() const;
public:
	void Visit(Text *text);
	void Visit(Row *row);
	void Visit(SingleByteCharacter *singleByteCharacter);
	void Visit(DoubleByteCharacter *doubleByteCharacter);

private:
	bool isPaint;
	Long startRow;
	Long startColumn;
	Long endRow;
	Long endColumn;

	Long startX;
	Long startY;
	Long endX;
	Long endY;

	Long paperX;
	Long paperY;
	string str;
	Long i;
	CDC *pdc;
	Long top;//top이 visitor 특성때문에 초기화되므로 여기로 설정
	Long font;//폰트 사이즈
	string buffer;
};
inline Long SelectedText::GetStartRow() const {
	return this->startRow;
}
inline Long SelectedText::GetStartColumn() const {
	return this->startColumn;
}
inline Long SelectedText::GetEndRow() const {
	return this->endRow;
}
inline Long SelectedText::GetEndColumn() const {
	return this->endColumn;
}
inline Long SelectedText::GetStartX() const {
	return this->startX;
}
inline Long SelectedText::GetStartY() const {
	return this->startY;
}
inline Long SelectedText::GetEndX() const {
	return this->endX;
}
inline Long SelectedText::GetEndY() const {
	return this->endY;
}
inline string& SelectedText::GetStr() const {
	return const_cast<string&>(this->str);
}
inline string& SelectedText::GetBuffer() const {
	return const_cast<string&>(this->buffer);
}
#endif // _SELECTEDTEXT_H
