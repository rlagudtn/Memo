//ShiftAllKey.h
#ifndef _SHIFTALLKEY_H
#define _SHIFTALLKEY_H
#include "KeyAction.h"
typedef signed long int Long;
class MemoForm;
class ShiftAllKey :public KeyAction {
public:
	ShiftAllKey();
	ShiftAllKey(const ShiftAllKey& source);
	virtual ~ShiftAllKey();

	void Implement(MemoForm *memoForm);

};
#endif // _SHIFTALLKEY_H