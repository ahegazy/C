#include <general.h>


void addToReadyQueue(process **processes, int procCount, process **ReadyQueue, cycleState * cycstate)
{
//int *readyEnd,int *ready, int recodedCount, int cyc

	int proc;
	for (proc = 0; proc < procCount; proc++)
	{
		if (processes[proc]->arriveTime == cycstate->cycle)
		{
			ReadyQueue[cycstate->cycAdded] = processes[proc];
			ReadyQueue[cycstate->cycAdded]->state = Ready;

			cycstate->cycAdded++;
			cycstate->recordedCount++;
		}
	}
}

void addcycToReady(process ** ReadyQueue, process ** cycReadyQ, cycleState *cycstate){
	int i,j;
	process * swaProc;
	//printf("%d \n",cycstate->cycAdded);
	for(i = 0;i < cycstate->cycAdded-1 ; i++){
		for(j=i+1;j < cycstate->cycAdded; j++){
			/* Arrange by id */
			if(cycReadyQ[i]->id > cycReadyQ[j]->id ){
				swaProc = cycReadyQ[i];
				cycReadyQ[i] = cycReadyQ[j];
				cycReadyQ[j] = swaProc;
			}
		}
	}
	for(i = 0;i < cycstate->cycAdded; i++){
			/* add to ready queue */
			IncReadyidx(&cycstate->readyEnd);

			ReadyQueue[cycstate->readyEnd] = cycReadyQ[i];
			ReadyQueue[cycstate->readyEnd]->state = Ready;
			cycstate->readyCount++;
			cycReadyQ[i] = NULL;
	}
	/*reset the cycle added counter */
	cycstate->cycAdded = 0;
}

void LogProcsStatus(process **processes, int procCount, int cyc, char *LogFileName)
{
	/*status */
	int i;
	storeLog(cyc, " ", LogFileName);
	for (i = 0; i < procCount; i++)
	{
		if (processes[i]->state == Running)
		{
			storeLog(processes[i]->id, NULL, LogFileName);
			storeLog(-1, ": ", LogFileName);
			storeLog(-1, "Running ", LogFileName);
		}
		else if (processes[i]->state == Ready)
		{
			storeLog(processes[i]->id, NULL, LogFileName);
			storeLog(-1, ": ", LogFileName);
			storeLog(-1, "Ready ", LogFileName);
		}
		else if (processes[i]->state == Blocked)
		{
			storeLog(processes[i]->id, NULL, LogFileName);
			storeLog(-1, ": ", LogFileName);
			storeLog(-1, "Blocked ", LogFileName);
		}
	}
	storeLog(-1, " \n", LogFileName);
}
void parallelBlockIO(process **processes, int procCount, process **ReadyQueue, cycleState *cycstate)
{
// int *readyEnd, int *ready
 	int i;
	for (i = 0; i < procCount; i++)
	{
		if (processes[i]->state == Blocked)
		{
			processes[i]->ioSize--;
			processes[i]->blockedTime++;
			if (processes[i]->ioSize == 0)
			{
				ReadyQueue[cycstate->cycAdded] = processes[i];
				ReadyQueue[cycstate->cycAdded]->state = Ready;

				cycstate->cycAdded++;
			}
		}
	}
}
void IncReadyidx(int *readyidx){
	if ( (*readyidx) == MAX_PROCESSES_NUM - 1 ){
	/* start over the readyqueue */
		(*readyidx) = 0;
	} else {
		(*readyidx)++;				
	}
}
void initQueue(process **processes, int count)
{
	int i, j, proc;
	process *swapProc;

	for (i = 0; i < count; i++)
	{
		for (j = i + 1; j < count; j = j + 1)
		{
			if (processes[i]->arriveTime > processes[j]->arriveTime)
			{
				swapProc = processes[i];
				processes[i] = processes[j];
				processes[j] = swapProc;
			}else if ( (processes[i]->arriveTime == processes[j]->arriveTime) && (processes[i]->id > processes[j]->id)){
				swapProc = processes[i];
				processes[i] = processes[j];
				processes[j] = swapProc;
			}
		}
	}
}
int countFinished(process ** processes,int procCount){
	int i,finishedProcs = 0;
	for (i = 0; i < procCount; i++)
	{
		/* calculate wait time */
		if (processes[i]->state == Ready)
		{
			processes[i]->waitTime++;
		}else if (processes[i]->state == Finished)
		{
			finishedProcs++;
		}
	}
	return finishedProcs;
}
void arrangeReadyQueue(process **ReadyQueue, cycleState *cycstate){
	int i,j;
	process *swapProc;

	if(cycstate->readyEnd >= cycstate->cycAdded) {
		i = cycstate->readyEnd - cycstate->cycAdded;
	}else{
		
	}
	
	for(;i < cycstate->cycAdded;i++){
		for(j=i+1;i<cycstate->cycAdded;j++){
			if( ReadyQueue[i]->id > ReadyQueue[j]->id){
				swapProc = ReadyQueue[i];
				ReadyQueue[i] = ReadyQueue[j];
				ReadyQueue[j] = swapProc;
			}
		}

	}
}
void storeLog(float logNum, char *logTxt, char *LogFileName)
{
	FILE *fp;
	int a = (int) logNum;

	fp = fopen(LogFileName, "a");
	if (logNum != -1 && logTxt != NULL)
	{
		if(a - logNum == 0){
			fprintf(fp, "%d %s", a, logTxt);
		}else{
			fprintf(fp, "%.2f %s", logNum, logTxt);
		}
	}
	else if (logNum == -1)
	{
		fprintf(fp, "%s", logTxt);
	}
	else if (logTxt == NULL)
	{
		if(a - logNum == 0){
			fprintf(fp, "%d ", a);
		}else{
			fprintf(fp, "%.2f ", logNum);
		}
	}
	else
	{
		printf("didnot write log\n");
	}
	fclose(fp);
}
