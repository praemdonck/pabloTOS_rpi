.section .init
.globl _start
.globl wait_function
_start:
b main_asm


.section .text
main_asm:
mov sp,#0x8000
bl main


#/* Initialise frame buffer */
#mov r0,#1024
#mov r1,#768
##mov r2,#16
#mov r2,#32
##bl InitialiseFrameBuffer
##bl frame_buffer_init
#
#teq r0,#0
#bne noError$
#
#mov r0,#16
#mov r1,#1
#bl SetGpioFunction
#mov r0,#16
#mov r1,#0
#bl SetGpio
#
#
#error$:
#b error$
#
#noError$:
#fbInfoAddr .req r4
#mov fbInfoAddr,r0
#
#
#
#
#x .req r1
#y .req r2
#fbAddr .req r3
#width .req r4
#height .req r5
#
#
##push {r0, r1, r2, r3}
###mov r0, fbAddr
##ldr r0,[fbInfoAddr,#0]
##bl blink_int
##pop {r0, r1, r2, r3}
#
#
#ldr fbAddr,[fbInfoAddr,#32]
#.unreq fbInfoAddr
#
#
#
#
#colour .req r0
#counter .req r6
##pixelAddress .req r0
#ldr colour,=0xFF000000
##Blue Mask
##ldr colourMask,=0x0000001F
##Green Mask
##ldr colourMask,=0x000007E0
##Red Mask
##ldr colourMask,=0xFF00FF00
#
#
#render$:
#
#mov x, #256
#mov y, #256
#mov width, #256
#mov height, #256
#
#mov colour, #0xFF000000
#add colour, #0x00FF0000
#bl GDrawRect
#
#
#
#mov x, #0
#mov y, #0
#mov width, #256
#mov height, #256
#
#mov colour, #0xFF000000
#add colour, #0x000000FF
#bl GDrawLine
#
#
#mov x, #0
#mov y, #0
#mov width, #1680
#ldr height,=0x41a
#                                     
#mov colour, #0xFF000000
#add colour, #0x000000FF
#bl GDrawLine
#
#
#
#mov x, #512
#mov y, #256
#mov width, #768
#mov height, #0
#
#mov colour, #0xFF000000
#add colour, #0x000000FF
#bl GDrawLine
#
##bl GDrawRect
##
##
#mov x, #256
#add x, #40
#mov y, #256
#add y, #40
#mov width, #176
#mov height, #176
#
#mov colour, #0xFF000000
#add colour, #0x00000000
#bl GDrawRect
#
#   add counter,#1
#   and counter,#0xFF
#   teq counter,#0xFF
##   bne render$
##
##   push {r0,r1,r2,r3}
##   ldr r0,=10000000
##   bl SysTimerWait
##   pop {r0,r1,r2,r3}
#infinite_loop$:
#   b infinite_loop$
#   b render$
#
#.unreq fbAddr
#
#
#
#
#
#
#
#
#
#
#
#
#
##/* Set io as output */
##mov r0,#16
##mov r1,#1
##bl SetGpioFunction
##
##
##
###start main loop
###bl GetGpioAddress 
###mov r4,r0
##
##loop$:
##
##/* Set pin low to turn on led */
##mov r0,#16
##mov r1,#0
##bl SetGpio
##
##
###bl GetGpioAddress 
###/* Set pin low to turn on led */
###mov r1,#1
###lsl r1,#16
###str r1,[r0,#40]
##
##/* wait */
###mov r0,#0x080000
###mov r0,#0x5F0000
###bl wait_function
##
##ldr r0,=100000
##bl SysTimerWait
##
##/* Set pin high to turn off led */
##mov r0,#16
##mov r1,#1
##bl SetGpio
##
##/* wait */
###mov r0,#0x5F0000
###bl wait_function
##
##
##ldr r0,=900000
##bl SysTimerWait
##
##b loop$                                
##
##/* Function wait_function
## * wait
## * r0 time to wait (tbd)
## */
##wait_function:
##wait1$:
##sub r0,#1
##cmp r0,#0
##bne wait1$
##mov pc,lr



/* Function wait_function
 * wait
 * r0 time to wait (tbd)
 */
wait_function:
wait1$:
sub r0,#1
cmp r0,#0
bne wait1$
mov pc,lr



.globl getPC
getPC:
mov r0,lr
mov pc,lr
