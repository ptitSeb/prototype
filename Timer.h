#pragma once
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#elif defined(USE_SDL2)
#include <SDL2/SDL.h>
#else
#include <SDL/SDL.h>
#endif
class Timer
{
private:
	#ifdef __EMSCRIPTEN__
	double m_dLastTime;
	double m_dCurTime;
	#else
	Uint32 m_uiLastTime;
	Uint32 m_uiCurTime;
	#endif
	float m_fDelta;
	float m_fOldTime;
	unsigned int m_uiCountFPS;
	unsigned int m_uiFPS;
public:
	float m_fTime;
	Timer(void);
	~Timer(void);
	void Update();

	float GetTime() { return m_fTime; }
	float GetDelta() { return m_fDelta<0.1f? m_fDelta: 0; }
	unsigned int GetFPS() { return m_uiFPS; }
	unsigned int GetFPSCounter() { return m_uiCountFPS; }
	void LockFrameRate(int fps) {
		#ifdef __EMSCRIPTEN__
		double tick = emscripten_get_now() - m_dCurTime;
		while(tick<(unsigned int)fps)
		{
			tick = emscripten_get_now() - m_dCurTime;
		}
		#else
		Uint32 tick = SDL_GetTicks()-m_uiCurTime;
//		if(tick>5000)
//			tick=0;		
		while(tick<(unsigned int)fps)
		{
			tick = SDL_GetTicks()-m_uiCurTime;
		}
		#endif
	}
};
