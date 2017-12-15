//CtrlXKey.h
#ifndef _CTRLXKEY_H
#define _CTRLXKEY_H
#include "KeyAction.h"
typedef signed long int Long;
class MemoForm;
class CtrlXKey :public KeyAction {
public:
	CtrlXKey();
	CtrlXKey(const CtrlXKey& source);
	virtual ~CtrlXKey();

	void Implement(MemoForm *memoForm);

};
#endif // _CTRLXKEY_H