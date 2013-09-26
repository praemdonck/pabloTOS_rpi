#ifndef GPIO_H
#define GPIO_H

#define GPIO_LED_OK   16
#define GPIO_LED_ON   0
#define GPIO_LED_OFF  1
#define GPIO_FUNC_IN  0
#define GPIO_FUNC_OUT 1

int gpio_set_function(unsigned int pin, unsigned int function);
int gpio_set(unsigned int pin, unsigned int value);

void blinker(unsigned int t_on, unsigned int t_off, unsigned int blink_time);
void blinker_n(unsigned int t_on, unsigned int t_off, unsigned int num_repeats);
void blink_int(unsigned int number);
#endif
