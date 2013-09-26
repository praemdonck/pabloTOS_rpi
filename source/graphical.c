#include "err_msg.h"
#include "gpio.h"

typedef struct
{
  unsigned int* fb_addr; 
  unsigned int width; 
  unsigned int height;
  unsigned int bit_depth;
} graph_screen_info_t;

graph_screen_info_t graph_screen_info = {1, 0, 0, 0};

unsigned int graph_init(unsigned int* fb_addr, unsigned int width, 
                        unsigned int height, unsigned int bit_depth)
{
  if (fb_addr == 0 || width > 4096 || height > 4096 || bit_depth > 32)
    return 0;

  graph_screen_info.fb_addr = fb_addr; 
  graph_screen_info.width = width; 
  graph_screen_info.height = height;
  graph_screen_info.bit_depth = bit_depth;

  //blink_int(graph_screen_info.fb_addr);
  //sys_timer_wait(4000000);
  //blink_int(graph_screen_info.width);
  //sys_timer_wait(4000000);

  return 1;
}

unsigned int graph_get_screen_width(void)
{
  return graph_screen_info.width;
}

unsigned int graph_get_screen_height(void)
{
  return graph_screen_info.height;
}

unsigned int* graph_get_xy_address(unsigned int x, unsigned int y)
{
  return graph_screen_info.fb_addr + y * graph_screen_info.width + x;
}

void graph_set_pixel(unsigned int x, unsigned int y, unsigned int colour)
{
  *graph_get_xy_address(x, y) = colour;
}

void graph_draw_dash(unsigned int x, unsigned int y, unsigned int length)
{
  unsigned int i;
  for (i = 0; i < length; i++)
    graph_set_pixel(x + i, y, 0xFF0000FF);
}


void graph_draw_number(unsigned int number, unsigned int x, unsigned int y)
{
   unsigned int nibble, i, j;
   for (i = 0; i < 8; i++)
   {
     nibble = number;
     nibble >>= 28;
     number <<= 4;

     if (nibble == 0)
     {
       graph_draw_dash(x, y, 10);
       x += 15;
     }
     else
     {
       for (j = 0; j < nibble; j++)
       {
         graph_draw_dash(x, y, 5);
         x += 7;
       }
       x += 3;
     }
   }
}
  
                                                     
unsigned int graph_draw_rect(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int colour)
{
  unsigned int* column_address = graph_get_xy_address(x, y);
  unsigned int* temp_address;
  unsigned int i, j;

  for (i = 0; i < height; i++)
  {
    temp_address = column_address;
    column_address += graph_screen_info.width;

    for (j = 0; j < width; j++)
    {
      *temp_address = colour;
      temp_address++;
    }
  }
  return 1;
}
