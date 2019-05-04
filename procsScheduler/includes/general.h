#ifndef GENERALHEADER
#define GENERALHEADER

#include<stdio.h>
#include<stdlib.h>

#define MAX_PROCESSES_NUM 100

enum state
{
	Submitted, //0
	Ready,	 //1
	Running,   //2
	Blocked,   //3
	Finished   //4
};
typedef enum
{
	FCFS,
	RR
} schedulingType;

typedef struct
{
	int id;
	int brustSize;
	int brust2Size;
	int ioSize;
	int arriveTime;
	int runTime;
	int waitTime;
	int blockedTime;
	int finishTime;
	enum state state;
} process;

typedef struct{
	int readyEnd;
	int readyCount;
	int runningTime;
	int runningCounter;
	int recordedCount;
	int finishedProcs;
	int cycle;
	int cycAdded;
} cycleState;

void storeLog(float logNum, char *logTxt, char *fp);
void addToReadyQueue(process **processes, int procCount, process **ReadyQueue, cycleState * cycstate);
void LogProcsStatus(process **processes, int procCount, int cyc, char *LogFileName);
void parallelBlockIO(process **processes, int procCount, process **ReadyQueue, cycleState *cycstate);
int countFinished(process ** processes,int procCount);
void IncReadyidx(int *readyidx);
void initQueue(process **processes, int count);
void arrangeReadyQueue(process **ReadyQueue, cycleState *cycstate);
void addcycToReady(process ** ReadyQueue, process ** cycReadyQ, cycleState *cycState);

#endif 