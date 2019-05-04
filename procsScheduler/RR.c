#include <general.h>
#include <RR.h>


int RunRR(process **processes, int procCount, int quantumTime)
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

	char *LogFileName = "outputRR.txt";
	while (1)
	{   
		/* This is a cycle */
		/* add the cycState->readyCount processes to cycState->readyCount queue */
		if (cycState->recordedCount < procCount) 
			addToReadyQueue(processes, procCount, cycReadyQ, cycState);

		addcycToReady(ReadyQueue, cycReadyQ, cycState);


		/* Run the process 1 quatum time  */
		while (cycState->readyCount > 0)/* run only if there is processses in the readyqueue */
		{
			ReadyQueue[cycState->runningCounter]->state = Running; /* set the current process in the queue to running*/
			
			if (ReadyQueue[cycState->runningCounter]->brustSize > 0 && (cycState->runningTime < quantumTime))
			{
				
				ReadyQueue[cycState->runningCounter]->brustSize--;
				cycState->runningTime++;						   /* the process is still running */
				ReadyQueue[cycState->runningCounter]->runTime++; //store the run time of the process
				break;
			}
			else if( (ReadyQueue[cycState->runningCounter]->ioSize > 0) && (ReadyQueue[cycState->runningCounter]->brustSize == 0) && (ReadyQueue[cycState->runningCounter]->state != Blocked) )
			{
				/* put it in the blocked state after it finishes */
				ReadyQueue[cycState->runningCounter]->state = Blocked;
				cycState->readyCount--;

				IncReadyidx(&cycState->runningCounter);			
				cycState->runningTime = 0;
			}else if ((ReadyQueue[cycState->runningCounter]->brust2Size > 0) && (ReadyQueue[cycState->runningCounter]->brustSize == 0) && (cycState->runningTime < quantumTime))
			{
				ReadyQueue[cycState->runningCounter]->brust2Size--;
				cycState->runningTime++;
				ReadyQueue[cycState->runningCounter]->runTime++; //store the run time of the process
				break;
			}else if(cycState->runningTime >= quantumTime && (ReadyQueue[cycState->runningCounter]->brust2Size > 0 || ReadyQueue[cycState->runningCounter]->brustSize > 0)){
				/* finished quantum, still needs to run, 
				 * add it to the end of the cycState->readyCount queue and update the cycState->readyCount queue
				 * */
				
				cycReadyQ[cycState->cycAdded] = ReadyQueue[cycState->runningCounter];
				cycReadyQ[cycState->cycAdded]->state = Ready;

				cycState->cycAdded++;
				cycState->runningTime = 0;
				cycState->readyCount--;
				IncReadyidx(&cycState->runningCounter);
			}
			else //if(ReadyQueue[cycState->runningCounter]->ioSize == -1 && ReadyQueue[cycState->runningCounter]->brust2Size == 0 && ReadyQueue[cycState->runningCounter]->brustSize == 0 )
			{
				/**/
				
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
		LogProcsStatus(processes, procCount, cycState->cycle, LogFileName);


		/* Parallel block */
		parallelBlockIO(processes, procCount, cycReadyQ, cycState);


		cycState->cycle++;
	}
	return cycState->cycle - 1;
}
