//CurrentPosition.h
#ifndef _CURRENTPOSITION_H
#define _CURRENTPOSITION_H
#include <string>
#include <afxwin.h>
#pragma warning(disable:4996)
using namespace std;
typedef signed long int Long;
class MemoForm;
class CurrentPosition {
public:
	CurrentPosition();
	CurrentPosition(const CurrentPosition& source);
	~CurrentPosition();
	void SaveCurrent(MemoForm *memoForm);
	void MoveToCurrent(MemoForm *memoForm);
	Long GetTextIndex() const;
	Long GetRowIndex() const;
private:
	Long textIndex;
	Long rowIndex;
};
inline Long CurrentPosition::GetTextIndex() const {
	return this->textIndex;
}
inline Long CurrentPosition::GetRowIndex() const {
	return this->rowIndex;
}
#endif // _CURRENTPOSITION_H
