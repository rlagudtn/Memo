//CtrlCopyKey.h
#ifndef _CTRLCOPYKEY_H
#define _CTRLCOPYKEY_H
#include "KeyAction.h"
typedef signed long int Long;
class MemoForm;
class CtrlCopyKey :public KeyAction {
public:
	CtrlCopyKey();
	CtrlCopyKey(const CtrlCopyKey& source);
	virtual ~CtrlCopyKey();

	void Implement(MemoForm *memoForm);

};
#endif // _CTRLCOPYKEY_H