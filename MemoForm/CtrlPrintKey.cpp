//CtrlPrintKey.cpp
#include "CtrlPrintKey.h"
#include "MemoForm.h"
#include <afxwin.h>
CtrlPrintKey::CtrlPrintKey() {

}
CtrlPrintKey::CtrlPrintKey(const CtrlPrintKey& source) {

}
CtrlPrintKey::~CtrlPrintKey() {

}

void CtrlPrintKey::Implement(MemoForm *memoForm) {
	CPrintDialog dlg(FALSE, PD_ALLPAGES | PD_COLLATE | PD_NOPAGENUMS |
		PD_HIDEPRINTTOFILE);
	if (dlg.DoModal() == IDOK)
	{
		// If the collate check box is selected, then GetCopies() will return
		// the number of copies printed. Otherwise, GetCopies() always 
		// returns 1. Then, the number of copies printed can be found from the
		// DEVMODE structure of the printing device.
		if (dlg.PrintCollate())
		{
			int num = dlg.GetCopies();
			TRACE(_T("Number of copies printed = %d\n"), num);
		}
		else
		{
			LPDEVMODE devmode = dlg.GetDevMode();
			TRACE(_T("Number of copies printed = %d\n"), devmode->dmCopies);
		}
	}
}