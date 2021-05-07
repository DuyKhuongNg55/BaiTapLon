#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "Common_Function.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include <vector>

#define WIDTH_MAIN_OBJECT 80
#define HEIGHT_MAIN_OBJECT 30

class MainObject : public BaseObject
{
public:
  MainObject();
  ~MainObject();

  void HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2]);
  void HandleMove();
  void SetBulletList(std::vector<BulletObject*> bullet_list) {p_bullet_list_ = bullet_list;}
  std::vector<BulletObject*> GetBulletList() {return p_bullet_list_;}
  void RemoveBullet(const int& idx);
private:
  int x_val_;
  int y_val_;

  std::vector<BulletObject*> p_bullet_list_;

};



#endif