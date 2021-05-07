#include "MainHeart.h"

MainHeart::MainHeart()
{}

MainHeart::~MainHeart()
{}

void MainHeart::Addpos(const int& xpos)
{
	post_list_.push_back(xpos);
}

void MainHeart::Render(SDL_Surface* des)
{
	if(number_ == post_list_.size())
	{
		for (int i=0; i < post_list_.size(); i++ )
		{
			rect_.x = post_list_.at(i);
			Show(des);
		}
	}
}

void MainHeart::Init()
{
	LoadImg("Heart.png");
	number_ = NUM_HEART;
	if (post_list_.size() > 0)
	{
		post_list_.clear();
	}
	Addpos(20);
	Addpos(60);
	Addpos(100);
}

void MainHeart::Dead()
{
	number_ --;
	post_list_.pop_back();
}
