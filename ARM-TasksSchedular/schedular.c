#include "schedular.h"

void CreateTask(uint8_t Taskindex,pft TaskFn,int period,uint8_t priority){
    Tasks[Taskindex].TaskFn = TaskFn;
    Tasks[Taskindex].Period = period; 
    Tasks[Taskindex].priority = priority;
    Tasks[Taskindex].state = IDLE;
}

void StartSchedule(){
		/* These Configuration are for microcontroller TivaC-tm4c123fg6pm. */

    /*enable interrupt reg for Timer0A */
    NVIC_EN0_R |= (1<<19);

    /* Enable Timer 0 */
    SYSCTL_RCGCTIMER_R |= (1<<0);
    /* Disable timer A */
    TIMER0_CTL_R &= ~(1<<0);
    /* Timer A 32 bit mode*/
    TIMER0_CFG_R = 0x00;

    /* timer A mode periodic | count up */
    TIMER0_TAMR_R |= (1<<1) | (1 << 4) ; 
		TIMER0_TAILR_R = 160000; //16MHZ clock >> 10ms TickTime

    /*enable interrupt in timer A */
    TIMER0_IMR_R |= (1<<0);

    /* Enable timer A */
    TIMER0_CTL_R |= (1<<0);

}


volatile void schedualrISR(){
    static int counter = 1;
    uint8_t TasksToDo[TasksCount];

    uint8_t active = 0;
    uint8_t TaskNum = 0,j;
    uint8_t index = 0;
    uint8_t swapTmp;
    for(TaskNum = 0; TaskNum < TasksCount;TaskNum++){
        if ( Tasks[TaskNum].state == RUNNING ){
            active = 1;
        }
        if ( ( ( counter % (Tasks[TaskNum].Period / TickTime) )  == 0 ) | ( Tasks[TaskNum].state == READY ) ){
            Tasks[TaskNum].state = READY;
            TasksToDo[index] = TaskNum;
            index++; /*now we have working tasks in an array */
        }
    }
    if ( index > 0){
        if ( active == 0 ){
            /* arrange tasks using priority */
            for(TaskNum = 0; TaskNum < index-1;TaskNum++){
                for(j = TaskNum+1; j < index;j++){
                    if( Tasks[TasksToDo[TaskNum]].priority < Tasks[TasksToDo[j]].priority ){
                        /*swap task index*/
                        swapTmp = TasksToDo[TaskNum];
                        TasksToDo[TaskNum] = TasksToDo[j];
                        TasksToDo[j] = swapTmp;
                    }
                }
              }


        /* run task with highest priority */
        Tasks[TasksToDo[0]].state = RUNNING;
        Tasks[TasksToDo[0]].TaskFn();
        Tasks[TasksToDo[0]].state = IDLE;
        }
    }else{

    }
    counter++;
    TIMER0_ICR_R |= (1<<0);

}
