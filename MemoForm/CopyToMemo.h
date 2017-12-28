//CopyToMemo.h
#ifndef _COPYTOMEMO_H
#define _COPYTOMEMO_H
#include <string>	
#pragma warning(disable:4996)
using namespace std;
class MemoForm;
class CopyToMemo {
public:
	CopyToMemo();
	~CopyToMemo();
	void WriteToMemo(MemoForm *memoForm, string str);
};
#endif // _COPYTOMEMO_H
