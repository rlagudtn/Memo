//CStatusButton.h
#ifndef _CSTATUSBUTTON_H
#define _CSTATUSBUTTON_H
#include <afxwin.h>	

class CStatusButton :public CButton {
public:
	CStatusButton();
	~CStatusButton();
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
};
#endif // _CSTATUSBUTTON_H
