#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

sem_t s0_1; 
sem_t s0_3; 
sem_t s0_4; 
sem_t s1_3; 
sem_t s1_5; 
sem_t s2_4; 
sem_t s2_5; 
sem_t s2_6; 
sem_t s3_7; 
sem_t s4_8; 
sem_t s5_6; 
sem_t s6_8; 
sem_t s7_8; 
sem_t s7_9; 
  
void* thread0(void* arg) 
{ 
    //execution 
    sleep(2); 
      
    //signal 
    printf("\nJob0 is done\n"); 
    sem_post(&s0_1); 
    sem_post(&s0_3); 
    sem_post(&s0_4); 
}

void* thread1(void* arg) 
{ 
    printf("\nJob1 is waiting for Job0\n"); 
    
    //wait 
    sem_wait(&s0_1); 
  
    //execution
    sleep(2); 
      
    //signal 
    printf("\nJob1 is done\n"); 
    sem_post(&s1_3); 
    sem_post(&s1_5);
}

void* thread2(void* arg) 
{ 
    //execution 
    sleep(2); 
      
    //signal 
    printf("\nJob2 is done\n"); 
    sem_post(&s2_4); 
    sem_post(&s2_5); 
    sem_post(&s2_6); 
}

void* thread3(void* arg) 
{ 
    printf("\nJob3 is waiting for Job0, Job1\n"); 
    
    //wait 
    sem_wait(&s0_3); 
    sem_wait(&s1_3); 
  
    //execution 
    sleep(2); 
      
    //signal 
    printf("\nJob3 is done\n"); 
    sem_post(&s3_7); 
}

void* thread4(void* arg) 
{ 
    printf("\nJob4 is waiting for Job0, Job2\n"); 

    //wait 
    sem_wait(&s0_4); 
    sem_wait(&s2_4); 
  
    //execution 
    sleep(2); 
      
    //signal 
    printf("\nJob4 is done\n"); 
    sem_post(&s4_8); 
}

void* thread5(void* arg) 
{ 
    printf("\nJob5 is waiting for Job1, Job2\n"); 
    
    //wait 
    sem_wait(&s1_5); 
    sem_wait(&s2_5); 
  
    //execution 
    sleep(2); 
      
    //signal 
    printf("\nJob5 is done\n"); 
    sem_post(&s5_6); 
}

void* thread6(void* arg) 
{ 
    printf("\nJob6 is waiting for Job2, Job5\n"); 
    
    //wait 
    sem_wait(&s2_6); 
    sem_wait(&s5_6); 
  
    //execution 
    sleep(2); 
      
    //signal 
    printf("\nJob6 is done\n"); 
    sem_post(&s6_8); 
}

void* thread7(void* arg) 
{ 
    printf("\nJob7 is waiting for Job3\n"); 
    
    //wait 
    sem_wait(&s3_7); 
  
    //execution
    sleep(2); 
      
    //signal 
    printf("\nJob7 is done\n"); 
    sem_post(&s7_8); 
    sem_post(&s7_9); 
}

void* thread8(void* arg) 
{ 
    printf("\nJob8 is waiting for Job4, Job6, Job7\n"); 
    
    //wait 
    sem_wait(&s4_8); 
    sem_wait(&s6_8);
    sem_wait(&s7_8);
  
    //execution 
    sleep(2); 
      
    printf("\nJob8 is done\n"); 
}

void* thread9(void* arg) 
{ 
    printf("\nJob9 is waiting for Job7\n"); 
    
    //wait 
    sem_wait(&s7_9); 
  
    //execution 
    sleep(2); 
      
    printf("\nJob9 is done\n");
}
  
  
int main() 
{ 
    /*
    int sem_init(sem_t *sem, int pshared, unsigned int value);

    sem: points to a semaphore object to initialize
    pshared: is a flag indicating whether or not the semaphore should be shared with fork()ed processes. LinuxThreads does not currently support shared semaphores
    value: is an initial value to set the semaphore to
    */
    sem_init(&s0_1, 0, 0); 
    sem_init(&s0_3, 0, 0);
    sem_init(&s0_4, 0, 0);
    sem_init(&s1_3, 0, 0);
    sem_init(&s1_5, 0, 0);
    sem_init(&s2_4, 0, 0);
    sem_init(&s2_5, 0, 0);
    sem_init(&s2_6, 0, 0);
    sem_init(&s3_7, 0, 0);
    sem_init(&s4_8, 0, 0);
    sem_init(&s5_6, 0, 0);
    sem_init(&s6_8, 0, 0);
    sem_init(&s7_8, 0, 0);
    sem_init(&s7_9, 0, 0);
    
    pthread_t t0,t1,t2,t3,t4,t5,t6,t7,t8,t9; 
    
    pthread_create(&t0,NULL,thread0,NULL); 
    pthread_create(&t1,NULL,thread1,NULL); 
    pthread_create(&t2,NULL,thread2,NULL); 
    pthread_create(&t3,NULL,thread3,NULL); 
    pthread_create(&t4,NULL,thread4,NULL); 
    pthread_create(&t5,NULL,thread5,NULL); 
    pthread_create(&t6,NULL,thread6,NULL); 
    pthread_create(&t7,NULL,thread7,NULL); 
    pthread_create(&t8,NULL,thread8,NULL); 
    pthread_create(&t9,NULL,thread9,NULL); 
    
    pthread_join(t0,NULL); 
    pthread_join(t1,NULL); 
    pthread_join(t2,NULL); 
    pthread_join(t3,NULL); 
    pthread_join(t4,NULL); 
    pthread_join(t5,NULL); 
    pthread_join(t6,NULL); 
    pthread_join(t7,NULL); 
    pthread_join(t8,NULL); 
    pthread_join(t9,NULL); 
    
    sem_destroy(&s0_1); 
    sem_destroy(&s0_3);
    sem_destroy(&s0_4);
    sem_destroy(&s1_3);
    sem_destroy(&s1_5);
    sem_destroy(&s2_4);
    sem_destroy(&s2_5);
    sem_destroy(&s2_6);
    sem_destroy(&s3_7);
    sem_destroy(&s4_8);
    sem_destroy(&s5_6);
    sem_destroy(&s6_8);
    sem_destroy(&s7_8);
    sem_destroy(&s7_9);
    
    return 0; 
}