#include "graphical.h"
                         
#define FONT_0_WIDTH     8
#define FONT_0_HEIGHT    16
extern char font0[];


extern void print_number(unsigned int number, unsigned int x, unsigned int y);


void text_draw_character(unsigned int symbol, unsigned int x, unsigned int y, unsigned int colour)
{

  unsigned int* base_ptr;
  unsigned int symbol_index;
  unsigned int temp, i, j;

  if (symbol > 127)
    return;

  symbol_index = symbol * FONT_0_HEIGHT;
  base_ptr = graph_get_xy_address(x, y);

  print_number(symbol_index, 500, 550);

  for (i = 0; i < FONT_0_HEIGHT; i++)
  {
    temp = font0[symbol_index + i];
    print_number(temp, 500, 570 + i * 20);

    for (j = 0; j < FONT_0_WIDTH; j++)
    {
      if (temp & 0x01)
        *base_ptr = colour;

      base_ptr++;
      temp >>= 1;
    }

    base_ptr += (graph_get_screen_width() - FONT_0_WIDTH);
  }
}

