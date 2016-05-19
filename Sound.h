#pragma once
#ifdef PANDORA
#include <SDL/SDL_mixer.h>
#else
#include <fmod.h>
#endif
#include <stdio.h>

class Sound
{
public:
	virtual bool Load(char* sound, bool loop)=0;
	virtual int Play()=0;//returns channel
	virtual void Stop(int channel)=0;
	virtual void Discard()=0;
	void Volume(int channel,int vol);
};


class Sample : public Sound
{
public:
	#ifdef PANDORA
	Sample(){pSample = 0; pLoop = 1;}
	#else
	Sample(){pSample = 0;}
	#endif
//	~Sample(){ Discard(); }
	bool Load(char* sound, bool loop);
	int Play();
	void Play(int channel);
	void Stop(int channel);
	void Discard();
	void SetFrequency(int channel,int frequency);
	void SetDefaults(int  deffreq, int defvol, int defpan, int defpri, int varfreq, int varvol, int varpan);
private:
#ifdef PANDORA
	Mix_Chunk* pSample;
	int	   pLoop;
char* name;
#else
	FSOUND_SAMPLE* pSample;
#endif
};
class Stream : public Sound
{
public:
	#ifdef PANDORA
	Stream(){pStream = 0; pLoop = 1;}
	#else
	Stream(){pStream = 0;}
	#endif
//	~Stream(){ Discard(); }
	bool Load(char* sound, bool loop);
	int Play();
	void Play(int channel);
	void Stop(int channel);
	void Discard();
	void Seek(int ms, int channel);
private:
#ifdef PANDORA
	Mix_Music* pStream;
	int	pLoop;
#else
	FSOUND_STREAM* pStream;
#endif
};
