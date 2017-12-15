//CtrlSaveKey.h
#ifndef _CTRLSAVEKEY_H
#define _CTRLSAVEKEY_H
#include "KeyAction.h"
typedef signed long int Long;
class MemoForm;
class CtrlSaveKey :public KeyAction {
public:
	CtrlSaveKey();
	CtrlSaveKey(const CtrlSaveKey& source);
	virtual ~CtrlSaveKey();

	void Implement(MemoForm *memoForm);

};
#endif // _CTRLCHANGEKEY_H