# ARM 
Using ARM TivaC-tm4c123fg6pm microcontroller local Timer, and ISR interrupt function to create a Tasks schedular with a 10ms tick time.

## Specs
1. Tasks priority.
2. Tasks period.
3. 3 state for every Task.
4. Tasks/functions cannot stop other function even if it has higher priority. -Non preemptive-
5. If a task is due its state is changed to `READY` and it's launched next tick.
6. If two tasks are due the higher priority task will launch first and the other held to next Tick.
7. The code is configured for 16 MHZ Clock cycle device.

## Usage 
1. Include the ```schedular.h``` header file.
2. Modify the number of tasks using the ``` TasksCount ``` macro in the header File.
2. Use function ``` CreateTask(); ``` to create your task giving it your task index,function,period and priority.
3. Add the ``` schedualrISR(); ``` function to your vector table in Timer0A index.
4. Use ```StartSchedule();``` function to start the schedular.
