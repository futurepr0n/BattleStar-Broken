//control.h

#ifndef _CONTROL_H_
#define _CONTROL_H_

// #include "loadobj.h"
// #include "blitobj.h"
#include "movement.h"
//#include "audio.h"
#include <pspaudio.h>
#include <pspaudiolib.h>
#include <oslib/oslib.h>
#include <mikmod.h>


#ifdef __cplusplus
extern "C" {
#endif


MODULE *mf = NULL; // for mod

//private functions
    void control();
    // void shootChain();
    // void scrollBackground();
    void my_error_handler(void);
    int AudioChannelThread(int args, void *argp);
    void setupMikMod();
    void quitMikMod();

#ifdef __cplusplus
}
#endif
#endif
