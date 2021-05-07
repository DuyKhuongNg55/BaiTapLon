#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <Windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>


const int SPEED = 5;
const int BKG_WIDTH = 2048;
const int BKG_HEIGHT = 675;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 675;
const int SCREEN_BPP = 32;
const int NUM_THREATS = 3;
const int NUM_HEART = 3;

static SDL_Surface* g_screen = NULL;
static SDL_Surface* g_bkground = NULL;
static SDL_Event g_even;

static Mix_Chunk* g_sound_bullet[2];
static Mix_Chunk* g_sound_exp[2];
static Mix_Chunk* g_sound_track;
namespace SDLCommonFunc
{
  SDL_Surface* LoadImage(std::string file_path);
  void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
  void CleanUp();
  bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
};


#endif
