//CtrlAllKey.h
#ifndef _CTRLALLKEY_H
#define _CTRLALLKEY_H
#include "KeyAction.h"
typedef signed long int Long;
class MemoForm;
class CtrlAllKey :public KeyAction {
public:
	CtrlAllKey();
	CtrlAllKey(const CtrlAllKey& source);
	virtual ~CtrlAllKey();

	void Implement(MemoForm *memoForm);

};
#endif // _SHIFTALLKEY_H