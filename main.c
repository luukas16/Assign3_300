#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include "list.c"

#define BUFFER_SIZE 256
time_t start_time, current_time;
int elapsed_time = 0;
char buffer;

    //the three priority queues
List p0_list;
List p1_list;
List p2_list;

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
};

//structure containing information about a specific semaphore
typedef struct semaphore{

    int sem_value; //unique identifier of the semaphore

};
//keeps track of the time in the program
//used in the round robin scheduling and the time quantum
void * clock_func(){

    start_time = time(NULL);

    while (buffer != '!') {
        current_time = time(NULL);
        elapsed_time = (int) difftime(current_time, start_time);

        //make the program wait two seconds
        //so the user has a chance to see what is going on
        //and the program isn't moving too fast
        sleep(2);
    }

    return NULL;
}

//DUMMY (for testing purposes only)
void print(List* pList){
    struct PCB *pcb;
    if(pList == NULL){
        printf("No items in the list.\n");
    }else{
        Node* temp = pList->head;
        printf("<-");
        while(temp != NULL){
            pcb = temp->item;
            printf("%d-", pcb->pid);
            temp = temp->next;
        }
        printf("> Queue length: %d", List_count(pList));
    }
    printf("\n");
}

//create a process and put it on
//the appropriate ready Q.
int Create(int priority, int process_ID){
    struct PCB temp;
    struct PCB *new_pcb = &temp;

    new_pcb->priority = priority;
    new_pcb->p_state = WAITING;
    new_pcb->pid = process_ID;


    switch(priority){
        case 0:
            List_append(&p0_list, new_pcb);
            if(List_count(&p0_list) == 0){
                printf("Error in adding process to queue\n");
                return -1;
            }
            break;
        case 1:
            List_append(&p1_list, new_pcb);
            if(List_count(&p1_list) == 0){
                printf("Error in adding process to queue\n");
                return -1;
            }
            break;
        case 2:
            List_append(&p2_list, new_pcb);
            if(List_count(&p2_list) == 0){
                printf("Error in adding process to queue\n");
                return -1;
            }
            break;
        default:
            List_append(&p0_list, new_pcb);
            if(List_count(&p0_list) == 0){
                printf("Error in adding process to queue\n");
                return -1;
            }
    };
    printf("new process created with priority: %d, and process ID: %d\n", new_pcb->priority, new_pcb->pid);
}

//Copy the currently running
//process and put it on the ready
//Q corresponding to the
//original process' priority.
//Attempting to Fork the "init"
//process (see below) should
//fail. 
int Fork(int priority){
    printf("The fork function\n");
}

//kill the named process and
//remove it from the system.
int Kill(int priority){
    printf("The kill function\n");
}

//kill the currently running
//process.
int Exit(int priority){
    printf("The exit function\n");
}

//time quantum of running
//process expires.
int Quantum(int priority){
    printf("The quantum function\n");
}

//send a message to another
//process - block until reply
int Send(int priority){
    printf("The send function\n");
}

//receive a message - block until
//one arrives
int Receive(int priority){
    printf("The receive function\n");
}

//unblocks sender and delivers
//reply
int Reply(int priority){
    printf("The reply function\n");
}

//Initialize the named
//semaphore with the value
//given. ID's can take a value
//from 0 to 4. This can only be
//done once for a semaphore -
//subsequent attempts result in
//error.
int New_semaphore(int priority){
    printf("The new_semaphore function\n");
}

//execute the semaphore P
//operation on behalf of the
//running process. You can
//assume sempahores IDs
//numbered 0 through 4.
int P_semaphore(int priority){
    printf("The p_semaphore function\n");
}

//execute the semaphore V
//operation on behalf of the
//running process. You can
//assume sempahores IDs
//numbered 0 through 4.
int V_semaphore(int priority){
    printf("The v_semaphore function\n");
}

//dump complete state
//information of process to
//screen (this includes process
//status and anything else you
//can think of)
int Process_info(int priority){
    printf("The process_info function\n");
}

//display all process queues and
//their contents
int Total_info(int priority){
    printf("The total_info function\n");
}

void printQueues(){

    printf("Priority 0: ");
    print(&p0_list);
    printf("Priority 1: ");
    print(&p1_list);
    printf("Priority 2: ");
    print(&p2_list);

}

