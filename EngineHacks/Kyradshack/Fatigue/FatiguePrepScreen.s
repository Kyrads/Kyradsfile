.thumb
.align

.macro blh to, reg=r3
    ldr \reg, =\to
    mov lr, \reg
    .short 0xF800
.endm


.global DenyDeploymentIfFatigued
.type DenyDeploymentIfFatigued, %function

@hook at 957F8, 0xA bytes are free
@return true if unit cannot be deployed
@return false if unit can be deployed
@r4=unit to check

.equ CannotDeployReturnPoint,0x8095805
.equ CanDeployReturnPoint,0x8095819

DenyDeploymentIfFatigued:

@we can also check if they were undeployed last chapter, and if so reset fatigue here (first, then always clear the deny deploy check)
ldrb r0,[r4,#0xE]
mov r1,#0x20
and r0,r1
cmp r0,#0
beq DenyDeploy
mov r0,r4
@calculate endurance
blh GetEndurance
mov r1,#0x3B
ldrb r1,[r4,r1]
sub r1,r0
mov r0,#0
cmp r1,r0
bgt SetFatigue
mov r1,#0
SetFatigue:
mov r0,#0x3B
strb r1,[r4,r0]

DenyDeploy:
@get fatigue and max hp
mov r0,r4
add r0,#0x12 @max hp
ldrb r0,[r0]
lsr r0,r0,#1 @half hp

mov r1,r4
add r1,#0x04 @go to class data
ldr r1,[r1]
add r1,#0x11 @class con
ldrb r1,[r1]
add r0,r1 @add class con to hp/2

mov r1,r4
add r1,#0x00 @go to char data
ldr r1,[r1]
add r1,#0x13 @char con
mov r2,#0
ldsb r1,[r1,r2]
add r0,r1 @add char con to hp/2 + class con

mov r1,r4
add r1,#0x1A @con bonus
ldrb r1,[r1]
add r0,r1 @add con bonus to hp/2 + unit con aka final endurance

lsl r0,r0,#1 @double endurance

mov r1,r4
add r1,#0x3B @fatigue
ldrb r1,[r1]

cmp r0,r1
blt CannotDeploy

CanDeploy:
ldr r1,=CanDeployReturnPoint
b GoBack

CannotDeploy:
ldr r1,=CannotDeployReturnPoint

GoBack:
bx r1

.ltorg
.align
