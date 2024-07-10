#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

//signal handler function
void sig_handler(int signum)
{
    printf("received signal: %d\n",signum);
}

int main()
{
    struct sigaction sa;
    sigset_t old_mask, new_mask;
    
    //set up signal handler
    sa.sa_handler=sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags =0;
    
    //register signal handler for SIGINT
    if(sigaction(SIGINT, &sa,NULL)==-1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    printf("signal handler registered for SIGINT (ctrl + c)\n");
    
    //initialize new signal mask
    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGINT);
    
    //get current signal mask
    if(sigprocmask(SIG_BLOCK,NULL,&old_mask)==-1)
    {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }
    //check if SIGINT is already in the mask
    if(sigismember(&old_mask,SIGINT))
        printf("SIGINT is already present\n");
    else
    {
        //add SIGINT to the signal mask
        if(sigprocmask(SIG_BLOCK, &new_mask, NULL)==-1)
        {
            perror("sigprocmask");
            exit(EXIT_FAILURE);
        }
        printf("added SIGINT to signal mask\n");
    }
    while(1)
    {
        sleep(1);
    }
    
    return 0;
}
