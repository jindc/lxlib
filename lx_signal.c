#include "lx_signal.h"

sighandler_t  lx_signal(int signo, sighandler_t func )
{
   struct sigaction act,oact;

   sigemptyset(&act.sa_mask);
   act.sa_flags = 0;
   if(signo == SIGALRM){
#ifdef SA_INTERRUPT
       act.sa_flags |= SA_INTERRUPT;/* SunOS 4.x* /
#endif
    }else {
#ifdef SA_RESTART        
    act.sa_flags |= SA_RESTART; /* SVR4, 44BSD*/
#endif
    }

    if(sigaction(signo,&act,&oact ) < 0)
        return (SIG_ERR);
    
    return (oact.sa_handler); 
}
