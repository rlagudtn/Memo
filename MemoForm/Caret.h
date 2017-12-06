//Caret.h
#ifndef _CARET_H
#define _CARET_H

typedef signed long int Long;
class Caret {
public:
	Caret();
	Caret(const Caret& source);
	~Caret();
	void Move(Long x, Long y);
	void MoveX(Long x);
	void MoveY(Long y);
	//Long Delete(Long index);
	Caret& operator=(const Caret& source);
	Long GetX() const;
	Long GetY() const;
private:
	Long x;
	Long y;
};

inline Long Caret::GetX() const {
return this->x;
}

inline Long Caret::GetY() const {
return this->y;
}

#endif //CARET_H