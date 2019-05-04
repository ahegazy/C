#include <general.h>
#include <FCFS.h>
#include <RR.h>
#include <statistics.h>

int main(int argc, char *argv[])
{
	process *p;
	process *processes[MAX_PROCESSES_NUM];

	int id, brustSize, ioSize, arriveTime;
	int procCount = 0;
	schedulingType type; //0:FCFS, 1:RR
	int q;				 /*quantum time x cycles for RR only*/
	int eofcheck = 0;
	char *file;
	FILE *fp;
	int finishTime = 0;
	char *LogFileName;

	if (argc < 3 || ((*(argv[1]) - '0') == 1 && argc < 4))
	{
		fprintf(stderr, "No suffecient arguments\nPlease use `scheduler [FCFS=0,RR=1] quantumTime[if RR] inputFilename*\nExitting. \n");
		return 1;
	}
	else
	{
		type = *(argv[1]) - '0';
		q = type ? (*(argv[2]) - '0') : 0;
		file = type ? argv[3] : argv[2];
	}

	fp = fopen(file, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Error, File %s not found\n", file);
		return 2;
	}
	/* Get the processes in an array */

	do
	{
		eofcheck = fscanf(fp, "%d %d %d %d", &id, &brustSize, &ioSize, &arriveTime);
		if (eofcheck == -1)
		{
			break;
		}
		p = (process *)malloc(sizeof(process));
		p->id = id;
		p->brustSize = brustSize;
		p->ioSize = ioSize;
		p->brust2Size = ioSize ? brustSize : 0;
		p->arriveTime = arriveTime;
		p->runTime = 0;
		p->waitTime = 0;
		p->blockedTime = 0;
		p->state = Submitted;
		processes[procCount] = p;

		procCount = procCount + 1;
	} while ((eofcheck == 4) && (procCount < MAX_PROCESSES_NUM));
	fclose(fp);
	
//	initQueue(processes, procCount);
	
	if (type == FCFS)
	{
		finishTime = RunFCFS(processes, procCount);
		LogFileName = "outputFCFS.txt";
	}
	else if (type == RR)
	{
		finishTime = RunRR(processes, procCount, q);
		LogFileName = "outputRR.txt";
	}
	statistics(processes, procCount, finishTime, LogFileName);
	return 0;
}
