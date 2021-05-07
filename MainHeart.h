#ifndef MAIN_HEART_H_
#define MAIN_HEART_H_
#include"BaseObject.h"
#include <vector>

class MainHeart : public BaseObject
{
public:
	MainHeart();
	~MainHeart();

	void SetNumber(const int& num){number_ = num;}
	void Addpos (const int& xpos);
	void Render(SDL_Surface* des);
	void Init();
	void Dead();

private:
	int number_;
	std::vector<int> post_list_;
};

#endif // !MAIN_HEART_H_
