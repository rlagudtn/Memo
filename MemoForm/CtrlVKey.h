//CtrlVKey.h
#ifndef _CTRLvKEY_H
#define _CTRLVKEY_H
#include "KeyAction.h"
typedef signed long int Long;
class MemoForm;
class CtrlVKey :public KeyAction {
public:
	CtrlVKey();
	CtrlVKey(const CtrlVKey& source);
	virtual ~CtrlVKey();

	void Implement(MemoForm *memoForm);

};
#endif // _CTRLVKEY_H