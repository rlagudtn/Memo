//RightKeyArrow.h
#ifndef _UPARROWKEY_H
#define _UPARROWKEY_H
#include "KeyAction.h"
typedef signed long int Long;
class MemoForm;
class UpArrowKey :public KeyAction {
public:
	UpArrowKey();
	UpArrowKey(const UpArrowKey& source);
	virtual ~UpArrowKey();

	void Implement(MemoForm *memoForm);

};
#endif // _UPARROWKEY_H