.thumb
.align

push {r4-r6, lr}
mov r4, r0 @mov
mov r5, r1 @unit

@check fatigue
mov r0,r5
add r0,#0x3B
ldrb r0,[r0]
@calculate endurance
ldrb r1,[r5,#0x12] @getting hp, base con and bonus con
ldrb r2,[r5,#0x1A]
ldr r3,[r5,#0x04]
ldrb r3,[r3,#0x11]
add r2, r3
lsr r1,r1,#1
add r1,r2
@check mounted status
ldr r2,[r5,#0x04]
ldr r2,[r2,#0x28]
ldr r3,[r5,#0x00]
ldr r3,[r3,#0x28]
orr r2,r2,r3
mov r3,#1
and r2,r3

@see if fatigue > endurance
cmp r0,r1
blt GoBack

@see if fatigue > 2 * endurance
lsl r1,r1,#1
cmp r0,r1
blt Gate
@if mounted
cmp r2,#1
bne Debuff2

Debuff3:
sub r4,r4,#3 @-3 mov
b GoBack

Gate:
@if mounted
cmp r2,#1
bne Debuff1

Debuff2:
sub r4,r4,#2 @-2 mov
b GoBack

Debuff1:
sub r4,r4,#1 @-1 mov

GoBack:
mov r0, r4
mov r1, r5
pop {r4-r6, pc}

.ltorg
.align
