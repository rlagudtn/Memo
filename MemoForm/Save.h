//Save.h
#ifndef _SAVE_H
#define _SAVE_H
#include <string>
#pragma warning(disable:4996)
using namespace std;
class MemoForm;
class Save {
public:
	Save();
	~Save();

	void SaveMemo(MemoForm *memoForm,string pathName);
};
#endif // _SAVE_H