//RightKeyArrow.h
#ifndef _DOWNARROWKEY_H
#define _DOWNARROWKEY_H
#include "KeyAction.h"
typedef signed long int Long;
class MemoForm;
class DownArrowKey :public KeyAction {
public:
	DownArrowKey();
	DownArrowKey(const DownArrowKey& source);
	virtual ~DownArrowKey();

	void Implement(MemoForm *memoForm);

};
#endif // _UPARROWKEY_H