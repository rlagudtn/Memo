//WriteKorean.cpp
#include "WriteKorean.h"
#include "MemoForm.h"
#include "Row.h"
#include "DoubleByteCharacter.h"
#include "Caret.h"
WriteKorean::WriteKorean(){}

WriteKorean::~WriteKorean(){}

void WriteKorean::Write(MemoForm *memoForm,UINT wParam, LONG lParam) {
	int nLength = 0;
	char  *wszComp;
	int cxBuffer;
	CClientDC dc(MemoForm);
	HIMC hImc = ImmGetContext(memoForm->GetSafeHwnd());
	HDC hdc = ::GetDC(memoForm->GetSafeHwnd());
	if (lParam&GCS_COMPSTR) {
		nLength = ImmGetCompositionString(hImc, GCS_COMPSTR, NULL, 0);
		wszComp = new char[nLength + 1];
		memset(wszComp, 0, nLength + 1);
		if (nLength > 0) {
			//글자 적기
			ImmGetCompositionString(hImc, GCS_COMPSTR, wszComp, nLength);

			DoubleByteCharacter *doubleByteCharacter = new DoubleByteCharacter((LPSTR)(LPCTSTR)wszComp);
			memoForm->row->Modify(memoForm->row->GetCurrent(), doubleByteCharacter);

		}
		//backspace
		else {
			memoForm->row->Delete(memoForm->row->GetCurrent());
		}
	}
	else if (lParam&GCS_RESULTSTR) {
		nLength = ImmGetCompositionString(hImc, GCS_RESULTSTR, NULL, 0);
		wszComp = new char[nLength + 1];
		memset(wszComp, 0, nLength + 1);

		if (nLength > 0) {

			//글자 적기
			ImmGetCompositionString(hImc, GCS_RESULTSTR, wszComp, nLength);
			DoubleByteCharacter *doubleByteCharacter = new DoubleByteCharacter((LPSTR)(LPCTSTR)wszComp);
			memoForm->row->Modify(memoForm->row->GetCurrent(), doubleByteCharacter);
			//다음칸에 넣어질 칸을 넣는다
			DoubleByteCharacter *doubleByteCharacter_ = new DoubleByteCharacter;
			if (memoForm->row->GetCurrent() < memoForm->row->GetLength() - 1) {
				memoForm->row->TakeIn(memoForm->row->GetCurrent() + 1, doubleByteCharacter_);
			}
			//글의 현재위치가 줄의 길이보다 크거나 같으면
			else if (memoForm->row->GetCurrent() >= memoForm->row->GetLength() - 1) {
				memoForm->row->Add(doubleByteCharacter_);
			}
			memoForm->caret->MoveToCurrent(memoForm);
		}

	}
	ImmReleaseContext(memoForm->GetSafeHwnd(), hImc);
	
}