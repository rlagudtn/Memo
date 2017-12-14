//CtrlFindKey.h
#ifndef _CTRLFINDKEY_H
#define _CTRLFINDKEY_H
#include "KeyAction.h"
typedef signed long int Long;
class MemoForm;
class CtrlFindKey :public KeyAction {
public:
	CtrlFindKey();
	CtrlFindKey(const CtrlFindKey& source);
	virtual ~CtrlFindKey();

	void Implement(MemoForm *memoForm);

};
#endif // _SHIFTALLKEY_H