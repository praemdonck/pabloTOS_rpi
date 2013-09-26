#ifndef GRAPHICAL_H
#define GRAPHICAL_H
unsigned int graph_draw_rect(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int colour);
unsigned int graph_init(unsigned int* fb_addr, unsigned int width, 
                        unsigned int height, unsigned int bit_depth);
void graph_set_pixel(unsigned int x, unsigned int y, unsigned int colour);
void graph_draw_number(unsigned int number, unsigned int x, unsigned int y);
unsigned int graph_get_screen_width(void);
unsigned int graph_get_screen_height(void);
#endif
