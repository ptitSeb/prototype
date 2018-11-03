CPP	      = g++
ifeq ($(ODROID),1)
CXXFLAGS      = -O3 -fsigned-char -fdiagnostics-color=auto -mcpu=cortex-a9 -mfpu=neon -mfloat-abi=hard -fsingle-precision-constant -g -ffast-math -I./ -I/usr/include/GL -Wno-write-strings -DODROID
LDFLAGS       = -lGL -lm
DEST          = /usr/local
else ifeq ($(LINUX),1)
CXXFLAGS      = -O2 -g -I./ -I/usr/include/GL -Wno-write-strings
LDFLAGS       = -lGL -lm
DEST          = /usr/local
else ifeq ($(AMIGAOS4),1)
CPP			  = ppc-amigaos-gcc
LD			  = ppc-amigaos-gcc -static
CXXFLAGS      = -O2 -g -I./ -I/usr/include/GL -Wno-write-strings -DAMIGAOS4
LDFLAGS       = -lSDL_image -lwebp -lpng12 -ltiff -ljpeg_8b -lmikmod -lmodplug -lvorbisfile -lvorbis -logg -lflac libgl4es.a -lstdc++ -lz
DEST          = /usr/local
else
CXXFLAGS      = -O3 -fsigned-char -fdiagnostics-color=auto -mcpu=cortex-a8 -mfpu=neon -mfloat-abi=softfp -fsingle-precision-constant -g -ffast-math -I/mnt/utmp/codeblocks/usr/include/ -I./ -I/mnt/utmp/codeblocks/usr/include/GL -Wno-write-strings -DPANDORA -DUSE_C4A
LDFLAGS       = -lGL -lm
DEST	      = .
endif

LD	      = g++

CXXFLAGS 	 += -std=c++11

CXXFLAGS     += -DNO_FMOD
ifeq ($(SDL2),1)
SDL_LDFLAGS   = $(shell sdl2-config --libs) 
SDL_CFLAGS    = $(shell sdl2-config --cflags)
CXXFLAGS     += -DUSE_SDL2
ifeq ($(AMIGAOS4),1)
LDFLAGS		 +=  -lSDL2_mixer -lSDL2_image libSDL2.a -lpthread -lsmpeg2
else
LDFLAGS      += -lSDL2_mixer 
endif
else
ifeq ($(AMIGAOS4),1)
LDFLAGS      += -lSDL_mixer -lSDL_image libSDL.a -lsmpeg
else
LDFLAGS      += -lSDL_mixer
endif
SDL_LDFLAGS   = $(shell sdl-config --libs) 
SDL_CFLAGS    = $(shell sdl-config --cflags)
endif

MAKEFILE      = Makefile

OBJS	      = AnimGenerator.o Font.o Serpent.o Beam.o FrontEnd.o SolarFlare.o Boss.o Game.o Sound.o BrainBoss.o Generator.o SpaceTrash.o BrainCell.o Geo2D.o Sperm.o BreakScenery.o Geo2D_Draw.o Sprite.o Bug.o HUD.o SpriteEffect.o Bullet.o LadyBird.o SpriteSheet.o Button.o Log.o StarBurst.o CheckPoint.o Map.o stdafx.o Debris.o MidBoss.o SuperTurret.o Demo.o Orb.o Timer.o Editor_Anims.o Player.o TriggerSlowDown.o Editor.o PostEffects.o TriggerSpeedUp.o Editor_EntityProperties.o PowerDroid.o Turret.o Engine.o PowerUp.o UTIL_bitop.o Engine_Generators.o Profiler.o UTIL_Fade.o Entity.o ProtoType.o UTIL_Misc.o Explosion.o RandExplosion.o UTIL_openGL.o Fighter.o Rhino.o UTIL_SDL.o firebug.o Rocket.o Fire.o Serializer.o

PRINT	      = pr

PROGRAM       = prototype

SHELL	      = /bin/bash

%.o:		%.cpp
		$(CPP) $(CXXFLAGS) $(SDL_CFLAGS) -c $<
all:		$(PROGRAM)

clean:
	rm $(OBJS) $(PROGRAM)

$(PROGRAM):     $(OBJS) $(LIBS)
		@echo "Linking $(PROGRAM) ..."
		$(LD) -o $(PROGRAM) $(OBJS) $(LDFLAGS) $(SDL_LDFLAGS)

