# Directories
src := $(realpath .)/Source
src_Include := $(realpath .)/Include
src_Event := $(realpath .)/Event
CLib := $(realpath .)/FE-CLib-Decompatible
clib_Include := $(CLib)/include

# Lyn
LYN := $(realpath .)/../../../EventAssembler/Tools/lyn
LYN_REFERENCE := $(realpath .)/definitions.o

# DevKit
include $(DEVKITARM)/base_tools

# Include Flags
INCLUDE_DIRS := $(clib_Include) $(src_Include)
INCFLAGS := $(foreach dir, $(INCLUDE_DIRS), -I "$(dir)")

# Compilation Flags
ARCH := -mcpu=arm7tdmi -mthumb -mthumb-interwork
CFLAGS := $(ARCH) $(INCFLAGS) -Wall -O2 -mtune=arm7tdmi -ffreestanding -fomit-frame-pointer -mlong-calls
ASFLAGS := $(ARCH) $(INCFLAGS)

.PRECIOUS: %.o;

# OBJ to event rule
$(src_Event)%.lyn.event: $(src)%.o $(LYN_REFERENCE)
	@mkdir -p $(dir $@)
	@$(LYN) $< $(LYN_REFERENCE) > $@

# OBJ to DMP rule
$(src)%.dmp: $(src)%.o
	@mkdir -p $(dir $@)
	@$(OBJCOPY) -S $< -O binary $@

# ASM to OBJ rule
%.o: %.s
	@mkdir -p $(dir $@)
	@$(AS) $(ASFLAGS) -I $(dir $<) $< -o $@

# C to ASM rule
$(src)%.o: $(src)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# C to ASM rule
$(src)/asm/%.asm: $(src)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -S $< -o $@ -fverbose-asm

# ASM/C and generated files
CFILES := $(shell find $(src) -name '*.c')
LYNFILES := $(patsubst $(src)%.c,$(src_Event)%.lyn.event,$(CFILES))

hack: $(LYNFILES)