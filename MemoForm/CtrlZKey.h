//CtrlZKey.h
#ifndef _CTRLZKEY_H
#define _CTRLZKEY_H
#include "KeyAction.h"
typedef signed long int Long;
class MemoForm;
class CtrlZKey :public KeyAction {
public:
	CtrlZKey();
	CtrlZKey(const CtrlZKey& source);
	virtual ~CtrlZKey();

	void Implement(MemoForm *memoForm);

};
#endif // _CTRLZKEY_H