#include "gpio.h"
#include "sys_timer.h"
#include "err_msg.h"
#include "frame_buffer.h"
#include "graphical.h"
#include "text.h"
#include <stdio.h>


extern unsigned int* InitialiseFrameBuffer(unsigned int width, unsigned int height, unsigned int bit_depth);                
extern DrawCharacter(unsigned int character, unsigned int x, unsigned int y);
extern unsigned int getPC();

void print_number(unsigned int number, unsigned int x, unsigned int y);

unsigned int my_num = 5;

int main(void)
{
  int* temp_ptr;
  int i;
  char my_string[100];

  extern unsigned int font[];
  extern int frame_buffer_info;                      

  //while (1)
  {
    //err_msg_blink(1, 5);
    //sys_timer_wait(5 * SYS_TIMER_CYCLES_PER_SEC);

    //err_msg_blink(2, 5);
    //sys_timer_wait(5 * SYS_TIMER_CYCLES_PER_SEC);

    //err_msg_blink(3, 5);
    //sys_timer_wait(5 * SYS_TIMER_CYCLES_PER_SEC);

    //err_msg_blink(4, 1);
    //sys_timer_wait(5 * SYS_TIMER_CYCLES_PER_SEC);


    //blinker_n(200000, 200000, 5);
    //sys_timer_wait(2000000);
    //blink_int(0x12345678);
    //sys_timer_wait(5000000);
    //blink_int(0x2000B880);
    //sys_timer_wait(2000000);
    //blinker_n(50000, 500000, 5);
    //sys_timer_wait(2000000);
  }

  //err_msg_blink(1, 1);
  temp_ptr = frame_buffer_init(1680, 1050, 32);
  //temp_ptr = InitialiseFrameBuffer(1680, 1050, 32);
  //err_msg_blink(2, 1);
  graph_init(temp_ptr, 1680, 1050, 32);
  //err_msg_blink(3, 1);

  sys_timer_wait(2000000);

  graph_draw_rect(100, 100, 100, 100, 0xFFFF0000);
  graph_draw_rect(300, 100, 100, 100, 0xFFFF0000);
  graph_draw_rect(500, 100, 100, 100, 0xFFFF0000);
  graph_draw_rect(700, 100, 100, 100, 0xFFFF0000);
  graph_draw_rect(900, 100, 100, 100, 0xFFFF0000);

  //for (i = 0; i < 100; i++)
  //  graph_set_pixel(i, 300, 0xFF0000FF);


  temp_ptr = (int*)&frame_buffer_info;

  print_number((unsigned int)temp_ptr, 100, 300);
  print_number((unsigned int)((void*)&frame_buffer_info + 0x40000000), 100, 340);


  text_draw_string("Hello World\n\rI'm a very sad programmer", 500, 500, 0xFFFF00FF);
  sprintf(my_string, "Hex Number: 0x%x", 1234432);

  //graph_draw_number((unsigned int)&my_num, 100, 390);
  //graph_draw_number(my_num, 100, 400);
  //my_num = 10;
  graph_draw_number(getPC(), 100, 410);
  print_number(getPC(), 100, 430);
  print_number(my_num, 100, 450);
  //for (i = 0; i < 50; i++)
  //  graph_draw_number(((unsigned int*)0x8058)[i], 100, 300 + i * 10);
 
  //blink_int((int)font);
  //sys_timer_wait(2000000);
  //blink_int((int)&font[261]);
  //sys_timer_wait(2000000);
  DrawCharacter('A', 100, 100);
  DrawCharacter('N', 110, 100);
  DrawCharacter('N', 120, 100);
  DrawCharacter('A', 130, 100);

  //graph_draw_rect(200, 200, 100, 100, 0xFF00FF00);
  //graph_draw_rect(400, 200, 100, 100, 0xFF00FF00);
  //graph_draw_rect(600, 200, 100, 100, 0xFF00FF00);
  //graph_draw_rect(800, 200, 100, 100, 0xFF00FF00);
  //
  //graph_draw_rect(100, 300, 100, 100, 0xFF0000FF);
  //graph_draw_rect(300, 300, 100, 100, 0xFF0000FF);
  //graph_draw_rect(500, 300, 100, 100, 0xFF0000FF);
  //graph_draw_rect(700, 300, 100, 100, 0xFF0000FF);
  //graph_draw_rect(900, 300, 100, 100, 0xFF0000FF);

  //graph_draw_rect(200, 400, 100, 100, 0xFFFFFFFF);
  //graph_draw_rect(400, 400, 100, 100, 0xFFFFFFFF);
  //graph_draw_rect(600, 400, 100, 100, 0xFFFFFFFF);
  //graph_draw_rect(800, 400, 100, 100, 0xFFFFFFFF);

  blinker_n(50000, 500000, 10000);
  return (int)temp_ptr;
}


void print_number(unsigned int number, unsigned int x, unsigned int y)
{
  unsigned int nibble, i, j;

  DrawCharacter('0', x, y);
  x += 10;
  DrawCharacter('x', x, y);
  x += 10;

  for (i = 0; i < 8; i++)
  {
    nibble = number;
    nibble >>= 28;
    number <<= 4;

    if (nibble < 0x0A)
    {
      DrawCharacter(nibble + '0', x, y);
      x += 10;
    }
    else
    {
      DrawCharacter(nibble - 10 + 'A', x, y);
      x += 10;
    }
  }
}

