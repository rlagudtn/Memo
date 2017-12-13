//KeyBoard.cpp
#include "KeyBoard.h"
#include "MemoForm.h"
#include "LeftArrowKey.h"
#include "RightArrowKey.h"
#include "UpArrowKey.h"
#include "DownArrowKey.h"
KeyBoard::KeyBoard() {

}
KeyBoard::KeyBoard(const KeyBoard& source) {

}
KeyBoard::~KeyBoard(){}

void KeyBoard::SetKeyAction(UINT nChar, UINT nRepCnt, UINT nFlags) {
	switch (nChar)
	{
	case VK_LEFT: {
		this->keyAction = new LeftArrowKey;
	}break;
	case VK_RIGHT: {
		this->keyAction = new RightArrowKey;
	}break;
	case VK_UP: {
		this->keyAction = new  UpArrowKey;

	}break;
	case VK_DOWN: {
		this->keyAction = new DownArrowKey;
	}break;
	default:
		break;
	}
}
void KeyBoard::DoAction(MemoForm *memoForm) {
	this->keyAction->Implement(memoForm);
}