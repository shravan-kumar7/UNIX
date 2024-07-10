#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

#define NUM_THREADS 5

int shared_resource =0;
sem_t semaphore;

void *thread_function(void *arg)
{
    int thread_id=*((int*)arg);
    sem_wait(&semaphore);
    
    printf("Thread %d accessing shared resource\n", thread_id);
    shared_resource++;
    printf("Shared resource value incremented to %d ",shared_resource);

    sem_post(&semaphore);
    pthread_exit(NULL);
}

int main()
{
    pthread_t thread[NUM_THREADS];
    int thread_ids [NUM_THREADS];
    
    sem_init(&semaphore,0,1);
    
    for(int i=0;i<NUM_THREADS;i++)
    {
        thread_ids[i] = i+1;
        if(pthread_create(&thread[i],NULL,thread_function,(void*)&thread_ids[i])!=0)
        {
            fprintf(stderr,"error creating thread%d\n",i);
            exit(EXIT_FAILURE);
        }
    }
    
    for(int i=0;i<NUM_THREADS;i++)
    {
        if(pthread_join(thread[i],NULL)!=0)
        {
            fprintf(stderr,"error joining thread%d\n",i);
            exit(EXIT_FAILURE);
        }    
    }
    
    sem_destroy(&semaphore);
    return 0;
    
}
