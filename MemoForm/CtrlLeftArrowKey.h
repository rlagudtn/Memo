//CtrlLeftArrowKey.h
#ifndef _CTRLLEFTARROWKEY_H
#define _CTRLLEFTARROWKEY_H
#include "KeyAction.h"
typedef signed long int Long;
class MemoForm;
class CtrlLeftArrowKey :public KeyAction {
public:
	CtrlLeftArrowKey();
	CtrlLeftArrowKey(const CtrlLeftArrowKey& source);
	virtual ~CtrlLeftArrowKey();

	void Implement(MemoForm *memoForm);

};
#endif // _CTRLLEFTARROWKEY_H