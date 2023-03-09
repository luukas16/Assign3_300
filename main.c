#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define BUFFER_SIZE 256
int Create(int priority){
    printf("The create function\n");
}
int Fork(int priority){
    printf("The fork function\n");
}
int Kill(int priority){
    printf("The kill function\n");
}
int Exit(int priority){
    printf("The exit function\n");
}
int Quantum(int priority){
    printf("The quantum function\n");
}
int Send(int priority){
    printf("The send function\n");
}
int Receive(int priority){
    printf("The receive function\n");
}
int Reply(int priority){
    printf("The reply function\n");
}
int New_semaphore(int priority){
    printf("The new_semaphore function\n");
}
int P_semaphore(int priority){
    printf("The p_semaphore function\n");
}
int V_semaphore(int priority){
    printf("The v_semaphore function\n");
}
int Process_info(int priority){
    printf("The process_info function\n");
}
int Total_info(int priority){
    printf("The total_info function\n");
}

//enum containing the possible states that a process can be in
typedef enum {
    RUNNING, WAITING, BLOCKED
} State; 

//Structure containing information about a specific process
typedef struct PCB {

    int pid; //unique process identification number
    int priority; //0 = high, 1 = medium, 2 = low
    State p_state; // 

    char * msg; //storage for string messages
};

//structure containing information about a specific semaphore
typedef struct semaphore{

    int sem_value; //unique identifier of the semaphore

};

int main (){

    char buffer;


    printf("Welcome to the Rastko_Luukas Operating System. Please enter one character at a time.\n");
    printf("Enter 'H' for a list of useable commands and '!' to close the program\n");

    while(buffer != '!'){

        buffer = getchar();
        if(buffer != '\n'){
                switch(buffer){
                case 'C':
                    Create(0);
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
}//end int main