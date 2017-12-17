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
			//���� ����
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

			//���� ����
			ImmGetCompositionString(hImc, GCS_RESULTSTR, wszComp, nLength);
			DoubleByteCharacter *doubleByteCharacter = new DoubleByteCharacter((LPSTR)(LPCTSTR)wszComp);
			memoForm->row->Modify(memoForm->row->GetCurrent(), doubleByteCharacter);
			//����ĭ�� �־��� ĭ�� �ִ´�
			DoubleByteCharacter *doubleByteCharacter_ = new DoubleByteCharacter;
			if (memoForm->row->GetCurrent() < memoForm->row->GetLength() - 1) {
				memoForm->row->TakeIn(memoForm->row->GetCurrent() + 1, doubleByteCharacter_);
			}
			//���� ������ġ�� ���� ���̺��� ũ�ų� ������
			else if (memoForm->row->GetCurrent() >= memoForm->row->GetLength() - 1) {
				memoForm->row->Add(doubleByteCharacter_);
			}
			memoForm->caret->MoveToCurrent(memoForm);
		}

	}
	ImmReleaseContext(memoForm->GetSafeHwnd(), hImc);
	
}