//LineFeed.cpp
#include "LineFeed.h"
#include "Row.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"

LineFeed::LineFeed() {

}
LineFeed::LineFeed(const LineFeed& source) {

}
LineFeed::~LineFeed() {

}
void LineFeed::SetLineFeed(Row *row) {
	Long rowIndex = row->GetCurrent();
	SingleByteCharacter *carriageReturn = new SingleByteCharacter('\r');
	SingleByteCharacter *lineFeed = new SingleByteCharacter('\n');
	row->Add(carriageReturn);
	row->Add(lineFeed);
	row->Move(rowIndex);
}
bool LineFeed::IsLineFeed(Row *row) {
	bool ret = false;
	Character *character = dynamic_cast<Character*>(row->GetAt(row->GetLength() - 1));
	if (dynamic_cast<SingleByteCharacter*>(character)) {
		if (dynamic_cast<SingleByteCharacter*>(character)->GetAlphabet() == '\n') {
			ret = true;
		}
	}
	return ret;
}