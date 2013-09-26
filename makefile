##############################################################################
#	makefile
#	 by Alex Chadwick
#
#	A makefile script for generation of raspberry pi kernel images.
###############################################################################

# The toolchain to use. arm-none-eabi works, but there does exist 
# arm-bcm2708-linux-gnueabi.
ARMGNU ?= arm-none-eabi

# The intermediate directory for compiled object files.
BUILD = build/

# The directory in which source files are stored.
SOURCE = source/

# The name of the output file to generate.
TARGET = kernel.img

# The name of the assembler listing file to generate.
LIST = kernel.list

# The name of the map file to generate.
MAP = kernel.map

# The name of the linker script to use.
LINKER = kernel.ld
LINKER_DBG = kernel_dbg.ld

# The names of all object files that must be generated. Deduced from the 
# assembly code files in source.
OBJECTS := $(patsubst $(SOURCE)%.s,$(BUILD)%.o,$(wildcard $(SOURCE)*.s))
OBJECTS_C := $(patsubst $(SOURCE)%.c,$(BUILD)%.o,$(wildcard $(SOURCE)*.c))


# Rule to make everything.
all: $(TARGET) $(LIST)
debug: $(BUILD)output_dbg.elf

# Rule to remake everything. Does not include clean.
rebuild: all

# Rule to make the listing file.
$(LIST) : $(BUILD)output.elf
	$(ARMGNU)-objdump -d -g -S $(BUILD)output.elf > $(LIST)

# Rule to make the image file.
$(TARGET) : $(BUILD)output.elf
	$(ARMGNU)-objcopy $(BUILD)output.elf -O binary $(TARGET) 

# Rule to make the elf file.
$(BUILD)output.elf : $(OBJECTS) $(OBJECTS_C) $(LINKER)
	$(ARMGNU)-ld --no-undefined $(OBJECTS) $(OBJECTS_C) -Map $(MAP) -o $(BUILD)output.elf -T $(LINKER)

# Rule to make the elf file.
$(BUILD)output_dbg.elf : $(OBJECTS) $(OBJECTS_C) $(LINKER_DBG)
	$(ARMGNU)-ld --no-undefined $(OBJECTS) $(OBJECTS_C) -Map $(MAP) -o $(BUILD)output_dbg.elf -T $(LINKER_DBG)

# Rule to make the object files.
$(BUILD)%.o: $(SOURCE)%.s
	$(ARMGNU)-as -g -I $(SOURCE) $< -o $@

$(BUILD)%.o: $(SOURCE)%.c
	$(ARMGNU)-gcc -c -g $(SOURCE) $< -o $@

# Rule to clean files.
clean : 
	-rm -f $(BUILD)*.o 
	-rm -f $(BUILD)*.elf
	-rm -f $(TARGET)
	-rm -f $(LIST)
	-rm -f $(MAP)
