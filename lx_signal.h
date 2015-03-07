#ifndef LX_SIGNAL_H
#define LX_SIGNAL_H
#include <signal.h>

typedef void (*sighandler_t)(int);

sighandler_t  lx_signal(int signo, sighandler_t func );


#endif

