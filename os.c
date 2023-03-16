#include "os.h"

bool all_empty(){

    if(List_count(&p0_list) == 0 && List_count(&p1_list) == 0 && List_count(&p2_list) == 0 ){
        return true;
    }
    return false;
}

//create a process and put it on
//the appropriate ready Q.
int Create(int priority){
    process++;
    struct PCB *new_pcb = malloc(sizeof(struct PCB));

    new_pcb->priority = priority;
    new_pcb->pid = process;
    new_pcb->p_state = WAITING;


    if(process == 1){
        INIT = new_pcb;
        current  = INIT;
        INIT->p_state = RUNNING;
        List_prepend(&pcbs, new_pcb);
        return 0;//success
    }//else handle the creation of a real process

    List_prepend(&pcbs, new_pcb);

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


    //process is currently running
    if(current->pid = pid){
        if(List_count(&p0_list) != 0){

            current = List_trim(&p0_list);

        }else if(List_count(&p1_list) != 0){

            current = List_trim(&p1_list);
            
        }else if(List_count(&p2_list)!= 0){

            current = List_trim(&p2_list);
        }
        //if all queues are empty switch back to the INIT process
        else if(all_empty() == true){
                current = INIT;
        }
        printf("Current process updated. Now running %d\n", current->pid);
        return 1;
    } 

    while(temp1 != NULL){
        if(temp1->pid == pid){
            printf("Process found in priority 0 queue. Process ID %d deleted\n", temp1->pid);
            List_remove(&p0_list);
            //<-2-4->

            //if all queues are empty switch back to the INIT process
            if(all_empty() == true){
                current = INIT;
            }
            printf("Current process updated. Now running %d\n", current->pid);
            return 1;//found and removed
        }
        temp1  = List_next(&p0_list);
    }
    while(temp2 != NULL){
        if(temp2->pid == pid){
            printf("Process found in priority 1 queue. Process ID %d deleted\n", temp2->pid);
            List_remove(&p1_list);

            //if all queues are empty switch back to the INIT process
            if(all_empty() == true){
                current = INIT;
            }
            printf("Current process updated. Now running %d\n", current->pid);
            return 1;//found and removed
        }
        temp2  = List_next(&p1_list);   
    }
    while(temp3 != NULL){
        if(temp3->pid == pid){
            printf("Process found in priority 2 queue. Process ID %d deleted\n", temp3->pid);
            List_remove(&p2_list);

            //if all queues are empty switch back to the INIT process
            if(all_empty() == true){
                current = INIT;
            }
            printf("Current process updated. Now running %d\n", current->pid);
            return 1;//found and removed
        }
        temp3  = List_next(&p2_list);
    }
    return 0; //nothing found
}

//kill the currently running
//process.
int Exit(){
    //If the process is the INIT call quantum
    if(current->pid ==1){
        printf("Cannot Kill the INIT process.\n");
        return 1;
    }
    //Check if the process about to be killed has a message
        //-> If they wish to continue with kill
        //->If they do not wish to kill
    
    //call quantum
    Kill(current->pid);//kill the son of a bitch!!!!
    return 1;
}

//time quantum of running
//process expires.
int Quantum(){
    printf("Quantum expired!\n");
    printf("Process with ID %d is giving the CPU to", current->pid);
    struct PCB * temp = current;
    //first step
    //check if there are any processes waiting that can replace the currently running process
    //if not, and if the current process hasn't been blocked, then we keep running the current process
    if((List_count(&p0_list) != 0 || List_count(&p1_list) != 0 || List_count(&p2_list) != 0)){
        //if we make inside this if block that means there is another process on one of the lists 
        //meaning we have at least one process guaranteed to replace the current running process

        //now we check which list has the new process
        //we are guaranteed one process as we made it into the if
        if(List_count(&p0_list) != 0){

            current = List_trim(&p0_list);

        }else if(List_count(&p1_list) != 0){

            current = List_trim(&p1_list);

        }else{
            current = List_trim(&p2_list);
        }


        //we must place the running process back on the correct list if it hasn't been blocked
        if(temp->p_state != BLOCKED && temp->pid != 1){
            if(temp->priority == 0){

                List_prepend(&p0_list, temp);

            }else if(temp->priority == 1){

                List_prepend(&p1_list, temp);

            }else{

                List_prepend(&p2_list, temp);
            }
        }

    }else if(current->p_state == BLOCKED){
        //if we make it inside this if else block then there are no other process available
        //and the current process is being blocked on some condition
        //thus we must switch back to the INIT process
        current = INIT;
    }
    printf(" process %d\n", current->pid);
    return 1;
}

