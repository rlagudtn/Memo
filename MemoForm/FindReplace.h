//FindReplace.h
#ifndef _FINDREPLACE_H
#define _FINDREPLACE_H
class MemoForm;
class FindReplace {
public:
	FindReplace();
	~FindReplace();
	void FindString(MemoForm *memoForm);
	void ReplaceString(MemoForm *memoForm);
	void ReplaceAll(MemoForm *memoForm);

};
#endif // _FINDREPLACE_H
