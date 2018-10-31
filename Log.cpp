#include "Log.h"
#include <sys/stat.h>
#include "stdafx.h"
//================================================================================================//
						/**************************
						** global logging system **	
						***************************/
//================================================================================================//
Log gLog;
#define PRINT_TO_CONSOLE//if defined will print to the console aswell as the logfile

void Log::OutPut(string str)
{
	char logpath[PATH_MAX];
#ifdef AMIGAOS4
	snprintf(logpath, PATH_MAX, "%s.prototype/Logfile.txt", "PROGDIR:");
#else
	snprintf(logpath, PATH_MAX, "%s/.prototype/Logfile.txt", getenv("HOME"));
#endif
	if(!bKeepLog)
		return;
#ifdef PRINT_TO_CONSOLE
	printf(str.c_str());
#endif
	ofstream f;
	if(!lcount)
	{
		f.open(logpath);
		f << "Logfile created on " << __DATE__ << endl;
	}
	else
		f.open(logpath,ios::app);

	if(f.is_open())
	{
		f << str.c_str();
		f.close();
	}
	lcount++;
}
void Log::SetLogState(int state)
{
	bool l = state?true:false;
	if(l && !bKeepLog)
	{
		bKeepLog = l;
		OutPut(">>Logging Enabled<<\n");
	}
	else if(!l && bKeepLog)
	{
		bKeepLog = l;
		OutPut(">>Logging Disabled<<\n");
	}
}