//RightKeyArrow.h
#ifndef _RIGHTARROWKEY_H
#define _RIGHTARROWKEY_H
#include "KeyAction.h"
typedef signed long int Long;
class MemoForm;
class RightArrowKey :public KeyAction {
public:
	RightArrowKey();
	RightArrowKey(const RightArrowKey& source);
	virtual ~RightArrowKey();

	void Implement(MemoForm *memoForm);

};
#endif // _RIGHTARROWKEY_H