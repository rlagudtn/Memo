//DeleteKey.h
#ifndef _DELETEKEY_H
#define _DELETEKEY_H
#include "KeyAction.h"
typedef signed long int Long;
class MemoForm;
class DeleteKey :public KeyAction {
public:
	DeleteKey();
	DeleteKey(const DeleteKey& source);
	virtual ~DeleteKey();

	void Implement(MemoForm *memoForm);

};
#endif // _SHIFTALLKEY_H