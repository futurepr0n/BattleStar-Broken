//audio.c
#include "audio.h"

int AudioChannelThread(int args, void *argp)
{
  while (!done)
  {
    MikMod_Update();
    // We have to sleep here to allow other threads a chance to process.
    // with no sleep this thread will take over when the output is disabled via MikMod_DisableOutput()
    // co-operative threading sucks bigtime...
    sceKernelDelayThread(1);
  }
  return (0);
}

void my_error_handler(void)
{
	printf("_mm_critical %d\n", MikMod_critical);
	printf("_mm_errno %d\n", MikMod_errno);
	printf("%s\n", MikMod_strerror(MikMod_errno));
	return;
}

void initMusicStuff()
{
    ///////////////////////////////////////
// Set up Mikmod stuff
///////////////////////////////////////
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(1);

    if (!MikMod_InitThreads()){
        printf("MikMod thread init failed\n");
 	}
     
    MikMod_RegisterErrorHandler(my_error_handler);
  	/* register all the drivers */
  	MikMod_RegisterAllDrivers();
  	/* register all the module loaders */
  	MikMod_RegisterAllLoaders();

    /* initialize the library */
	md_mode = DMODE_16BITS|DMODE_STEREO|DMODE_SOFT_SNDFX|DMODE_SOFT_MUSIC; 
	md_reverb = 0;
	md_pansep = 128;
  	if (MikMod_Init("")){
   		printf("Could not initialize sound, reason: %s\n", MikMod_strerror(MikMod_errno));
    	sceKernelExitGame();
    	//return 0;
    }
  
  	MikMod_SetNumVoices(-1, 8);
	/* get ready to play */
    //int v1;
	sf = Sample_Load("ViperFiring.wav");
    //MikMod_SetNumVoices(-1, 2);
    outputEnabled = 1;


	mf = Player_Load("mrdeath_-_12th_moon_rising.xm", maxchan, 0);
    	if (NULL != mf){
    		mf->wrap = 1;
			Player_Start(mf);
    	}
	MikMod_EnableOutput();
  	//BOOL outputEnabled = true;
  	if ((mikModThreadID = sceKernelCreateThread("MikMod" ,(void*)&AudioChannelThread,0x12,0x10000,0,NULL)) > 0){
    	sceKernelStartThread(mikModThreadID, 0 , NULL);
	}
  	else{
    	printf("Play thread create failed!\n");
  	}    

}