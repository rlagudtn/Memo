//SelectedText.h
#ifndef _SELECTEDTEXT_H
#define _SELECTEDTEXT_H
#include <string>
#pragma warning (disable:4996)
using namespace std;
typedef signed long int Long;
class MemoForm;
class Text;
class Row;
class SingleByteCharacter;
class DoubleByteCharacter;
class CDC;
class SelectedText {
public:
	SelectedText();
	SelectedText(const SelectedText& source);
	~SelectedText();
	string Select(MemoForm *memoForm,Long startLine, Long startColumn, Long endLine, Long endColumn);
	void EraseSelectedText(MemoForm *memoForm);
	bool SetAgainPos(Long previousLine, Long previousColumn, Long currentLine, Long currentColumn);
	SelectedText& operator=(const SelectedText& source);

	void DrawUnderLine(MemoForm *memoForm,CDC *dc);
	Long GetStartLine() const;
	Long GetStartColumn() const;
	Long GetEndLine() const;
	Long GetEndColumn() const;
	string& GetBuffer() const;
private:
	
	Long startLine;
	Long startColumn;
	Long endLine;
	Long endColumn;
	string buffer;
};
inline Long SelectedText::GetStartLine() const {
	return this->startLine;
}
inline Long SelectedText::GetStartColumn() const {
	return this->startColumn;
}
inline Long SelectedText::GetEndLine() const {
	return this->endLine;
}
inline Long SelectedText::GetEndColumn() const {
	return this->endColumn;
}
inline string& SelectedText::GetBuffer() const {
	return const_cast<string&>(this->buffer);
}
#endif // _SELECTEDTEXT_H
