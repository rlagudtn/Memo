//RowInfoIndex.h
#ifndef _ROWINFO_H
#define _ROWINFO_H
typedef signed long int Long;
class Character;
class Row;
class RowInfo {
public:

	RowInfo();
	RowInfo(const RowInfo& source);
	~RowInfo();
	void GetRowInfo(Row *row);
	Long GetLastIndex() const;
	Character* GetAlphabet() const;
	bool GetIsLastIndex() const;
private:
	Long lastIndex;
	Character *lastAlphabet;
	bool isLastIndex;
};
inline Long RowInfo::GetLastIndex() const {
	return this->lastIndex;
}
inline Character* RowInfo::GetAlphabet() const {
	return const_cast<Character*>(this->lastAlphabet);
}
inline bool RowInfo::GetIsLastIndex() const {
	return this->isLastIndex;
}
#endif // _ROWINFO_H
