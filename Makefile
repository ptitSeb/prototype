CPP	      = g++
ifeq ($(ODROID),1)
CXXFLAGS      = -O3 -fsigned-char -fdiagnostics-color=auto -mcpu=cortex-a9 -mfpu=neon -mfloat-abi=hard -fsingle-precision-constant -g -ffast-math -I./ -I/usr/include/GL -Wno-write-strings -DODROID
LDFLAGS       = -lGL -lm
DEST          = /usr/local
else ifeq ($(PYRA),1)
CXXFLAGS      = -O3 -fsigned-char -fdiagnostics-color=auto -mcpu=cortex-a15 -mfpu=neon-vfpv4 -marm -mfloat-abi=hard -fsingle-precision-constant -g -ffast-math -I./ -I/usr/include/GL -Wno-write-strings -DPYRA
LDFLAGS       = -lGL -lm
DEST          = /usr/local
else ifeq ($(LINUX),1)
CXXFLAGS      = -O2 -g -I./ -I/usr/include/GL -Wno-write-strings
LDFLAGS       = -lGL -lm
DEST          = /usr/local
else ifeq ($(AMIGAOS4),1)
ifeq ($(SDL2),1)
CXXFLAGS      = -O2 -g -I./ -Wno-write-strings -DUSE_SDL2 -DNO_FMOD -DAMIGAOS4
else
CXXFLAGS      = -O2 -g -I./ -Wno-write-strings -DNO_FMOD -DAMIGAOS4
endif
DEST          = /usr/local
else ifeq ($(EMSCRIPTEN),1)
CXXFLAGS= -s FULL_ES2=1 -I../gl4es/include -s USE_SDL_MIXER=2 -s USE_SDL=2
CXXFLAGS+= -s USE_OGG=1 -s USE_VORBIS=1 -lidbfs.js
CXXFLAGS+= -std=gnu++11 -O2 -Wno-write-strings
CXXFLAGS+= -Dlinux -DUSE_SDL2 -DNO_FMOD
CXXFLAGS+= --emrun --preload-file Data --no-heap-copy
CXXFLAGS+= -s TOTAL_MEMORY=128MB -s ALLOW_MEMORY_GROWTH=1
CXXFLAGS+= --shell-file template.html
LDFLAGS= $(CXXFLAGS) ../gl4es/lib/libGL.a
CC= emcc
CPP= em++
LD= em++
override SDL=2
else
CXXFLAGS      = -O3 -fsigned-char -fdiagnostics-color=auto -mcpu=cortex-a8 -mfpu=neon -mfloat-abi=softfp -fsingle-precision-constant -g -ffast-math -I/mnt/utmp/codeblocks/usr/include/ -I./ -I/mnt/utmp/codeblocks/usr/include/GL -Wno-write-strings -DPANDORA -DUSE_C4A
LDFLAGS       = -lGL -lm
DEST	      = .
endif

ifeq ($(EMSCRIPTEN),1)
#OBJS	      = AnimGenerator.bc Font.bc Serpent.bc Beam.bc FrontEnd.bc SolarFlare.bc Boss.bc Game.bc Sound.bc BrainBoss.bc Generator.bc SpaceTrash.bc BrainCell.bc Geo2D.bc Sperm.bc BreakScenery.bc Geo2D_Draw.bc Sprite.bc Bug.bc HUD.bc SpriteEffect.bc Bullet.bc LadyBird.bc SpriteSheet.bc Button.bc Log.bc StarBurst.bc CheckPoint.bc Map.bc stdafx.bc Debris.bc MidBoss.bc SuperTurret.bc Demo.bc Orb.bc Timer.bc Editor_Anims.bc Player.bc TriggerSlowDown.bc Editor.bc PostEffects.bc TriggerSpeedUp.bc Editor_EntityProperties.bc PowerDroid.bc Turret.bc Engine.bc PowerUp.bc UTIL_bitop.bc Engine_Generators.bc Profiler.bc UTIL_Fade.bc Entity.bc ProtoType.bc UTIL_Misc.bc Explosion.bc RandExplosion.bc UTIL_openGL.bc Fighter.bc Rhino.bc UTIL_SDL.bc firebug.bc Rocket.bc Fire.bc Serializer.bc
OBJS	      = AnimGenerator.o Font.o Serpent.o Beam.o FrontEnd.o SolarFlare.o Boss.o Game.o Sound.o BrainBoss.o Generator.o SpaceTrash.o BrainCell.o Geo2D.o Sperm.o BreakScenery.o Geo2D_Draw.o Sprite.o Bug.o HUD.o SpriteEffect.o Bullet.o LadyBird.o SpriteSheet.o Button.o Log.o StarBurst.o CheckPoint.o Map.o stdafx.o Debris.o MidBoss.o SuperTurret.o Demo.o Orb.o Timer.o Editor_Anims.o Player.o TriggerSlowDown.o Editor.o PostEffects.o TriggerSpeedUp.o Editor_EntityProperties.o PowerDroid.o Turret.o Engine.o PowerUp.o UTIL_bitop.o Engine_Generators.o Profiler.o UTIL_Fade.o Entity.o ProtoType.o UTIL_Misc.o Explosion.o RandExplosion.o UTIL_openGL.o Fighter.o Rhino.o UTIL_SDL.o firebug.o Rocket.o Fire.o Serializer.o
PROGRAM       = docs/index.html

