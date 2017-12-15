//CtrlChangeKey.h
#ifndef _CTRLCHANGEKEY_H
#define _CTRLCHANGEKEY_H
#include "KeyAction.h"
typedef signed long int Long;
class MemoForm;
class CtrlChangeKey :public KeyAction {
public:
	CtrlChangeKey();
	CtrlChangeKey(const CtrlChangeKey& source);
	virtual ~CtrlChangeKey();

	void Implement(MemoForm *memoForm);

};
#endif // _CTRLCHANGEKEY_H