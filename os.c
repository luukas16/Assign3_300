#include "os.h"

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