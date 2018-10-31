// ProtoType.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <sys/stat.h>

int main(int argc, char* argv[])
{
	char cfg_path[PATH_MAX];
#ifdef AMIGAOS4
	snprintf(cfg_path, PATH_MAX, "%s.prototype", "PROGDIR:");
	printf("Will create %s folder\n", cfg_path);
#else
	snprintf(cfg_path, PATH_MAX, "%s/.prototype/", getenv("HOME"));
#endif
	mkdir(cfg_path, 0755);
	Engine engine(640,480,false,"PROTOTYPE");

	return 0;
}

