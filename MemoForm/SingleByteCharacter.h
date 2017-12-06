// SingleByteCharacter.h
#ifndef _SINGLEBYTECHARACTER_H
#define _SINGLEBYTECHARACTER_H
#include "Character.h"

typedef signed long int Long;
class MemoForm;
class SingleByteCharacter :public Character {
public:
	SingleByteCharacter();
	SingleByteCharacter(Long width, Long height, char alphabet);
	SingleByteCharacter(char alphabet);
	SingleByteCharacter(const SingleByteCharacter& source);
	virtual ~SingleByteCharacter();
	SingleByteCharacter& operator=(const SingleByteCharacter& source);
	bool IsEqual(const SingleByteCharacter& other);
	bool IsNotEqual(const SingleByteCharacter& other);
	bool operator==(const SingleByteCharacter& other);
	bool operator!=(const SingleByteCharacter& other);

	char GetAlphabet() const;

	Glyph* Clone();
	void Accept(Visitor *visitor);
private:
	char alphabet;
};
inline char SingleByteCharacter::GetAlphabet() const {
	return this->alphabet;
}
#endif // _SINGLEBYTECHARACTER_H