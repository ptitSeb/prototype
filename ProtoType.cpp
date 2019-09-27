// ProtoType.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <sys/stat.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#ifdef AMIGAOS4
static const char* __attribute__((used)) stackcookie = "$STACK: 1000000";
#endif
#ifdef __EMSCRIPTEN__
int fileSynched = 0;

static void em_wait_loop()
{
	if(!fileSynched)
		return;
	emscripten_cancel_main_loop();
	Engine engine(640,480,false,"PROTOTYPE");
}
#endif

int main(int argc, char* argv[])
{
	char cfg_path[PATH_MAX];
#ifdef AMIGAOS4
	snprintf(cfg_path, PATH_MAX, "%s.prototype", "PROGDIR:");
	printf("Will create %s folder\n", cfg_path);
#elif defined(__EMSCRIPTEN__)
	// that HEAP32 on &fileSynched looks like a hack, but I needed a way to be sure the DB is read before reading the ini files
	printf("Permanent storage init\n");
	EM_ASM_INT({
		FS.mkdir('prototype_data'); 
		FS.mount(IDBFS,{},'prototype_data');
		Module.print("Will import permanent storage");
		FS.syncfs(true, function() {
			Module.print("Permanent storage imported");
			HEAP32[$0>>2] = 1;
		});
	}, &fileSynched);
#else
	snprintf(cfg_path, PATH_MAX, "%s/.prototype/", getenv("HOME"));
#endif
#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(em_wait_loop, 0, 1);
#else
	mkdir(cfg_path, 0755);
	Engine engine(640,480,false,"PROTOTYPE");
#endif
	return 0;
}

