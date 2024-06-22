.thumb
.align

push {r4-r6, lr}
mov r4, r0 @stat
mov r5, r1 @unit

@check fatigue
mov r0,r5
add r0,#0x3B
ldrb r0,[r0]
@calculate endurance
ldrb r1,[r5,#0x12] @HP
lsr r1,r1,#1 @halving hp
ldr r2,[r5,#0x04]
ldrb r2,[r2,#0x11] @class con
add r1,r2 @add class con to HP/2
ldr r2,[r5,#0x00]
add r2,#0x13 @char con
mov r3,#0
ldsb r2,[r2,r3]
add r1,r2
ldrb r2,[r5,#0x1A] @bonus con
add r1,r2 @final endurance

@see if fatigue > endurance
cmp r0,r1
ble GoBack

@see if fatigue > 2*endurance
lsl r1,r1,#1
cmp r0,r1
ble DebuffA

@if so, we debuff stat by 1/2
lsr r4,r4,#1
b GoBack

DebuffA:
@if so, we debuff stat by 1/4
mov r0,r4
add r0,#3
lsr r0,r0,#2
sub r4,r0

GoBack:
mov r0, r4
mov r1, r5
pop {r4-r6,pc}


.ltorg
.align
