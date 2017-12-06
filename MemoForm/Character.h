//character.h

#ifndef _CHARACTER_H
#define _CHARACTER_H
#include "Glyph.h"
typedef signed long int Long;
class Visitor;
class Character :public Glyph {
public:
	Character();
	Character(Long width, Long  height);
	
	Character(const Character& source);
	virtual ~Character() = 0;
	virtual bool IsEqual(const Character& other);
	virtual bool IsNotEqual(const Character& other);
	Character& operator=(const Character& source);
	virtual bool operator==(const Character& other);
	virtual bool operator!=(const Character& ohter);

	Long GetWidth() const;
	Long GetHeight() const;
	virtual Glyph* Clone();
	virtual void Accept(Visitor *visitor)=0;
protected:
	
	Long width;
	Long height;

};

inline Long Character::GetWidth() const {
	return this->width;
}
inline Long Character::GetHeight() const {
	return this->height;
}



#endif //_CHARACTER_H