#ifndef SCHEDULAR_HEADER

#define SCHEDULAR_HEADER

/* Timer registers (TIMER0)*/
#define SYSCTL_RCGCTIMER_R      (*((volatile uint32_t *)0x400FE604))

#define TIMER0_CFG_R            (*((volatile uint32_t *)0x40030000))
#define TIMER0_TAMR_R           (*((volatile uint32_t *)0x40030004))
#define TIMER0_CTL_R            (*((volatile uint32_t *)0x4003000C))
#define TIMER0_IMR_R            (*((volatile uint32_t *)0x40030018))
#define TIMER0_ICR_R            (*((volatile uint32_t *)0x40030024))
#define TIMER0_TAILR_R          (*((volatile uint32_t *)0x40030028))

/* Interrupt */
#define NVIC_EN0_R              (*((volatile uint32_t *)0xE000E100))

#define TickTime 10 /* TickTime 10 ms*/
#define TasksCount 3u

typedef void (*pft)(void);
typedef enum {IDLE = 0,RUNNING,READY} TaskStateType;

typedef struct {
    pft TaskFn;
    int Period;
    uint8_t priority;
    TaskStateType state;
} TaskConfigType;


TaskConfigType Tasks[TasksCount];

void CreateTask(uint8_t Taskindex,pft TaskFn,int period,uint8_t priority);
void StartSchedule();

#endif
