.thumb
.align

push {r4-r6, lr}
mov r4, r0 @stat
mov r5, r1 @unit

@check fatigue
mov r0,r5
add r0,#0x3B
ldrb r0,[r0]
@check max HP
ldrb r1,[r5,#0x12]

@see if fatigue > max HP 
cmp r0,r1
blt GoBack

@if so, we debuff stat by 1/2
lsr r4,r4,#1

GoBack:
mov r0, r4
mov r1, r5
pop {r4-r6,pc}


.ltorg
.align
