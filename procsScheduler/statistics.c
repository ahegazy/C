#include <general.h>
#include <statistics.h>

void statistics(process **processes, int procCount, int finishTime, char *LogFileName)
{
	int proc;
	//    int tTAT1=0;//Total turnaround time;
	//    int tTAT2=0;//Total turnaround time;
	int TAT = 0;
	int Twait = 0; //total Wait time;
	int cpuBusy = 0;
	float cpuUtl = 0.0;
	storeLog(-1, "\n\n", LogFileName);
	storeLog(-1, "Finishing Time: ", LogFileName);
	storeLog(finishTime, "\n", LogFileName);

	for (proc = 0; proc < procCount; proc++)
	{
		cpuBusy = cpuBusy + processes[proc]->runTime;
	}
	cpuUtl = (float)cpuBusy / (float)(finishTime + 1);
	storeLog(-1, "CPU Utilization: ", LogFileName);
	storeLog(cpuUtl, "\n", LogFileName);

	for (proc = 0; proc < procCount; proc++)
	{
		//TAT = processes[proc]->runTime + processes[proc]->waitTime + processes[proc]->blockedTime;
		TAT =  processes[proc]->finishTime - processes[proc]->arriveTime + 1;
		storeLog(-1, "Turnaround time of Process ", LogFileName);
		storeLog(processes[proc]->id, ": ", LogFileName);
		storeLog(TAT, " \n", LogFileName);
		/*        tTAT2 = tTAT2 + processes[proc]->finishTime - processes[proc]->arriveTime + 1;
        Twait = Twait + processes[proc]->waitTime;
        tTAT1 = tTAT1 + TAT;*/
	}
}
