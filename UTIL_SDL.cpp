#include "UTIL_SDL.h"
//================================================================================================//
									/*****************
									 ** SDL helpers **
									 *****************/
//================================================================================================//
namespace UTIL_SDL
{
//================================================================================================//
									/********************
									 ** Initialize SDL **
									 ********************/
//================================================================================================//
	bool InitSDL(char* winName, int width, int height, int bpp, bool vsync, bool fscreen)
	{
		gLog.OutPut("\n[Initializing Video Settings]\n");
		const SDL_VideoInfo* info = NULL;
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_NOPARACHUTE) < 0 || !(info = SDL_GetVideoInfo()))
		{
			gLog.OutPut("\n[Failed to initialize Video Settings]\n");
			return false;
		}
		SDL_WM_SetIcon(SDL_LoadBMP("icon1.bmp"), NULL);
		int flags = SDL_OPENGL | (fscreen?SDL_FULLSCREEN:0);
/*		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	//	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 0);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
*/
		SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
		SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 0);

		if(SDL_SetVideoMode(width, height, bpp, flags) == 0)
		{
			SDL_Quit();
			return false;
		}
		stringstream(str);
		str << "Resolution Set: " << width << "x" << height << "x" << bpp << endl;
		gLog.OutPut(str.str());
/*		if(!vsync)
		{
			PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT  = (PFNWGLSWAPINTERVALEXTPROC) wglGetProcAddress("wglSwapIntervalEXT");
			if(wglSwapIntervalEXT==NULL)
				PostQuitMessage(0);
			wglSwapIntervalEXT(0);
			gLog.OutPut("Vsync Disabled.\n");
		}
		else
		{
			PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT  = (PFNWGLSWAPINTERVALEXTPROC) wglGetProcAddress("wglSwapIntervalEXT");
			if(wglSwapIntervalEXT==NULL)
				PostQuitMessage(0);
			wglSwapIntervalEXT(1);
			gLog.OutPut("Vsync Enabled.\n");
		}
*/		SDL_ShowCursor(0);
		SDL_WM_SetCaption(winName, NULL);
		gLog.OutPut("Complete...\n\n");
		return true;
	}
//================================================================================================//
									/*************************
									 ** Initialize joystick **
									 *************************/
//================================================================================================//
	bool InitJoystick()
	{
		SDL_Joystick* pad;
		gLog.OutPut("\n[Searching for Joystick]\n");

		SDL_Init(SDL_INIT_JOYSTICK);
		int numJoy=0;
		if(!(numJoy=SDL_NumJoysticks()))
		{
			gLog.OutPut("No joysticks found...\n");
			return false;
		}
		bool bJoyFound = false;
		for(int n=0; n<numJoy; n++)
		{
			char sz[256];
			pad = SDL_JoystickOpen(n);
			if(!pad)
			{
				sprintf(sz,"Joystick %i could not be opened!\n" ,n);
				gLog.OutPut(sz);
				//return false;
			}
			else
			{
				sprintf(sz,"Joystick %i found and intialized.\n",n);
				gLog.OutPut(sz);
				bJoyFound = true;
			}
		}
		gLog.OutPut("Complete...\n\n");
		if(bJoyFound)
			return true;
		return false;
	}
//================================================================================================//
									/*********************
									 ** pbuffer related **
									 *********************/
//================================================================================================//
#ifdef SDL_VERSION_1_3
	SDL_RenderTarget* Create_pBuffer(unsigned int width, unsigned int height)
	{
		SDL_RenderTarget* pTarget=NULL;
		GLuint tID;
		glGenTextures(1, &tID);
		UTIL_GL::BindTexture(GL_TEXTURE_2D, tID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		pTarget = SDL_GL_CreateRenderTarget(width, height, NULL);
		if(pTarget)
		{
#ifdef DEBUG_VERBOSE
			int value;
			stringstream(str);
			str << "Created render target:\n";
			gLog.OutPut(str.str());str.clear();
			SDL_GL_GetRenderTargetAttribute( pTarget, SDL_GL_RED_SIZE, &value );
			str << "SDL_GL_RED_SIZE:" << value << endl;
			gLog.OutPut(str.str());str.clear();
			SDL_GL_GetRenderTargetAttribute( pTarget, SDL_GL_GREEN_SIZE, &value );
			str << "SDL_GL_GREEN_SIZE:" << value << endl;
			gLog.OutPut(str.str());str.clear();
			SDL_GL_GetRenderTargetAttribute( pTarget, SDL_GL_BLUE_SIZE, &value );
			str << "SDL_GL_BLUE_SIZE:" << value << endl;
			gLog.OutPut(str.str());str.clear();
			SDL_GL_GetRenderTargetAttribute( pTarget, SDL_GL_ALPHA_SIZE, &value );
			str << "SDL_GL_ALPHA_SIZE:" << value << endl;
			gLog.OutPut(str.str());str.clear();
			SDL_GL_GetRenderTargetAttribute( pTarget, SDL_GL_DEPTH_SIZE, &value );
			str << "SDL_GL_DEPTH_SIZE:" << value << endl;
			gLog.OutPut(str.str());str.clear();
#endif
			SDL_GL_BindRenderTarget(pTarget, tID);
		}
		return pTarget;
	}
	void Unlock_pBuffer(SDL_RenderTarget* pTarget)
	{
		if(pTarget)
			SDL_GL_UnlockRenderTarget(pTarget);
	}
	void Lock_pBuffer(SDL_RenderTarget* pTarget)
	{
		if(pTarget)
		{
			SDL_GL_LockRenderTarget(pTarget);
			glViewport(0,0,pTarget->w,pTarget->h);
		}
	}
	void Bind_pBuffer(SDL_RenderTarget pTarget)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,pTarget.texture);
	}
#endif
}
