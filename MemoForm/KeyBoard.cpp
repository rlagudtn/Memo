//KeyBoard.cpp
#include "KeyBoard.h"
#include "MemoForm.h"
#include "LeftArrowKey.h"
#include "RightArrowKey.h"
#include "UpArrowKey.h"
#include "DownArrowKey.h"
#include "HomeKey.h"
#include "EndKey.h"
#include "EnterKey.h"
#include "BackSpaceKey.h"
#include "DeleteKey.h"
#include "CtrlFindKey.h"
#include "CtrlAllKey.h"

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
	case VK_HOME: {
		this->keyAction = new HomeKey;
	}break;
	case VK_END: {
		this->keyAction = new EndKey;
	}break;
	case VK_RETURN: {
		this->keyAction = new EnterKey;
	}break;
	case VK_BACK: {
		this->keyAction = new BackSpaceKey;
	}break;
	case VK_DELETE: {
		this->keyAction = new DeleteKey;
	}break;
	case 0x41: {
		if (GetKeyState(VK_CONTROL) < 0) {
			this->keyAction = new CtrlAllKey;
		}
	}break;
	default:
		break;
	}
}
void KeyBoard::DoAction(MemoForm *memoForm) {
	this->keyAction->Implement(memoForm);
}