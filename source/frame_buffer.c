#include "sys_timer.h"
#include "gpio.h"
#include "mailbox.h"
#include "err_msg.h"

typedef struct
{
  unsigned int width;
  unsigned int height;
  unsigned int v_width;
  unsigned int v_height;
  unsigned int gpu_pitch;
  unsigned int bit_depth;
  unsigned int X;
  unsigned int Y;
  unsigned int gpu_ptr;
  unsigned int gpu_size;
} frame_buffer_info_t;

frame_buffer_info_t frame_buffer_info __attribute__ ((aligned (16))) = {1024, 768, 1024, 768, 0, 32, 0, 0, 0, 0};

unsigned int* frame_buffer_init(unsigned int width, unsigned int height, unsigned int bit_depth)
{
    if (width > 4096 || height > 4096 || bit_depth > 32)
      return 0;

    frame_buffer_info.width = width;
    frame_buffer_info.height = height;
    frame_buffer_info.v_width = width;
    frame_buffer_info.v_height = height;
    frame_buffer_info.gpu_pitch = 0;
    frame_buffer_info.bit_depth = bit_depth;
    frame_buffer_info.X = 0;
    frame_buffer_info.Y = 0;
    frame_buffer_info.gpu_ptr = 0;
    frame_buffer_info.gpu_size = 0;

    //blink_int((unsigned int*)((void*)&frame_buffer_info + 0x40000000));
    //sys_timer_wait(2000000);

    //mailbox_write((unsigned int*)&frame_buffer_info, 1);
    mailbox_write((unsigned int*)((void*)&frame_buffer_info + 0x40000000), 1);


    if (mailbox_read(1) != 0)
    {
      err_msg_blink(2, 3);
      return 0;
    }

    while (!frame_buffer_info.gpu_ptr)
    {
      err_msg_blink(2, 1);
      sys_timer_wait(2000000);
    }
    //sys_timer_wait(2000000);

    return (unsigned int*)frame_buffer_info.gpu_ptr;
}


//extern frame_buffer_info_t* FrameBufferInfo;
//
//unsigned int* frame_buffer_init(unsigned int width, unsigned int height, unsigned int bit_depth)
//{
//    volatile unsigned int* temp;
//
//    if (width > 4096 || height > 4096 || bit_depth > 32)
//      return 0;
//
//    FrameBufferInfo->width = width;
//    FrameBufferInfo->height = height;
//    FrameBufferInfo->v_width = 0;
//    FrameBufferInfo->v_height = 0;
//    FrameBufferInfo->gpu_pitch = 0;
//    FrameBufferInfo->bit_depth = bit_depth;
//    FrameBufferInfo->X = 0;
//    FrameBufferInfo->Y = 0;
//    FrameBufferInfo->gpu_ptr = 0;
//    FrameBufferInfo->gpu_size = 0;
//
//    mailbox_write((unsigned int*)FrameBufferInfo, 1);
//
//    if (!mailbox_read(1))
//    {
//      err_msg_blink(2, 3);
//      return 0;
//    }
//
//    temp = &FrameBufferInfo->gpu_ptr;
//    sys_timer_wait(1000000);
//    //while (!FrameBufferInfo->gpu_ptr)
//    while (!*temp)
//    {
//      err_msg_blink(2, 1);
//      sys_timer_wait(2000000);
//    }
//    //sys_timer_wait(2000000);
//
//    //return (unsigned int*)FrameBufferInfo->gpu_ptr;
//    return (unsigned int*)*temp;
//}
