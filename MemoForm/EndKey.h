//EndKey.h
#ifndef _ENDKEY_H
#define _ENDKEY_H
#include "KeyAction.h"
typedef signed long int Long;
class MemoForm;
class EndKey :public KeyAction {
public:
	EndKey();
	EndKey(const EndKey& source);
	virtual ~EndKey();

	void Implement(MemoForm *memoForm);

};
#endif // _ENDKEY_H