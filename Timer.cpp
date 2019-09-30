#include "Timer.h"

Timer::Timer(void)
{
	#ifdef __EMSCRIPTEN__
	m_dLastTime = m_dCurTime = 0.;
	#else
	m_uiLastTime = m_uiCurTime = 0;
	#endif
	m_fDelta = m_fTime = m_fOldTime = 0;
	m_uiFPS = m_uiCountFPS = 0;
}

Timer::~Timer(void)
{

}
void Timer::Update()
{
	#ifdef __EMSCRIPTEN__
	m_dLastTime = m_dCurTime;
	m_dCurTime = emscripten_get_now();
	m_fDelta = (m_dCurTime - m_dLastTime) * 0.001;
	#else
	m_uiLastTime = m_uiCurTime;
	m_uiCurTime = SDL_GetTicks();
	m_fDelta = (float)( (m_uiCurTime - m_uiLastTime)) * 0.001f;
	#endif
	m_uiCountFPS += 1;
	m_fTime += m_fDelta;
	if(m_fTime > m_fOldTime+1)
	{
		m_fOldTime = m_fTime;
		m_uiFPS = m_uiCountFPS;
		m_uiCountFPS = 0;
	}
}