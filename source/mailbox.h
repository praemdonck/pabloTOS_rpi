#ifndef MAILBOX_H
#define MAILBOX_H
unsigned int mailbox_write(unsigned int* message_ptr, unsigned int channel);
unsigned int mailbox_read(unsigned int channel);
#endif
