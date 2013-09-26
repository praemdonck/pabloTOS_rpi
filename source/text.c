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

  for (i = 0; i < FONT_0_HEIGHT; i++)
  {
    temp = font0[symbol_index + i];

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

void text_draw_string(char* string, unsigned int x, unsigned int y, unsigned int colour)
{
  unsigned int temp_x = x;
  while (*string)
  {
    switch (*string)
    {
      case '\n':
        y += FONT_0_HEIGHT;
        break;
      case '\r':
        x = temp_x;
        break;
      default:
        text_draw_character(*string, x, y, colour);
        x += FONT_0_WIDTH;
    }
    string++;
  }
}

