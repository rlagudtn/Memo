//CutString.h
#ifndef _CUTSTRING_H
#define _CUTSTRING_H
#include <string>
#pragma warning(disable:4996)
using namespace std;
class MemoForm;
typedef signed long int Long;
class Text;
class CutString {
public:
	CutString();
	CutString(const CutString& source);
	~CutString();
	string CutText(MemoForm *memoForm, Long startLine, Long startColumn, Long endLine, Long endColumn);
};
#endif // !_CUTSTRING_H
