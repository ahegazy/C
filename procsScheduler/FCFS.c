#include <general.h>
#include <FCFS.h>


int RunFCFS(process **processes, int procCount)
{ /* returns finish time */

	process *ReadyQueue[MAX_PROCESSES_NUM];
	process *cycReadyQ[MAX_PROCESSES_NUM];

	cycleState * cycState = (cycleState *) malloc(sizeof(cycleState));

	cycState->readyEnd = -1; /* keep track of max index of ready queue s*/
	cycState->readyCount = 0;/* keep track of # of proccesses that are ready*/
	cycState->runningTime = 0; /* keep the running time of each proccess */
	cycState->recordedCount = 0; /* number of added processes from the total */
	cycState->runningCounter = 0; /* keep track of # of processes that ran or is running */
	cycState->finishedProcs = 0;
	cycState->cycle = 0;
	cycState->cycAdded = 0; /* added processes in this cycle */

	char *LogFileName = "outputFCFS.txt";

	while (1)
	{   /* This is a cycle */
		/* add the ready processes to ready queue */
		/* Run the process till it finishes, FIFO */
		if (cycState->recordedCount < procCount) 
			addToReadyQueue(processes, procCount, cycReadyQ, cycState);

		addcycToReady(ReadyQueue, cycReadyQ, cycState);


		/* Run the process 1 quatum time  */
		while (cycState->readyCount > 0)/* run only if there is processses in the readyqueue */
		{
			ReadyQueue[cycState->runningCounter]->state = Running; /* set the current process in the queue to running*/

			if (ReadyQueue[cycState->runningCounter]->brustSize > 0)
			{
				ReadyQueue[cycState->runningCounter]->brustSize--;
				ReadyQueue[cycState->runningCounter]->runTime++; //store the run time of the process
				break;
			}
			else if( ReadyQueue[cycState->runningCounter]->ioSize > 0)
			{
					/* put it in the blocked state after it finishes */
				ReadyQueue[cycState->runningCounter]->state = Blocked;
				cycState->readyCount--;

				IncReadyidx(&cycState->runningCounter);			
				cycState->runningTime = 0;
			}else if (ReadyQueue[cycState->runningCounter]->brust2Size > 0)
			{
				ReadyQueue[cycState->runningCounter]->brust2Size--;
				ReadyQueue[cycState->runningCounter]->runTime++; //store the run time of the process
				break;
			}
			else
			{
				ReadyQueue[cycState->runningCounter]->state = Finished;
				ReadyQueue[cycState->runningCounter]->finishTime = cycState->cycle - 1;

				cycState->finishedProcs++;
				cycState->readyCount--;
				cycState->runningTime = 0;
				/* make the next process run if available */
				IncReadyidx(&cycState->runningCounter);			
			}
		}

		if (cycState->finishedProcs == procCount)
		{
			break;
		}

		LogProcsStatus(processes, procCount, cycState->cycle , LogFileName);
		/* Parallel block */
		parallelBlockIO(processes, procCount, cycReadyQ, cycState);
		/*
        for(i=0;i<procCount;i++){
            printf("pid: %d -",processes[i]->id);
            printf("BrustSize %d - ",processes[i]->brustSize);
            printf("io %d ",processes[i]->ioSize);
            printf("arrive %d -",processes[i]->arriveTime);
            printf("running %d -",processes[i]->runTime);
            printf("wait %d -",processes[i]->waitTime);
            printf("blocked %d -",processes[i]->blockedTime);
            printf("state %d ",processes[i]->state);
            printf("\n");
        }
        */
		cycState->cycle ++;
	}
	return cycState->cycle - 1;
}
