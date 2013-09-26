#include "err_msg.h"
#include "sys_timer.h"
#include "gpio.h"

#define MAILBOX_BASE_ADDRESS   0x2000B880
#define MAILBOX_STATUS_OFFSET  0x00000018
#define MAILBOX_WRITE_OFFSET   0x00000020
#define MAILBOX_MAX_CHANNEL    15
#define MAILBOX_CHANNEL_MASK   0x0000000F
#define MAILBOX_WRITE_READY    0x80000000
#define MAILBOX_READ_READY     0x04000000

extern unsigned int GetMailboxBase(void);

unsigned int mailbox_write(unsigned int* message_ptr, unsigned int channel)
{
  volatile unsigned int* status_ptr = (unsigned int*)(MAILBOX_BASE_ADDRESS + 
                                      MAILBOX_STATUS_OFFSET);

  volatile unsigned int* write_ptr  = (unsigned int*)(MAILBOX_BASE_ADDRESS + 
                                      MAILBOX_WRITE_OFFSET);

  unsigned int temp = (unsigned int)message_ptr;


  if (temp & MAILBOX_CHANNEL_MASK)
  {
    err_msg_blink(1, 10);
    return 0;
  }

  if (channel >= MAILBOX_MAX_CHANNEL)
  {
    err_msg_blink(2, 10);
    return 0;
  }

  // Wait until mailbox is ready for write
  while ((*status_ptr & MAILBOX_WRITE_READY) == MAILBOX_WRITE_READY);
    
  temp += channel;
  
  *write_ptr = temp;

  return 1;
}


unsigned int mailbox_read(unsigned int channel)
{
  volatile unsigned int* status_ptr = (unsigned int*)(MAILBOX_BASE_ADDRESS + 
      MAILBOX_STATUS_OFFSET);

  volatile unsigned int* read_ptr  = (unsigned int*)(MAILBOX_BASE_ADDRESS);
  unsigned int temp;

  if (channel >= MAILBOX_MAX_CHANNEL)
  {
    err_msg_blink(2, 10);
    return 0;
  }

  // Wait until mailbox is ready for read
  while ((*status_ptr & MAILBOX_READ_READY) == MAILBOX_READ_READY);

  do
  {
    temp = *read_ptr;
    //blink_int(temp);
    //sys_timer_wait(2000000);
  } while ((temp & MAILBOX_CHANNEL_MASK) != channel); 

  return temp & 0xFFFFFFF0;
}