else
ifeq ($(AMIGAOS4),1)
# no c++11 on amiga?!
CPP			  = ppc-amigaos-gcc
LD			  = ppc-amigaos-gcc -static
else
LD	      	  = g++
CXXFLAGS 	 += -std=c++11
endif

ifeq ($(AMIGAOS4),1)
ifeq ($(SDL2),1)
LDFLAGS		 += -lSDL2_image -lwebp -lpng12 -ltiff -ljpeg_8b -lSDL2_mixer -lmikmod -lmodplug -lvorbisfile -lvorbis -logg -lflac -lsmpeg2 libSDL2.a libgl4es.a -lpthread -lstdc++ -lz
else
LDFLAGS      += -lSDL_image -lwebp -lpng12 -ltiff -ljpeg_8b -lSDL_mixer -lmikmod -lmodplug -lvorbisfile -lvorbis -logg -lflac -lsmpeg2 libSDL.a libgl4es.a -lstdc++ -lz
endif
else
ifeq ($(SDL2),1)
CXXFLAGS     += -DUSE_SDL2
SDL_LDFLAGS   = $(shell sdl2-config --libs) 
SDL_CFLAGS    = $(shell sdl2-config --cflags)
else
SDL_LDFLAGS   = $(shell sdl-config --libs) 
SDL_CFLAGS    = $(shell sdl-config --cflags)
endif
ifeq ($(FMOD),1)
LDFLAGS      += -lfmod
else
CXXFLAGS     += -DNO_FMOD
ifeq ($(SDL2),1)
LDFLAGS      += -lSDL2_mixer 
else
LDFLAGS      += -lSDL_mixer 
endif
endif
endif

OBJS	      = AnimGenerator.o Font.o Serpent.o Beam.o FrontEnd.o SolarFlare.o Boss.o Game.o Sound.o BrainBoss.o Generator.o SpaceTrash.o BrainCell.o Geo2D.o Sperm.o BreakScenery.o Geo2D_Draw.o Sprite.o Bug.o HUD.o SpriteEffect.o Bullet.o LadyBird.o SpriteSheet.o Button.o Log.o StarBurst.o CheckPoint.o Map.o stdafx.o Debris.o MidBoss.o SuperTurret.o Demo.o Orb.o Timer.o Editor_Anims.o Player.o TriggerSlowDown.o Editor.o PostEffects.o TriggerSpeedUp.o Editor_EntityProperties.o PowerDroid.o Turret.o Engine.o PowerUp.o UTIL_bitop.o Engine_Generators.o Profiler.o UTIL_Fade.o Entity.o ProtoType.o UTIL_Misc.o Explosion.o RandExplosion.o UTIL_openGL.o Fighter.o Rhino.o UTIL_SDL.o firebug.o Rocket.o Fire.o Serializer.o
PROGRAM       = prototype
endif

PRINT	      = pr


SHELL	      = /bin/bash

%.o:		%.cpp
		$(CPP) $(CXXFLAGS) $(SDL_CFLAGS) -c $<

%.bc:		%.cpp
		$(CPP) -o $@ $(CXXFLAGS) $(SDL_CFLAGS) -c $<

all:		$(PROGRAM)

clean:
	rm $(OBJS) $(PROGRAM)

$(PROGRAM):     $(OBJS) $(LIBS)
		@echo "Linking $(PROGRAM) ..."
		$(LD) -o $(PROGRAM) $(OBJS) $(LDFLAGS) $(SDL_LDFLAGS)

