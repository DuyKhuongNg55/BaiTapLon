#include "Common_Function.h"
#include "MainObject.h"
#include "ThreatObject.h"
#include "MainHeart.h"


bool Init()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
  {
    return false;
  }

  g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

  if (g_screen == NULL)
    return false;

  if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
  {
	  return false;
  }

  g_sound_bullet[1] = Mix_LoadWAV("Shot.wav");
  g_sound_exp[1] = Mix_LoadWAV("exp.wav");
  g_sound_track = Mix_LoadWAV("SoundTrack.wav");

  if (g_sound_bullet[1] == NULL || g_sound_exp[1] == NULL || g_sound_track == NULL )
  {
	  return false;
  }
  return true;
}


int main(int arc, char*argv[])
{
  int bkg_x =0 ;
  bool is_quit = false;
  if (Init() == false)
    return 0;



  g_bkground = SDLCommonFunc::LoadImage("Bkg.png");
  if (g_bkground == NULL)
  {
    return 0;
  }
  
  MainHeart mainheart;
  mainheart.Init();

  MainObject plane_object;
  plane_object.SetRect(100, 200);
  bool ret = plane_object.LoadImg("Plane.png");
  if (!ret)
  {
    return 0;
  }

  ThreatObject* p_threats = new ThreatObject[NUM_THREATS];
  for (int t=0; t< NUM_THREATS; t++)
  {
	ThreatObject* p_threat = (p_threats + t);
	ret = p_threat->LoadImg("Enemi.png");
	if (!ret)
	{
		return 0;
	}
  
	srand(time(NULL));
	int rand_y = rand() % (H_MIN-H_MAX+1) + H_MAX;
	while (rand_y > H_MIN)
	{
		rand_y = rand() % (H_MIN-H_MAX+1) + H_MAX;
	}
	p_threat->SetRect(SCREEN_WIDTH + t*300 ,rand_y);
	p_threat->set_x_val(SPEED);

	BulletObject* p_bullet = new BulletObject();
	p_threat->InitBullet(p_bullet);
  };
  Mix_PlayChannel(-1, g_sound_track, 0);
  
  unsigned int die_number = 0; 

  while (!is_quit) 
  {
    while (SDL_PollEvent(&g_even)) 
    {
      if (g_even.type == SDL_QUIT)
      {
        is_quit = true;
        break;
      }
      plane_object.HandleInputAction(g_even, g_sound_bullet);
    }

	bkg_x -= 2;
    SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkg_x, 0);
	SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkg_x + BKG_WIDTH, 0);
	if (bkg_x <= -BKG_WIDTH)
	{
		bkg_x = 0;
	}

	//show heart
	mainheart.Render(g_screen);

	plane_object.HandleMove();
    plane_object.Show(g_screen);

    for (int i = 0; i < plane_object.GetBulletList().size(); i++)
    {
      std::vector<BulletObject*> bullet_list = plane_object.GetBulletList();
      BulletObject* p_bullet = bullet_list.at(i);
      if (p_bullet != NULL)
      {
        if (p_bullet->get_is_move())
        {
          p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
          p_bullet->Show(g_screen);
        }
        else 
        {
          if (p_bullet != NULL)
          {
            bullet_list.erase(bullet_list.begin() + i);
            plane_object.SetBulletList(bullet_list);

            delete p_bullet;
            p_bullet = NULL;
          }
        }
      }
    }
	for (int T=0;T<NUM_THREATS;T++)
	{
		ThreatObject* p_threat = (p_threats + T);
		if (p_threat)
		{
			p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
			p_threat->Show(g_screen);
			p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);

			std::vector<BulletObject*> bullet_list2 = p_threat->GetBulletList();
			for (int J = 0; J < bullet_list2.size();J++)
			{
				BulletObject* p_bullet2 = bullet_list2.at(J);
				if (p_bullet2 != NULL)
				{
					bool is_col2 = SDLCommonFunc::CheckCollision(plane_object.GetRect(),p_bullet2->GetRect());
					if (is_col2)
					{
						if (is_col2)
						{
							Mix_PlayChannel(-1, g_sound_exp[1], 0);
							die_number++;
							if (die_number > 2)
							{
							if(MessageBox(NULL,L"GAME OVER",L"Info",MB_OK) ==IDOK)
							{
								delete[] p_threats;
								SDLCommonFunc::CleanUp();
								SDL_Quit();
								return 1;
							}
							else
							{
								SDL_Delay(1000);
								plane_object.SetRect(SCREEN_HEIGHT*0.5, SCREEN_WIDTH*0.5);
								mainheart.Dead();
								mainheart.Render(g_screen);
							}
							}
						}
					}
				}
			}
			bool is_col1 = SDLCommonFunc::CheckCollision(plane_object.GetRect(),p_threat->GetRect());
			if (is_col1)
			{
				Mix_PlayChannel(-1, g_sound_exp[1], 0); 
				die_number++;
				if (die_number++)
				{
				if(MessageBox(NULL,L"GAME OVER",L"Info",MB_OK) ==IDOK)
				{
					delete[] p_threats;
					SDLCommonFunc::CleanUp();
					SDL_Quit();
					return 1;
				}
				else
				{
					SDL_Delay(1000);
					plane_object.SetRect(SCREEN_HEIGHT*0.5, SCREEN_WIDTH*0.5);
					mainheart.Dead();
					mainheart.Render(g_screen);
				}
				}
			}

			std::vector<BulletObject*> bullet_list1 = plane_object.GetBulletList();
			for (int j = 0; j < bullet_list1.size();j++)
			{
				BulletObject* p_bullet1 = bullet_list1.at(j);
				if (p_bullet1 != NULL)
				{
					bool ret_col = SDLCommonFunc::CheckCollision(p_bullet1->GetRect(),p_threat->GetRect());
					if (ret_col)
					{
						p_threat->Reset(SCREEN_WIDTH + T*300);
						plane_object.RemoveBullet(j);
					}
				}
			}
		}
	}

    if ( SDL_Flip(g_screen) == -1)
      return 0;
  }

  delete[] p_threats;

  SDLCommonFunc::CleanUp();
  SDL_Quit();

  return 1;
}