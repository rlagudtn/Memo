//Load.h
#ifndef _LOAD_H
#define _LOAD_H
#include <string>	
#pragma warning(disable:4996)
using namespace std;
class MemoForm;
typedef signed long int Long;
class Load {
public:
	Load();
	~Load();
	void WriteToMemo(MemoForm *memoForm);
};
#endif // _LOAD_H