int main (){


    p0_list = * List_create();
    p1_list = * List_create();
    p2_list = * List_create();


    //starting the clock for use in timing the processes
    pthread_t tid;
    if (pthread_create(&tid, NULL, &clock_func, NULL) != 0) {
        printf("Failed to create thread.\n");
        return 1;
    }

    printf("Welcome to the Rastko_Luukas Operating System. Please enter one character at a time.\n");
    printf("Enter 'H' for a list of useable commands and '!' to close the program\n");
    int num, num2;
    char priority_int[50];
    char process_ID[50];

    while(buffer != '!'){

        buffer = getchar();
        if(buffer != '\n'){
            switch(buffer){
                case 'C':
                    printf("Please enter the priority of the new process. 0 = high, 1 = medium, 2 = low: ");
                    scanf("%s", priority_int);
                    num = atoi(priority_int);
                    printf("Please enter a unique process ID for the new process: ");
                    scanf("%s", process_ID);
                    num2 = atoi(process_ID);
                    Create(num, num2);
                    break;
                case 'F':
                    Fork(0);
                    break;
                case 'K':
                    Kill(0);
                    break;
                case'E':
                    Exit(0);
                    break;         
                case 'Q':
                    Quantum(0);
                    break; 
                case 'S':
                    Send(0);
                    break;           
                case 'R':
                    Receive(0);
                    break;            
                case 'Y':
                    Reply(0);
                    break;            
                case 'N':
                    New_semaphore(0);
                    break;           
                case 'P':
                    P_semaphore(0);
                    break;          
                case 'V':
                    V_semaphore(0);
                    break;           
                case 'I':
                    Process_info(0);
                    break;      
                case 'T':
                    Total_info(0);
                    break;  
                case 'A':
                    printf("Elapsed time: %d\n", elapsed_time);
                    break;
                case 'B':
                    printQueues();
                    break;
                //this will be the help section, if the user inputs H
                //Then the program will print some helpful info
                case 'H':
                    printf("This operating system supports 14 operations: (To close the system enter '!')\n");
                    printf("\n");

                    printf("C (create): Creates a process and puts it on the appropriate ready queue\n");
                    printf("----> Parameters for C (create): int priority, 0 = high, 1 = norm, 2 = low.\n");
                    printf("\n");

                    printf("F (fork): Copy the currently running process and put it on the ready queue corresponding to the original process' priority.\n");
                    printf("----> Parameters for F (fork): NONE\n");
                    printf("\n");

                    printf("K (kill): Kill the named process and remove it from the system\n");
                    printf("----> Parameters for K (kill): int pid, the process id corresponding to the process to be killed\n");
                    printf("\n");

                    printf("E (exit): Kill the currently running process\n");
                    printf("----> Parameter for E (exit): NONE\n");
                    printf("\n");

                    printf("Q (quantum): time quantum of running process expires\n");
                    printf("----> Parameters for Q (quantum): NONE\n");printf("\n");
                    printf("\n");

                    printf("S (send): send a message to another process -- block until it gets a reply\n");
                    printf("----> Parameters for S (send): pid, process id of the process to send to, char * msg, the message to be sent (40 char max)\n");
                    printf("\n");

                    printf("R (receive): receive a message -- block until one arrives\n");
                    printf("----> Parameters for R (receive): NONE\n");
                    printf("\n");

                    printf("Y (reply): unblocks the sending process and delivers a reply\n");
                    printf("----> Parameters for Y (reply): int pid, process id of the process we are replying too, char * msg, message to reply (40 char max)\n");
                    printf("\n");

                    printf("N (new semaphore): initialize the named semaphore with the value given. Value can be 0-4\n");
                    printf("----> Parameters for N (new semaphore): int sid, integer value representing the semaphore can be 0-4.\n");
                    printf("\n");

                    printf("P (semaphore lock): lock the given semaphore\n");
                    printf("----> Parameters for P (semaphore lock): int sid, semaphore id\n");
                    printf("\n");

                    printf(" V (semaphore unlock): unlock the corresponding semaphore\n");
                    printf("----> Parameters for V (semaphore unlock): int sid, semaphore id \n");
                    printf("\n");

                    printf("I (process info): dump complete state information of process to screen\n");
                    printf("----> Parameters for I (process info): int pid, process id you would like info on\n");
                    printf("\n");

                    printf("T (total info): display all available information on processes and the states of the queues\n");
                    printf("----> Parameters for T (total info): NONE\n");
                    break;
                case '!':
                    break;
                default:
                    printf("Command not recognised. Enter 'H' for help or '!' to close the program \n");
            }//end switch buffer
        }// end if(buffer != '\n')
    }//end while(buffer != '!')

    //kill the thread
    pthread_join(tid, NULL);
}//end int main