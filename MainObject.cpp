#include "MainObject.h"

MainObject::MainObject()
{
  rect_.x = 0;
  rect_.y = 0;
  rect_.w = WIDTH_MAIN_OBJECT;
  rect_.h = HEIGHT_MAIN_OBJECT;
  x_val_ = 0;
  y_val_ = 0;
}

MainObject::~MainObject()
{

}

void MainObject::HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2])
{
  if (events.type == SDL_KEYDOWN)
  {
    switch (events.key.keysym.sym)
    {
    case SDLK_UP:
      y_val_ -= SPEED;
      break;
    case SDLK_DOWN:
      y_val_ += SPEED;
      break;
    case SDLK_RIGHT:
      x_val_ += SPEED;
      break;
    case SDLK_LEFT:
      x_val_ -= SPEED;
      break;;
    default:
      break;
    }
  }
  else if (events.type == SDL_KEYUP)
  {
    switch(events.key.keysym.sym )
    {
      case SDLK_UP: y_val_ += SPEED; break;
      case SDLK_DOWN: y_val_ -= SPEED; break;
      case SDLK_LEFT: x_val_ += SPEED; break;
      case SDLK_RIGHT: x_val_ -= SPEED; break;
    }
  }
  else if (events.type == SDL_MOUSEBUTTONDOWN)
  {
    BulletObject* p_bullet = new BulletObject();
    if (events.button.button == SDL_BUTTON_LEFT)
    {
		p_bullet->SetWidthHeight(WIDTH_BULLET,HEIGHT_BULLET);
		p_bullet->LoadImg("Bullet_3.png");
		p_bullet->set_type(BulletObject::BULLET);
		Mix_PlayChannel(-1, bullet_sound[1], 0);
    }
    else if (events.button.button == SDL_BUTTON_RIGHT)
    {
		;
    }

    p_bullet->SetRect(this->rect_.x + this->rect_.w, this->rect_.y+5);
    p_bullet->set_is_move(true);
	p_bullet->set_x_val(15);
    p_bullet_list_.push_back(p_bullet);
  }
  else if (events.type == SDL_MOUSEBUTTONUP)
  {

  }
  else
  {
    ;//
  }
}

void MainObject::HandleMove()
{
  rect_.x += x_val_;

  if (rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH)
  {
    rect_.x -= x_val_;
  }


  rect_.y += y_val_;
  if (rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT)
  {
    rect_.y -= y_val_;
  }
}

void MainObject::RemoveBullet(const int& idx)
{
	for (int i=0;i<p_bullet_list_.size();i++)
	{
		if (idx < p_bullet_list_.size())
		{
			BulletObject*p_bullet =p_bullet_list_.at(idx);
			p_bullet_list_.erase(p_bullet_list_.begin() + idx);
			if(p_bullet != NULL)
			{
				delete p_bullet;
				p_bullet = NULL;
			}
		}
	}
}