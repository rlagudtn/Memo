//FindCurrentByString.h
#ifndef _FINDCURRENTBYSTRING_H
#define _FINDCURRENTBYSTRING_H
#include <string>
#include <afxwin.h>
#pragma warning(disable:4996)
using namespace std;
typedef signed long int Long;
class FindCurrentByString {
public:
	FindCurrentByString();
	FindCurrentByString(const FindCurrentByString& source);
	~FindCurrentByString();
	void MoveToCurrent(CDC *dc,string text,Long screenWidth);
	Long GetTextIndex() const;
	Long GetRowIndex() const;
private:
	Long textIndex;
	Long rowIndex;
};
inline Long FindCurrentByString::GetTextIndex() const {
	return this->textIndex;
}
inline Long FindCurrentByString::GetRowIndex() const {
	return this->rowIndex;
}
#endif // _FINDCURRENTBYSTRING_H
