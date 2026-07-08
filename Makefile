
PROJ_NAME := stm32f407xxx_driver

PRO_DIR   := .
OUT_DIR   := $(PRO_DIR)/output
OBJ_DIR   := $(OUT_DIR)/obj

COMPILER_DIR := C:/GCC_Toolchain

CC      := $(COMPILER_DIR)/bin/arm-none-eabi-gcc
OBJCOPY := $(COMPILER_DIR)/bin/arm-none-eabi-objcopy
SIZE    := $(COMPILER_DIR)/bin/arm-none-eabi-size


CPU := cortex-m4

LINKER_FILE := $(PRO_DIR)/Target/STM32F407XXX/Linker/stm32f4xx_linker.ld

SRC_DIRS :=                        							\
$(PRO_DIR)/					      							\
$(PRO_DIR)/Integration/		      							\
$(PRO_DIR)/Target/STM32F407XXX/Startup						\
$(PRO_DIR)/Mcal/Mcu											\
$(PRO_DIR)/Mcal/Port										\
$(PRO_DIR)/Target/STM32F407XXX/Utilities/SysTick			\
$(PRO_DIR)/Bsw/Communication/CanIf							\
$(PRO_DIR)/Mcal/Dio											\
$(PRO_DIR)/Mcal/Can											\
$(PRO_DIR)/Target/STM32F407XXX/NVIC							\
$(PRO_DIR)/Target/STM32F407XXX/VectorTable


INC_DIRS := 												\
$(PRO_DIR)/Integration/		      							\
$(PRO_DIR)/Mcal/Mcu											\
$(PRO_DIR)/Mcal/Port										\
$(PRO_DIR)/Mcal/Dio											\
$(PRO_DIR)/Mcal/Can                                         \
$(PRO_DIR)/Target/STM32F407XXX/Registers 					\
$(PRO_DIR)/Target/STM32F407XXX/Registers/Core				\
$(PRO_DIR)/Target/STM32F407XXX/Registers/Peripherals		\
$(PRO_DIR)/Target/STM32F407XXX/Utilities/SysTick			\
$(PRO_DIR)/Bsw/Communication/Com_Stack						\
$(PRO_DIR)/Bsw/Communication/CanIf							\
$(PRO_DIR)/Target/STM32F407XXX/NVIC							\
$(PRO_DIR)/Target/STM32F407XXX/VectorTable

SRC_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

VPATH := $(SRC_DIRS)

OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(notdir $(SRC_FILES:.c=.o)))

DEP_FILES := $(OBJ_FILES:.o=.d)

INCLUDE_FLAGS := $(foreach dir,$(INC_DIRS),-I$(dir))

CFLAGS := \
-mcpu=$(CPU) \
-mthumb \
-std=gnu11 \
-O0 \
-g3 \
-Wall \
-Wextra \
-ffunction-sections \
-fdata-sections \
-MMD \
-MP \
$(INCLUDE_FLAGS)

LDFLAGS := \
-T $(LINKER_FILE) \
-mcpu=$(CPU) \
-mthumb \
-Wl,-Map=$(OUT_DIR)/$(PROJ_NAME).map \
-Wl,--gc-sections \
--specs=nano.specs \
--specs=nosys.specs

all: build

build: $(OUT_DIR)/$(PROJ_NAME).elf

# 

$(OUT_DIR)/$(PROJ_NAME).elf: $(OBJ_FILES)
	mkdir -p $(OUT_DIR)
	$(CC) $(OBJ_FILES) $(LDFLAGS) -o $@
	$(OBJCOPY) -O binary $@ $(OUT_DIR)/$(PROJ_NAME).bin
	$(OBJCOPY) -O ihex   $@ $(OUT_DIR)/$(PROJ_NAME).hex

	$(SIZE) $@

	@echo ""
	@echo "========== BUILD SUCCESS =========="

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OUT_DIR)

run:
	$(PRO_DIR)/ST_LINK/ST-LINK_CLI -p "$(OUT_DIR)/$(PROJ_NAME).hex" 0x08000000
	$(PRO_DIR)/ST_LINK/ST-LINK_CLI -rst


print-%:
	@echo '$*=$($*)'

-include $(DEP_FILES)