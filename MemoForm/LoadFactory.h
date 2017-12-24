//LoadFactory.h
#ifndef _LOADFACTORY_H
#define _LOADFACTORY_H
#include <string>
#pragma warning(disable:4996)
using namespace std;
class MemoForm;
class LoadFactory {
public:
	LoadFactory();
	~LoadFactory();
	void Load(MemoForm *memoForm, string text);
};
#endif // !_LOADFACTORY_H
