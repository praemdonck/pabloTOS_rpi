#include "gpio.h"
#include "sys_timer.h"

#define GPIO_BASE_ADDRESS 0x20200000

int gpio_set_function(unsigned int pin, unsigned int function)
{
  unsigned int *gpio_address = (unsigned int*)GPIO_BASE_ADDRESS;
  unsigned int mask = 0x07;
  unsigned int register_field;

  if (pin >= 54 || function >= 7)
    return 0;

  gpio_address += pin / 10;
  register_field = pin % 10;
  mask =~(mask << (register_field * 3));
  *gpio_address &= mask;

  *gpio_address |= (function << (register_field * 3));

  return 1;
}


int gpio_set(unsigned int pin, unsigned int value)
{
  unsigned int *gpio_address = (unsigned int*)GPIO_BASE_ADDRESS;
  unsigned int bit_poker = 0x01;
  unsigned int register_field;

  if (pin >= 54)
    return 0;

  gpio_address += pin / 32;
  register_field = pin & 0x1F;
  bit_poker <<= register_field; 

  if (value)
    gpio_address += 7; // The set register has an offset of 7 ints with respect of base address
  else
    gpio_address += 10; // The clear register has an offset of 10 ints with respect of base address


  *gpio_address |= bit_poker;

  return 1;
}

int test_gpio(void)
{
  return gpio_set_function(16, 1);
}

void blinker_n(unsigned int t_on, unsigned int t_off, unsigned int num_repeats)
{
  if (!num_repeats) return;

  gpio_set_function(GPIO_LED_OK, GPIO_FUNC_OUT);

  gpio_set(GPIO_LED_OK, GPIO_LED_ON);
  sys_timer_wait(t_on);
  num_repeats--;
  while (num_repeats > 0)
  {
    gpio_set(GPIO_LED_OK, GPIO_LED_OFF);
    sys_timer_wait(t_off);
    gpio_set(GPIO_LED_OK, GPIO_LED_ON);
    sys_timer_wait(t_on);
    num_repeats--;
  }
  gpio_set(GPIO_LED_OK, GPIO_LED_OFF);
}

void blinker(unsigned int t_on, unsigned int t_off, unsigned int blink_time)
{
 unsigned long stop_time = sys_timer_get_counter() + 
                           blink_time * SYS_TIMER_CYCLES_PER_SEC;

 gpio_set_function(GPIO_LED_OK, GPIO_FUNC_OUT);

 while (sys_timer_get_counter() < stop_time)
 {
    gpio_set(GPIO_LED_OK, GPIO_LED_ON);
    sys_timer_wait(t_on);
    gpio_set(GPIO_LED_OK, GPIO_LED_OFF);
    sys_timer_wait(t_off);
 }
}


void blink_int(unsigned int number)
{
   unsigned int nibble, i;

   for (i = 0; i < 8; i++)
   {
     nibble = number;
     nibble >>= 28;
     number <<= 4;

     if (nibble == 0)
     {
       gpio_set(GPIO_LED_OK, GPIO_LED_ON);
       sys_timer_wait(SYS_TIMER_CYCLES_PER_SEC);
       gpio_set(GPIO_LED_OK, GPIO_LED_OFF);
     }
     else
     {
       blinker_n(100000, 500000, nibble);
     }
     sys_timer_wait(2 * SYS_TIMER_CYCLES_PER_SEC);
   }
}

