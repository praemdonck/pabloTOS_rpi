#define SYS_TIMER_BASE_ADDRESS   0x20003000
#define SYS_TIMER_CLO_OFFSET     4
#define SYS_TIMER_CHI_OFFSET     8

unsigned long sys_timer_get_counter(void)
{
//    unsigned int clo = *(unsigned int*)(SYS_TIMER_BASE_ADDRESS + SYS_TIMER_CLO_OFFSET);
//    unsigned long chi = *(unsigned int*)(SYS_TIMER_BASE_ADDRESS + SYS_TIMER_CHI_OFFSET);
//
//    return (chi << 32) + clo;
    volatile unsigned int* counter_low_ptr = (unsigned int*)(SYS_TIMER_BASE_ADDRESS + SYS_TIMER_CLO_OFFSET);
    volatile unsigned int* counter_high_ptr = SYS_TIMER_BASE_ADDRESS + SYS_TIMER_CHI_OFFSET;

    unsigned int counter_hi = *counter_high_ptr;
    unsigned int counter_low = *counter_low_ptr;
    
    // Check the high counter in case it incremented while reading the low part
    unsigned int new_counter_hi = *counter_high_ptr;
    
    unsigned long result;

    // If high counter incremented read low counter again
    if (new_counter_hi != counter_hi)
      counter_low = *counter_low_ptr;

    result = new_counter_hi;
    result <<= 32;
    result += counter_low;

    return result;
}


void sys_timer_wait(unsigned int wait_period)
{
    unsigned long stop_time = sys_timer_get_counter() + wait_period;

    while (sys_timer_get_counter() < stop_time);
}

