#pragma once
#include <SDL/SDL.h>
#include "UTIL_openGL.h"
#include "Log.h"
#define SDL_VERSION_1_3
#undef SDL_VERSION_1_3
//================================================================================================//
									/*****************
									 ** SDL helpers **
									 *****************/
//================================================================================================//
namespace UTIL_SDL
{
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
