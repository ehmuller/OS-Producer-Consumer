#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

//Data structure to go into shared memory
struct sharedData{
	int bufferSpace;
	int semaphore;
	int full;
	int empty;
	char buffer[2];
	
	void wait(int &value)
	{
		while (value <= 0)
		;
		--value;
	};
	
	void signal(int &value)
	{
		++value;
	};
};

int main()
{
	int setBufferSize = 2; //Set max size of buffer
	int shmid;
	//Set up random seed and shared memory
	srand(0); //Set Random Number for usage in producing
	key_t key = 1234; //Key for shared memory	
	struct sharedData * shared; // Pointer for struc in shared memory
	shmid = shmget(key, sizeof(sharedData), 0666 | IPC_CREAT);
	shared = (sharedData*)shmat(shmid, NULL, 0);
	//
	std::cout << std::endl; //For better output to console
	//Writing values to shared structure
	(*shared).bufferSpace = setBufferSize;
	shared->semaphore = 1;
	shared->full = 0;
	shared->empty = setBufferSize;
	
	
	int bufferSize = setBufferSize;
	int count = 0;

	
	do{
		//Start of Production Loop
		//Wait 0-2 sec and then
		//Produce a random character
		sleep(rand() % 3);

		//Produce random character	
		char newChar = rand() % 26 + 65;
		
		//Semaphore wait functions
		(*shared).wait((*shared).empty);
		shared->wait(shared->semaphore);

		//Find the Correct location to insert the new character
		count = count % bufferSize;
		shared->buffer[count] = newChar;
		std::cout << "You wrote " << newChar << " to the buffer\n";
		++count;

		//Send signal to structure saying done with shared memory
		shared->signal(shared->semaphore);
		shared->signal(shared->full);
	}while(true);


}

