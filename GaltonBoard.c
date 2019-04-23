#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include<stdlib.h>
#include <stdbool.h> 

#define N 10000
#define slots 20

pthread_t tid[N];
int slotArr[slots];
int counter;
pthread_mutex_t lock;

void* runWithMutex(void *arg)
{

    pthread_mutex_lock(&lock);

    int k=0;
    counter=0;

    for(k=0;k<slots-1;k++){
    	// right:0 , left:1
    	// #of right: index of slotArr[]
    	bool randbool = rand() & 1; 
    	
    	if(randbool == 0)
    		counter += 1;
    }
    slotArr[counter] += 1;

    /* CONTROL
    printf("slotArr[%d]: ", counter);
    printf("%d \n", slotArr[counter]); */

    pthread_mutex_unlock(&lock);

    return NULL;
}

int main(void)
{
	printf("\nGALTON BOARD\n------------\n");
	int i,err,createdThreadCount=0; 

    // creating threads
    for(i=0;i<N;i++){
        pthread_create(&(tid[i]), NULL, &runWithMutex, NULL);
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
		printf("%d\n", slotArr[i]);

		sum += slotArr[i];
	}

	printf("\nSuccessfully created threads: %d\n", createdThreadCount++);
	printf("Sum of values in the slots %d\n\n\n", sum);

	printf("###\n\n");
	printf("COMMENT: Galton Board experiment shows us the number of balls in slots is distributed normally. Normal distribution is a bell-shaped distribution which has higher possibilities around the middle and lower possibilities at the edges. We can explain this event as below:\n\n");
	printf("In this example, if we analyze the possible paths of the balls, there is only one possible path for the first and last slot which is 19 times left or 19 times right.\n\n");
	printf("On the other hand, each path includes 9 times right and 10 times left (or reverse) ends with slot 9 (or 10). That makes C(19 9) = 92,378 possible paths for both these two slots.\n\n");
	printf("###\n");

    return 0;
}
