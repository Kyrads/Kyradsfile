.thumb

.equ LockTouchID, SkillTester+4
.equ CunningID, SkillTester+8

@Check for TouchLock Skill 

push {r2} @The vanilla routine we jump back to needs this value
push {r4}

	ldr r0, SkillTester
	mov lr, r0
	mov r0, r2
	ldr r1, LockTouchID
	mov r4, r0
	
	.short 0xf800
	
	cmp r0, #0
		bne HasPickSkill
		ldr r0, SkillTester
		mov lr, r0
		mov r0, r4
		ldr r1, CunningID
		.short 0xf800
		cmp r0, #0
		beq NoPickSkill

		HasPickSkill:
			mov r2, r5

pop {r4}	
pop {r2}

	ldr r3, PickSkillBranch
	bx r3
		
	NoPickSkill:
		pop {r4}
		pop {r2}
		ldr r3, NoPickSkillBranch
			bx r3

.align

	PickSkillBranch:
.long 0x8023E9D

	NoPickSkillBranch:
.long 0x8023E95

.ltorg

	SkillTester:
		@POIN SkillTester
		@WORD LockTouchID
