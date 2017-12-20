//CtrlPrintKey.h
#ifndef _CTRLPRINTKEY_H
#define _CTRLPRINTKEY_H
#include "KeyAction.h"
typedef signed long int Long;
class MemoForm;
class CtrlPrintKey :public KeyAction {
public:
	CtrlPrintKey();
	CtrlPrintKey(const CtrlPrintKey& source);
	virtual ~CtrlPrintKey();

	void Implement(MemoForm *memoForm);

};
#endif // _CTRLPRINTKEY_H