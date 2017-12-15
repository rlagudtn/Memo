//CtrlRightArrowKey.h
#ifndef _CTRLRIGHTKEY_H
#define _CTRLRIGHTKEY_H
#include "KeyAction.h"
typedef signed long int Long;
class MemoForm;
class CtrlRightArrowKey :public KeyAction {
public:
	CtrlRightArrowKey();
	CtrlRightArrowKey(const CtrlRightArrowKey& source);
	virtual ~CtrlRightArrowKey();

	void Implement(MemoForm *memoForm);

};
#endif // _CTRLRIGHTKEY_H