//send a message to another
//process - block until reply
int Send(int pid, char* msg){

    //if the message is too long we will not send it
    if(strlen(msg) > 40){
        return -1;
    }
    
    struct PCB* temp0 = List_first(&p0_list);
    struct PCB* temp1 = List_first(&p1_list);
    struct PCB* temp2 = List_first(&p2_list);

    //searching for the desired process
    while(temp0 != NULL){

        //process found
        if(temp0->pid == pid){

            printf("Message sent to the process with id %d. Sender is now blocked and waiting for response\n", pid);
            //we block the sender
            current->p_state = BLOCKED;

            //we give the message to the receiver and the ID of the sender
            temp0->msg = msg;
            temp0->sender_id = pid;

            //we add the sender to a blocked queue and 
            List_prepend(&blockedQueue, current);
            Quantum();//Replace the current process as it has been blocked
            return 1; 
        }
        temp0  = List_next(&p0_list);
    }
    while(temp1 != NULL){
        if(temp1->pid == pid){
            printf("Message sent to the process with id %d. Sender is now blocked and waiting for response\n", pid);
            current->p_state = BLOCKED;
            temp1->msg = msg;
            temp1->sender_id = pid;
            List_prepend(&blockedQueue, current);
            Quantum();
            return 1; 
        }
        temp1  = List_next(&p1_list);   
    }
    while(temp2 != NULL){
        if(temp2->pid == pid){
            printf("Message sent to the process with id %d. Sender is now blocked and waiting for response\n", pid);
            current->p_state = BLOCKED;
            temp2->msg = msg;
            temp2->sender_id = pid;
            List_prepend(&blockedQueue, current);
            Quantum();
            return 1; 
        }
        temp2  = List_next(&p2_list);
    }
}

//receive a message - block until
//one arrives
int Receive(){
    if(current->msg != NULL){
        printf("Message received by process %d ", current->sender_id);
        printf("Message received: %s\n", current->msg);
    }else{
        current->p_state = BLOCKED;
        List_prepend(&blockedQueue, current);
        Exit();
    }
}

//unblocks sender and delivers
//reply
int Reply(int pid){
    struct PCB* temp = List_first(&blockedQueue);

    while(temp != NULL){
        if(temp->pid == pid){
            printf("Sending a reply to process with id %d\n", pid);
            temp->p_state = WAITING;
            temp->msg = NULL;
            temp->sender_id = -1;
            List_remove(&blockedQueue);

            if(temp->priority == 0){
                List_prepend(&p0_list, temp);
            }else if(temp->priority == 1){
                List_prepend(&p1_list, temp);
            }else if(temp->priority == 2)
                List_prepend(&p2_list, temp);
            return 1; 
        }
        temp  = List_next(&p0_list);
    }
    printf("Process not found");
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

//DUMMY (for testing purposes only)
void print(List* pList){
    struct PCB *pcb;
    if(pList == NULL){
        printf("No items in the list.\n");
    }else{
        Node* temp = pList->head;
        printf("<-");
        for(int i = 0; i< List_count(pList);i++){
            pcb = temp->item;
            printf("%d-", pcb->pid);
            temp = temp->next;
        }
        printf("> Queue length: %d", List_count(pList));
    }
    printf("\n");
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
    printf("The currently running process: Process %d\n", current->pid);
    return current;
}