//audio.h
//
// 
//
//////////////////////////////////////////////////////////////////////
#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <pspaudio.h>
#include <pspaudiolib.h>
#include <oslib/oslib.h>
#include <mikmod.h>

#ifdef __cplusplus
extern "C" {
#endif

/*mikmod specific*/
extern int _mm_errno;
extern BOOL _mm_critical;
extern char *_mm_errmsg[];
int mikModThreadID = -1;
int done = 0;
char playerName[128];

extern UWORD md_mode;
extern UBYTE md_reverb;
extern UBYTE md_pansep;


BOOL outputEnabled;
int maxchan = 128;
MODULE *mf = NULL; // for mod
SAMPLE *sf = NULL; // for wav
int voice = 0; 	   // for wav
int pan = 127;
int vol = 127;
int freq = 22000;

void my_error_handler(void);
int AudioChannelThread(int args, void *argp);
void initMusicStuff();




#ifdef __cplusplus
}
#endif
#endif