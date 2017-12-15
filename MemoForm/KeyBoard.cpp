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
#include "CtrlZKey.h"
#include "CtrlXKey.h"
#include "CtrlCopyKey.h"
#include "CtrlVKey.h"
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
		//ctrl+a
	case 0x41: {
		if (GetKeyState(VK_CONTROL) < 0) {
			this->keyAction = new CtrlAllKey;
		}
	}break;
		//ctrl+x
	case 0x58: {
		if (GetKeyState(VK_CONTROL) < 0) {
			this->keyAction = new CtrlXKey;
		}
	}break;
		//ctrl+c
	case 0x43: {
		if (GetKeyState(VK_CONTROL) < 0) {
			this->keyAction = new CtrlCopyKey;
		}
	}break;
		//ctrl+v
	case 0x56: {
		if (GetKeyState(VK_CONTROL) < 0) {
			this->keyAction = new CtrlVKey;
		}
	}break;
	default:
		break;
	}
}
void KeyBoard::DoAction(MemoForm *memoForm) {
	this->keyAction->Implement(memoForm);
}