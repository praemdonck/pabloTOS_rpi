#include "gpio.h"
#include "sys_timer.h"

void err_msg_blink(unsigned int code, unsigned int num_repeats)
{
  if (!num_repeats) return;

  blinker_n(50000, 500000, code);

  num_repeats--;
  while (num_repeats > 0)
  {
    sys_timer_wait(2000000);
    blinker_n(50000, 500000, code);
    num_repeats--;
  }
}

