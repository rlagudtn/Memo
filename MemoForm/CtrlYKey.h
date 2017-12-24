//CtrlYKey.h
#ifndef _CTRLYKEY_H
#define _CTRLYKEY_H
#include "KeyAction.h"
typedef signed long int Long;
class MemoForm;
class CtrlYKey :public KeyAction {
public:
	CtrlYKey();
	CtrlYKey(const CtrlYKey& source);
	virtual ~CtrlYKey();

	void Implement(MemoForm *memoForm);

};
#endif // _CTRLYKEY_H