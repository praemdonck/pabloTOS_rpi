#ifndef SYS_TIMER_H
#define SYS_TIMER_H                        

#define SYS_TIMER_CYCLES_PER_SEC  1000000

void sys_timer_wait(unsigned int wait_period);
unsigned long sys_timer_get_counter(void);

#endif
