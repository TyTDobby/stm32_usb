#Makefile

# Имя проекта
#-------------------------------------------------------------------------------
TARGET = build

# Переменные для сборки
#-------------------------------------------------------------------------------
# отладка?
DEBUG = 1
# оптимизация
OPT = -Og

# Пути
#-------------------------------------------------------------------------------

# Путь к папке сборки
BUILD_DIR = build

# Исходники
#-------------------------------------------------------------------------------
# C исходники
# C_SOURCES += $(wildcard library/usb/*.c)
C_SOURCES +=  \
main.c \
cmsis/system_stm32f10x.c \
usb/usb.c\

#library/usb/usb_desc.c\

# ASM исходники
ASM_SOURCES =  \
cmsis/startup_stm32f10x_md.s

# Исходники библиотек
#-------------------------------------------------------------------------------
PERIFLIB_SOURCES = 

# Инструменты
#-------------------------------------------------------------------------------
BINPATH = /usr/bin
PREFIX = arm-none-eabi-
CC = $(BINPATH)/$(PREFIX)gcc
AS = $(BINPATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(BINPATH)/$(PREFIX)objcopy
AR = $(BINPATH)/$(PREFIX)ar
SZ = $(BINPATH)/$(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m3 -std=c99 -std=c11  -Wabi
# fpu
# NONE for Cortex-M0/M0+/M3

# float-abi

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI) 

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32F103xB \
-DSTM32F10X_MD

# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-Iusb/ \
-Icmsis/ \

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"

# LDFLAGS
#-------------------------------------------------------------------------------
# link script
LDSCRIPT = STM32F103C8Tx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys
LIBDIR =
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

# Сорка приложения
#-------------------------------------------------------------------------------
# список обектных файлов
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# список ASM файлов
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))
compile: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	@$(CC) $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) -c $< -o $@
	@echo -en '\033[34m CC\033[0m   \033[32m' $(addprefix '',$(notdir $<)) '\033[0m\n'

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	@$(AS) $(CFLAGS) -c $< -o $@
	@echo -en '\033[34m CC\033[0m   \033[32m' $(addprefix '',$(notdir $<)) '\033[0m\n\n'

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	@$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	@echo -en '\033[34m .o to .elf\033[0m  \033[32m' $(addprefix '',$(notdir $(OBJECTS))) '\033[0m\n'

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@$(HEX) $< $@
	@echo -en '\033[34m .elf to .hex\033[0m  \033[32m' $(addprefix '',$(notdir $<)) '\033[0m\n'

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@$(BIN) $< $@	
	@echo -en '\033[34m .hex to .bin\033[0m  \033[32m' $(addprefix '',$(notdir $<)) '\033[0m\n\n'

	@echo -en '\033[32m   Size:' $(BUILD_DIR)/$(TARGET).elf  '\033[0m\n'
	@$(SZ) $(BUILD_DIR)/$(TARGET).elf

$(BUILD_DIR):
	@mkdir $@				
	@echo -en '\033[31m Creating build folder!\033[0m\n'

# Очистка
#-------------------------------------------------------------------------------
clean:
	@-rm -fR .dep $(BUILD_DIR)
	@echo -en '\033[31m Clean up!\033[0m\n'

# Прошивка через bootloader
#-------------------------------------------------------------------------------
flash: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin
	st-flash write $(BUILD_DIR)/$(TARGET).bin 0x8000000
  
# Подключение
#-------------------------------------------------------------------------------
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)