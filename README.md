# OS-Producer-Consumer
Producer/Consumer problem with shared memory on a Linux OS

This c++ code is for the producer/consumer
probelm in linux using separate processes.
To accomplish this, a struct was shared 
between the two processes including the 
buffer that is being written to and the 
user built semaphore to ensure 
appropriate access to the buffer. 

----------RUNNGING-----------------
The compilation for the code is
g++ producer.cpp -o producer
g++ consumer.cpp -o consumer

The execution of the code is
./producer& ./consumer&
-----------------------------------

----TERMINATION-------------------
As program simulates producer/consumer 
and runs indefinitely, to stop the 
processes, must call:

ps -ef | grep -i <process_name>

and then :

kill -9 <process_id> 

with the process_id found using the 
grep search

--------------------------------------
This program will only work on linux 
systems, as it calls shmget() for 
shared memory and references the
unistd.h library, which is also
only on linux
-----------------------------------
Lack of Pthreads
While this assignment called for
potentially using pthreads, I could not
figure out the correct context to use them,
so I went with a solution I could figure out
---------------------------------------
Program was ran and tested on Ubuntu
20.04.1
