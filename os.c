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
int Create(int priority){
    process++;
    struct PCB *new_pcb = malloc(sizeof(struct PCB));

    new_pcb->priority = priority;
    new_pcb->pid = process;
    new_pcb->p_state = WAITING;
    List_append(&pcbs, new_pcb);


    if(process == 1){
        return 0;//success
    }//else handle the creation of a real process

    switch(priority){
        case 0:
            List_prepend(&p0_list, new_pcb);
            if(List_count(&p0_list) == 0){
                printf("Error in adding process to queue\n");
                return -1;
            }
            break;
        case 1:

            List_prepend(&p1_list, new_pcb);
            if(List_count(&p1_list) == 0){
                printf("Error in adding process to queue\n");
                return -1;
            }
            break;
        case 2:

            List_prepend(&p2_list, new_pcb);
            if(List_count(&p2_list) == 0){
                printf("Error in adding process to queue\n");
                return -1;
            }
            break;
        default:

            List_prepend(&p0_list, new_pcb);
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
int Fork(){
    if(current->pid != 1){
        Create(current->priority); 
        return 0;//success
    }
    return -1;//errror
}

//kill the named process and
//remove it from the system.
int Kill(int pid){
    struct PCB * temp1, *temp2, *temp3;
    temp1 = List_first(&p0_list);
    temp2 = List_first(&p1_list);
    temp3 = List_first(&p2_list);

    while(temp1 != NULL){
        if(temp1->pid == pid){
            printf("Process found in priority 0 queue. Process ID %d deleted\n", temp1->pid);
            List_remove(&p0_list);
            return 1;//found and removed
        }
        temp1  = List_next(&p0_list);
    }
    while(temp2 != NULL){
        if(temp2->pid == pid){
            printf("Process found in priority 1 queue. Process ID %d deleted\n", temp2->pid);
            List_remove(&p1_list);
            return 1;//found and removed
        }
        temp2  = List_next(&p1_list);   
    }
    while(temp3 != NULL){
        if(temp3->pid == pid){
            printf("Process found in priority 2 queue. Process ID %d deleted\n", temp3->pid);
            List_remove(&p2_list);
            return 1;//found and removed
        }
        temp3  = List_next(&p2_list);
    }
    return 0; //nothing found
}

//kill the currently running
//process.
int Exit(){
    Quantum();
}

//time quantum of running
//process expires.
int Quantum(){
    //when the quantum function is called it is treated as the end of a time quantum and thus the CPU needs to be updated
    printf("Process with ID %d is no longer running\n", current->pid);
    if(current->pid == 1){
        INIT->p_state = WAITING;
    }

    //we first check the highest priority queue for processes to run and work our way down in priority
    if(List_count(&p0_list) != 0 ){

        current = List_trim(&p0_list);
        current->p_state = RUNNING;

    }else if(List_count(&p1_list) != 0){

        current = List_trim(&p1_list);
        current->p_state = RUNNING;

    }else if(List_count(&p2_list) != 0){

        current = List_trim(&p2_list);
        current->p_state = RUNNING;

    }else{//if no other process are available we will run the INIT process
        current = INIT;
        current->p_state = RUNNING;
    }
    printf("Now running process with ID %d\n", current->pid);
}

//send a message to another
//process - block until reply
int Send(int pid, char* msg){
    if(strlen(msg) > 40){
        return -1;
    }

    struct PCB* temp0 = List_first(&p0_list);
    struct PCB* temp1 = List_first(&p1_list);
    struct PCB* temp2 = List_first(&p2_list);

    while(temp0 != NULL){
        if(temp0->pid == pid){
            printf("Message sent to the process with id %d. Sender is now blocked and waiting for response\n", pid);
            current->p_state = BLOCKED;
            temp0->msg = msg;
            List_prepend(&blockedQueue, current);
            List_remove(&p0_list);
            return 1; 
        }
        temp0  = List_next(&p0_list);
    }
    while(temp1 != NULL){
        if(temp1->pid == pid){
            printf("Message sent to the process with id %d. Sender is now blocked and waiting for response\n", pid);
            current->p_state = BLOCKED;
            temp1->msg = msg;
            List_prepend(&blockedQueue, current);
            List_remove(&p1_list);
            return 1; 
        }
        temp1  = List_next(&p1_list);   
    }
    while(temp2 != NULL){
        if(temp2->pid == pid){
            printf("Message sent to the process with id %d. Sender is now blocked and waiting for response\n", pid);
            current->p_state = BLOCKED;
            temp2->msg = msg;
            List_prepend(&blockedQueue, current);
            List_remove(&p2_list);
            return 1; 
        }
        temp2  = List_next(&p2_list);
    }
}

//receive a message - block until
//one arrives
int Receive(){
    printf("The receive function\n");
}

//unblocks sender and delivers
//reply
int Reply(){
    printf("The reply function\n");
}

//Initialize the named
//semaphore with the value
//given. ID's can take a value
//from 0 to 4. This can only be
//done once for a semaphore -
//subsequent attempts result in
//error.
int New_semaphore(){
    printf("The new_semaphore function\n");
}

//execute the semaphore P
//operation on behalf of the
//running process. You can
//assume sempahores IDs
//numbered 0 through 4.
int P_semaphore(){
    printf("The p_semaphore function\n");
}

//execute the semaphore V
//operation on behalf of the
//running process. You can
//assume sempahores IDs
//numbered 0 through 4.
int V_semaphore(){
    printf("The v_semaphore function\n");
}

//dump complete state
//information of process to
//screen (this includes process
//status and anything else you
//can think of)
int Process_info(int pid){
    struct PCB * temp1, *temp2, *temp3, *the_one;
    temp1 = List_first(&p0_list);
    temp2 = List_first(&p1_list);
    temp3 = List_first(&p2_list);
    bool found = false;

    while(temp1 != NULL){
        if(temp1->pid == pid){
            found = true;
            the_one = List_curr(&p0_list);
        }
        temp1  = List_next(&p0_list);
    }
    while(temp2 != NULL){
        if(temp2->pid == pid){
            found = true;
            the_one = List_curr(&p1_list);
        }
        temp2  = List_next(&p1_list);   
    }
    while(temp3 != NULL){
        if(temp3->pid == pid){
            found = true;
            the_one = List_curr(&p2_list);
        }
        temp3  = List_next(&p2_list);
    }
    if(found == true){
        printf("The process with ID %d ", the_one->pid);
        if(the_one->p_state == WAITING){
            printf(" is currently Waiting on ready queue %d\n", the_one->priority);

        }else if(the_one->p_state  == RUNNING){
            printf("is currently running\n");
        }else{
            printf("is currently blocked\n");
        }
        the_one = NULL;
    }else{
        if(current->pid == pid){
            printf("The process listed is currently the running process\n");
        }else{
            printf("The process listed could not be found\n");
        }
    }
}

//display all process queues and
//their contents
int Total_info(){
    printf("Priority 0: ");
    print(&p0_list);
    printf("Priority 1: ");
    print(&p1_list);
    printf("Priority 2: ");
    print(&p2_list);
}


struct PCB * curr(){
    printf("The currently running process: Process %d", current->pid);
    return current;
}