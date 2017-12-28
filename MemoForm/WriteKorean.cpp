//WriteKorean.cpp
#include "WriteKorean.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "DoubleByteCharacter.h"
#include "Caret.h"
#include "GetString.h"
#include "MoveConnectedText.h"
WriteKorean::WriteKorean(){}

WriteKorean::~WriteKorean(){}

void WriteKorean::Write(MemoForm *memoForm,UINT wParam, LONG lParam) {
	memoForm->isChanged = true;
	int nLength = 0;
	char  *wszComp;
	int cxBuffer;
	CClientDC dc(memoForm);
	//dc.SelectObject(memoForm);
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
		
		//화면넘는지에 관한 처리
		GetString getString;
		dc.SelectObject(memoForm->font);

		CSize size = dc.GetTextExtent(CString(getString.SubString(memoForm->row, 0, memoForm->row->GetLength() - 1).c_str()));
		//넘는다면 자동줄바꿈 시켜준다.
		if (size.cx > memoForm->screenWidth) {
			Row *row = memoForm->row;
			MoveConnectedText moveConnectedText;
			moveConnectedText.ChangeLine(memoForm, &dc, memoForm->text->GetCurrent());
			row->Connect();
		}
		//캐럿 이동
		memoForm->caret->MoveToCurrent(memoForm);
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
			
			Long temp = ImmGetCompositionString(hImc, GCS_COMPSTR, NULL, 0);

			if (temp >0) {
				DoubleByteCharacter *doubleByteCharacter_ = new DoubleByteCharacter;
				if (memoForm->row->GetCurrent() < memoForm->row->GetLength() - 1) {
					memoForm->row->TakeIn(memoForm->row->GetCurrent() + 1, doubleByteCharacter_);
				}
				//글의 현재위치가 줄의 길이보다 크거나 같으면
				else if (memoForm->row->GetCurrent() >= memoForm->row->GetLength() - 1) {
					memoForm->row->Add(doubleByteCharacter_);
				}
			}
			
		}

	}
	
	ImmReleaseContext(memoForm->GetSafeHwnd(), hImc);
	
}