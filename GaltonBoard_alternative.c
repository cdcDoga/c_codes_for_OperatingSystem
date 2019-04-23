#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <math.h>

#define N 10
#define slots 20
#define depth 19

pthread_t tid[N];
int arr[slots];
int numofrights;
pthread_mutex_t lock;
int start[2];
int k;

void* runnner(void *arg)
{

    pthread_mutex_lock(&lock);
    
    int i;
    float scale = 0;
    
    start[1] = round(depth/2.0);//start 0 için +
    start[0] = start[1] - 1;// start 1 için -
    
    
    for(i=0;i<depth;i++){
        
        bool rnd = rand() & 1; 
        
        printf("%d", rnd);
        
        if(rnd == 0)
            scale += 0.5;
        else
            scale -= 0.5;
    }
    
    if(scale < 0)
        k = round(start[1] + scale) - 1;
    else
        k = round(start[0] + scale);


    arr[k] += 1;
    printf(" arr[%d]:",k);
    printf("%d\n",arr[k]);

    pthread_mutex_unlock(&lock);

    return NULL;
}

int main(void)
{
    printf("\nCell: Value\n------------\n");
    int i,err,createdThreadCount=0; 

    // creating threads
    for(i=0;i<N;i++){
        pthread_create(&(tid[i]), NULL, &runnner, NULL);
        if (err == 0)
            createdThreadCount++;
    }
    // waiting for termination 
    for(i=0;i<N;i++)
        pthread_join(tid[i], NULL);

    int sum=0;
    // slots are writed as output
    for(i=0;i<slots;i++){
        printf("%*d: ", 5, i);
        printf("%d\n", arr[i]);

        sum += arr[i];
}

    printf("\nSuccessfully created threads: %d\n", createdThreadCount++);
    printf("Sum of values: %d\n\n\n", sum);
    printf("COMMENT:\n");
    return 0;
}