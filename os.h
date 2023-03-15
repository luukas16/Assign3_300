#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include "list.h"

#define BUFFER_SIZE 256

static char buffer;
static struct PCB * current; //will point to the currently running process;
static struct PCB *INIT;
static int process = 0;

//the three priority queues
static List pcbs;
static List p0_list;
static List p1_list;
static List p2_list;

static List blockedQueue;

//enum containing the possible states that a process can be in
typedef enum {
    RUNNING, WAITING, BLOCKED
} State; 

//Structure containing information about a specific process
struct PCB {

    int pid; //unique process identification number
    int priority; //0 = high, 1 = medium, 2 = low
    State p_state; // 

    char * msg; //storage for string messages
    int sender_id;
};

//structure containing information about a specific semaphore
typedef struct semaphore{

    int sem_value; //unique identifier of the semaphore

};


//DUMMY (for testing purposes only)
void print(List* pList);

//create a process and put it on
//the appropriate ready Q.
int Create(int priority);

//Copy the currently running
//process and put it on the ready
//Q corresponding to the
//original process' priority.
//Attempting to Fork the "init"
//process (see below) should
//fail. 
int Fork();

//kill the named process and
//remove it from the system.
int Kill(int pid);

//kill the currently running
//process.
int Exit();

//time quantum of running
//process expires.
int Quantum();

//send a message to another
//process - block until reply
int Send(int pid, char* msg);

//receive a message - block until
//one arrives
int Receive();

//unblocks sender and delivers
//reply
int Reply(int pid);

//Initialize the named
//semaphore with the value
//given. ID's can take a value
//from 0 to 4. This can only be
//done once for a semaphore -
//subsequent attempts result in
//error.
int New_semaphore();

//execute the semaphore P
//operation on behalf of the
//running process. You can
//assume sempahores IDs
//numbered 0 through 4.
int P_semaphore();

//execute the semaphore V
//operation on behalf of the
//running process. You can
//assume sempahores IDs
//numbered 0 through 4.
int V_semaphore();

//dump complete state
//information of process to
//screen (this includes process
//status and anything else you
//can think of)
int Process_info(int pid);

//display all process queues and
//their contents
int Total_info();