#include "Sound.h"

void Sound::Volume(int channel,int vol)
{
//printf("Sample::Volume(%i, %i)\n", channel, vol);
	#ifdef NO_FMOD
	Mix_Volume(channel, vol);
	#else
	FSOUND_SetVolume(channel,vol);
	#endif
}
bool Sample::Load(char* sound, bool loop)
{
//printf("Sample::Load(\"%s\", %i)\n", sound, loop);
	if(loop)
	{
		#ifdef NO_FMOD
		pLoop=-1;
		if((pSample = Mix_LoadWAV(sound))==0)
		#else
		if((pSample = FSOUND_Sample_Load(FSOUND_FREE,sound,FSOUND_NORMAL | FSOUND_LOOP_NORMAL,0,0))==0)
		#endif
		{
			printf("Failed to load sample: %s\n",sound);
			return false;
		}
	}
	else
	{
		#ifdef NO_FMOD
		pLoop=0;
		if((pSample = Mix_LoadWAV(sound))==0)
		#else
		if((pSample = FSOUND_Sample_Load(FSOUND_FREE,sound,FSOUND_NORMAL | FSOUND_LOOP_OFF,0,0))==0)
		#endif
		{
			printf("Failed to load sample: %s\n",sound);
			return false;
		}
	}
//name=(char*)malloc(strlen(sound)+1);
//strcpy(name, sound);
//printf("pSample=%p, name=%s\n", pSample, name);
	return true;
}
int Sample::Play()
{
//printf("Sample::Play() pSample=%p, name=%s\n", pSample, name);
	if(pSample)
		#ifdef NO_FMOD
 		return(Mix_PlayChannel(-1, pSample, pLoop));
		#else
		return(FSOUND_PlaySound(FSOUND_FREE,pSample));
		#endif
	return -1;
}
void Sample::Play(int channel)
{
//printf("Sample::Play(%i) pSample=%p, name=%s\n", channel, pSample, name);	
	if(pSample)
		#ifdef NO_FMOD
 		Mix_PlayChannel(channel, pSample, pLoop);
		#else
		FSOUND_PlaySound(channel,pSample);
		#endif
}
void Sample::Stop(int channel)
{
//printf("Sample::Stop(\"%s\", %i)\n", name, channel);
	#ifdef NO_FMOD
	Mix_HaltChannel(channel);
	#else
	FSOUND_StopSound(channel);
	#endif
}
void Sample::Discard()
{
//printf("Sample::Discard()\n");
	if(pSample)
		#ifdef NO_FMOD
		Mix_FreeChunk(pSample);
		#else
		FSOUND_Sample_Free(pSample);
		#endif
//	pSample = 0;
}
void Sample::SetFrequency(int channel,int frequency)
{
//printf("Sample::SetFrequency(%i, %i)\n", channel, frequency);
	#ifdef NO_FMOD
	//TODO is this usefull?
	#else
	FSOUND_SetFrequency(channel,frequency);
	#endif
}
void Sample::SetDefaults(int  deffreq, int defvol, int defpan, int defpri, int varfreq, int varvol, int varpan)
{
//printf("Sample::SetDefaults(%i, %i, %i, %i, %i, %i, %i)\n", deffreq, defvol, defpan, defpri, varfreq, varvol, varpan);
	#ifdef NO_FMOD
	//TODO is this usefull?
	#else
	FSOUND_Sample_SetDefaultsEx(pSample,deffreq,defvol,defpan,defpri,varfreq,varvol,varpan);
	#endif
}
bool Stream::Load(char* stream, bool loop)
{
//printf("Stream::Load(\"%s\", %i)\n", stream, loop);
	if(loop)
	{
		#ifdef NO_FMOD
		pLoop=-1;
		if((pStream = Mix_LoadMUS(stream))==0)
		#else
		if((pStream = FSOUND_Stream_Open(stream,FSOUND_NORMAL | FSOUND_LOOP_NORMAL,0,0))==0)
		#endif
		{
			printf("Failed to load sample: %s\n",stream);
			return false;
		}
	}
	else
	{
		#ifdef NO_FMOD
		pLoop=0;
		if((pStream = Mix_LoadMUS(stream))==0)
		#else
		if((pStream = FSOUND_Stream_Open(stream,FSOUND_NORMAL,0,0))==0)
		#endif
		{
			printf("Failed to load sample: %s\n",stream);
			return false;
		}
	}
	return true;
}
int Stream::Play()
{
//printf("Stream::Play()\n");
	if(pStream)
		#ifdef NO_FMOD
		Mix_PlayMusic(pStream, pLoop);
		return(1);//TODO, better value?
		#else
		return(FSOUND_Stream_Play(FSOUND_FREE,pStream));
		#endif
	return -1;
}
void Stream::Play(int channel)
{
//printf("Stream::Play(%i)\n", channel);
	if(pStream)
		#ifdef NO_FMOD
		Mix_PlayMusic(pStream, pLoop);
		#else
		FSOUND_Stream_Play(channel,pStream);
		#endif
//		return(FSOUND_Stream_Play(channel,pStream));
//	return -1;
}
void Stream::Stop(int channel)
{
//printf("Stream::Stop(%i)\n", channel);
	if(pStream)
		#ifdef NO_FMOD
		Mix_HaltMusic();
		#else
		FSOUND_Stream_Stop(pStream);
		#endif
}
void Stream::Discard()
{
//printf("Stream::Discard()\n");
	if(pStream)
		#ifdef NO_FMOD
		Mix_FreeMusic(pStream);
		#else
		FSOUND_Stream_Close(pStream);
		#endif
	pStream = 0;
}
void Stream::Seek(int ms, int channel)
{
//printf("Stream::Seek(%i, %i)\n", ms, channel);
	if(pStream)
	{
		#ifdef NO_FMOD
		Mix_PlayMusic(pStream, pLoop);
		Mix_PauseMusic();
		Mix_SetMusicPosition(ms/1000.0);
		Mix_ResumeMusic();
		#else
		FSOUND_Stream_Play(channel,pStream);
		FSOUND_SetPaused(channel,true);
		FSOUND_Stream_SetTime(pStream,ms);
		FSOUND_SetPaused(channel,false);
		#endif
	}
}
