#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

struct sharedData{
	int bufferSpace;
	int semaphore;
	int full;
	int empty;
	char buffer[2];
	
	void wait(int &value)
	{
		while (value <= 0){
		};
		--value;
	};
	
	void signal(int &value)
	{
		++value;
	};
};


int main(){

	//Sleep Function so if run at same time, give producer time to set 
	//up shared memory and allow for some writing
	sleep(1);
	//Connect to the Shared Memory between producer and consumer 
	key_t key = 1234;
	int shmid = shmget(key, sizeof(sharedData), 0666);
	sharedData * shared = (sharedData*)shmat(shmid, NULL, 0);
	srand(0); //Set Random Number
	
	int count = 0;
	int bufferSize = shared->bufferSpace;
	char bufferValue;
	
	//Continues looping indefinitely, need to kill process to stop
	do{
		//Sleep a random amount to simulate different times to 			complete job
		sleep(rand() % 4);
		
		//Semaphore Locks
		shared->wait(shared->full);
		shared->wait(shared->semaphore);
		
		bufferValue = shared->buffer[count];
		//Value changed to zero symblized empty array spot, will be 			written 
		//over instead of deleted from array
		shared->buffer[count] = '0';
		
		//Signals to structure to say done with data
		shared->signal(shared->semaphore);
		shared->signal(shared->empty);
		
		//State what was removed and set up for removal of next item
		std::cout << bufferValue <<" was removed from the buffer\n";
		++count;
		count = count % bufferSize;
	}while(true);

};
