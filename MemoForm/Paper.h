//Paper.h
#ifndef _PAPER_H
#define _PAPER_H
typedef signed long int Long;
class Paper {
public:
	Paper();
	Paper(Long width, Long height);
	Paper(const Paper& source);
	~Paper();
	void MoveToX(Long x);
	void MoveToY(Long y);
	void Move(Long x, Long y);
	void ModifyWidth(Long width);
	void ModifyHeight(Long height);
	void ModifyPaper(Long width, Long height);
	Long GetX() const;
	Long GetY() const;
	Long GetWidth() const;
	Long GetHeight() const;
private:
	Long x;
	Long y;
	Long width;
	Long height;
};
inline Long Paper::GetX() const {
	return this->x;
}
inline Long Paper::GetY() const {
	return this->y;
}
inline Long Paper::GetWidth() const {
	return this->width;
}
inline Long Paper::GetHeight() const {
	return this->height;
}
#endif // _PAPER_H