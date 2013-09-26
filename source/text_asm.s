.align 4
.globl font 
font:
.incbin "font0.bin"

.globl DrawCharacter
DrawCharacter:
cmp r0,#127
movhi r0,#0
movhi r1,#0
movhi pc,lr

push {r4,r5,r6,r7,r8,lr}
x .req r4
y .req r5
charAddr .req r6
mov x,r1
mov y,r2
ldr charAddr,=font
add charAddr, r0,lsl #4

lineLoop$:
bits .req r7
bit .req r8
ldrb bits,[charAddr]
mov bit,#8

charPixelLoop$:
subs bit,#1
blt charPixelLoopEnd$
lsl bits,#1
tst bits,#0x100
beq charPixelLoop$

#add r0,x,bit
#mov r1,y
#bl DrawPixel

push {r0, r1, r2, r3}
mov r2, #0xFF000000
add r2, #0x000000FF
add r0,x,bit
mov r1,y
bl graph_set_pixel
pop {r0, r1, r2, r3}

teq bit,#0
bne charPixelLoop$
charPixelLoopEnd$:
.unreq bit
.unreq bits
add y,#1
add charAddr,#1
tst charAddr,#0b1111
bne lineLoop$
.unreq x
.unreq y
.unreq charAddr

width .req r0
height .req r1
mov width,#8
mov height,#16

pop {r4,r5,r6,r7,r8,pc}
.unreq width
.unreq height
