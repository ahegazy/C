
# Processes Scheduling Utility

A command line utility used to simulate First Come First Served (FCFS) and Round Robin (RR) processes scheduling technique.

## Specifications
-The program reads an input file that lists the information of the processes that need to be scheduled to run on the processor.
-It simulates scheduling these processes using one of the two algorithms and output the state of each process at every cycle time. 
-It maintains statistics about the processes and output them after the simulation finishes.

## Compilation 
- ```make``` will generate the binary file you can use. 
- Or import the project files in you favorite IDE and compile it however you want.

## Usage
```
scheduler OPT quantumTime inputFilename*
 ```
- where OPT can be 0 or 1 as follows
	- 0 for FCFS sceduling of the processes.
    - 1 for RR scheduling
- filename: the input file that lists the information of the processes.
    - Each line in the input file contains four numbers interpreted as follows :
        - Process ID
        - CPU time : this is the time the process needs to execute on the CPU to complete. It is represented as a number of simulation cycles.
        - I/O time : his is the time the process will need to wait for I/O. Note that this is the number of simulation cycles a process will remain blocked, and you can safely assume that processes do not compete for the I/O devices.
        - Arrival time:this is the time the process becomes available in the system.It is represented as simulation time cycle.
        - A process arriving at the system will run as follows. It will need to run for CPU time, block for I/O time, and then run for CPU time again. Note that all the numbers are integers.

## simulation Output 
- The output is a text file, called ouputFCFS.txt or outputRR.txt the output file will be formatted to output two parts .
- The simulation of the scheduling starting from simulation time cycle 0. Every line shows the following:
    - Simulation cycle time.
    - The state of each process: Running, Ready, or Blocked. This should appear as follows: K: STATE to represent the state of process with ID K. Therefore, for a running process 1,it is presented as ``` 1: Running.```
    - Note that at simulation listing, the process that have terminated or that have not arrived yet isnot written.
- Statistics collected about the simulation type, the following is printed:
    - Finishing time. This is the last simulation time at which all the processes have terminated.
    - CPU utilization. This can be calculated as the ratio between the number of the simulation
    - cycles at which the CPU was busy divided by the total number of the simulation cycles.
    - For each process, print the turnaround time. This is calculated as: (the cycle the process finished - the cycle the process arrived +1).

## Examples

### Example 1:
```scheduler 0 processesFile1.txt```
- 0 for FCFS scheduling.

### Example 2:
```scheduler 1 1 processesFile1.txt```
- 1 for RR scheduling
- q=1 for 1 cycle quantum time 

### Example Contents 
- an example [input file](../examples/processesFile1.txt) contents:
``` 
    0 1 2 0
    1 1 1 5
    2 1 1 3
```
- In the above example, process 0 will run for one simulation cycle, then block for two simulation cycles, and finally run for one simulation cycle. The process might wait in the ready queue before being scheduled on the CPU to run. Note that a process added to the list of processes that are blocked for I/O can take any time in this list, and does not have to be removed from it before other processes added to the same list after it. In other words, it is a bad choice to simulate the list of blocked processes as a FIFO queue.