#Returns the frame buffer addres 
#of a pixel
#r0 x coordinate from 0 to 1023
#r1 y coordinate from 0 to 767
#r2 frame buffer address
#r0 returns fb address for xy pixel
#assumes 4 bytes per pixel (32 bits color depth)
.globl GGetXYAddr
GGetXYAddr:
x .req r1
y .req r2
fbAddr .req r3

#mov r0, #0x400 
mov r0, #0x690 
mla r0, y, r0, x
add r0, fbAddr, r0, lsl #2
mov pc,lr


.globl GSetPixel
GSetPixel:
colour .req r0
x .req r1
y .req r2
fbAddr .req r3
temp .req r4

push {r4}
#mov temp, #0x400 
mov temp, #0x690 
mla temp, y, temp, x
add temp, fbAddr, temp, lsl #2
str colour,[temp]
pop {r4}
mov pc,lr




.globl GDrawRect
GDrawRect:
colour .req r0
x1 .req r1
y1 .req r2
fbAddr .req r3
width .req r4
height .req r5

push {r6,lr}
tempX .req r6

add height, y1
add width, x1
.unreq width
.unreq height
x2 .req r4
y2 .req r5

mov tempX, x1
drawRow$:
  mov x1, tempX
  drawPixel$:
     bl GSetPixel
     add x1,#1
     teq x1,x2
     bne drawPixel$

  add y1,#1
  teq y1,y2
  bne drawRow$

.unreq colour
.unreq x1
.unreq y1
.unreq fbAddr
.unreq x2
.unreq y2

pop {r6,pc}



.globl GDrawLine
GDrawLine:
push {r6,r7,r8,r9,r10,lr}

colour .req r0
x0 .req r1
y0 .req r2
fbAddr .req r3
x1 .req r4
y1 .req r5

dx .req r6
dyn .req r7 /* Note that we only ever use -deltay, so I store its negative for speed. (hence dyn) */
sx .req r8
sy .req r9
err .req r10

cmp x0,x1
subgt dx,x0,x1
movgt sx,#-1
suble dx,x1,x0
movle sx,#1

cmp y0,y1
subgt dyn,y1,y0
movgt sy,#-1
suble dyn,y0,y1
movle sy,#1

add err,dx,dyn
add x1,sx
add y1,sy

pixelLoop$:
teq x0,x1
teqne y0,y1
popeq {r6,r7,r8,r9,r10,pc}

bl GSetPixel

cmp dyn, err,lsl #1
addle err,dyn
addle x0,sx

cmp dx, err,lsl #1
addge err,dx
addge y0,sy

b pixelLoop$

.unreq x0
.unreq x1
.unreq y0
.unreq y1
.unreq dx
.unreq dyn
.unreq sx
.unreq sy
.unreq err
.unreq fbAddr

