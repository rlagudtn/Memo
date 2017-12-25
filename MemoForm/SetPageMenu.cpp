//SetPageMenu.cpp
#include "SetPageMenu.h"
#include "MemoForm.h"
SetPageMenu::SetPageMenu() {}
SetPageMenu::~SetPageMenu() {}

void SetPageMenu::Implement(MemoForm *memoForm) {
	if (memoForm->pageSetUpDialog == NULL) {
		memoForm->pageSetUpDialog = new CPageSetupDialog(PSD_INTHOUSANDTHSOFINCHES | PSD_MARGINS | PSD_ENABLEPAGEPAINTHOOK, memoForm);
		// Initialize margins
		memoForm->pageSetUpDialog->m_psd.rtMargin.top = 1000;
		memoForm->pageSetUpDialog->m_psd.rtMargin.left = 1250;
		memoForm->pageSetUpDialog->m_psd.rtMargin.right = 1250;
		memoForm->pageSetUpDialog->m_psd.rtMargin.bottom = 1000;
	}
	

	if (IDOK == memoForm->pageSetUpDialog->DoModal())
	{
		// Propagate changes to the app
		AfxGetApp()->SelectPrinter(memoForm->pageSetUpDialog->m_psd.hDevNames, memoForm->pageSetUpDialog->m_psd.hDevMode);
	}
	
}