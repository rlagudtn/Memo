//DoubleByteCharacter
#ifndef _DOUBLEBYTECHARACTER_H
#define _DOUBLEBYTECHARACTER_H
#include "Character.h"
#include <string>
using namespace std;
typedef signed long int Long;
class Visitor;
class DoubleByteCharacter :public Character {
public:
	DoubleByteCharacter();
	DoubleByteCharacter(Long width, Long height, char *alphabet);
	DoubleByteCharacter(char *alphabet);
	DoubleByteCharacter(const DoubleByteCharacter& source);
	virtual ~DoubleByteCharacter();
	DoubleByteCharacter& DoubleByteCharacter::operator=(const DoubleByteCharacter& source);
	bool IsEqual(const DoubleByteCharacter& other);
	bool IsNotEqual(const DoubleByteCharacter& other);
	bool operator==(const DoubleByteCharacter& other);
	bool operator!=(const DoubleByteCharacter& other);
	char* GetAlphabet() const;
	Glyph* Clone();
	void Accept(Visitor *visitor);
private:
	char alphabet[3];
};
inline char* DoubleByteCharacter::GetAlphabet() const {
	return const_cast<char*>(this->alphabet);
}
#endif // _DOUBLEBYTECHARACTER_H