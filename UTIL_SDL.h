#pragma once
#ifdef USE_SDL2
#include <SDL2/SDL.h>
#else
#include <SDL/SDL.h>
#endif
#include "UTIL_openGL.h"
#include "Log.h"
#define SDL_VERSION_1_3
#undef SDL_VERSION_1_3
//================================================================================================//
									/*****************
									 ** SDL helpers **
									 *****************/
//================================================================================================//
#ifdef USE_SDL2
extern SDL_Window	  *glWindow;
extern SDL_GLContext glContext;
#endif
namespace UTIL_SDL
{
	//SDL2 related

	bool InitSDL(char* winName, int width, int height, int bpp, bool vsync, bool fscreen);
	bool InitJoystick();
//================================================================================================//
									/*********************
									 ** pbuffer related **
									 *********************/
//================================================================================================//
#ifdef SDL_VERSION_1_3
	SDL_RenderTarget* Create_pBuffer(unsigned int width, unsigned int height);//must be power of 2
	void Unlock_pBuffer(SDL_RenderTarget* pTarget);
	void Lock_pBuffer(SDL_RenderTarget* pTarget);
	void Bind_pBuffer(SDL_RenderTarget pTarget);
#endif
}
