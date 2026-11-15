### MN316 OpenCPU Makefile文件，谨慎修改!!! ###

.PHONY: all clean

#根目录
ROOT_DIR := .
TARGET := xinyiNBSoc_M3
OC_FILES := 
INC :=
#系统脚本，请勿修改！！！
include $(ROOT_DIR)/tools/scripts/config.mk
include $(ROOT_DIR)/tools/scripts/feature.mk

#三方库
include $(ROOT_DIR)/third-party/third-party.mk

#自有库
include $(ROOT_DIR)/src/source.mk

#用户代码
ifeq ($(DEMO_SUPPORT),y)
include $(ROOT_DIR)/examples/examples.mk
else
include $(ROOT_DIR)/custom/custom.mk
endif

#版本控制
DBRD_VER := DBRD
XGCD_VER := XGCD

#预构建文件
PREBUILD_IMG_DIR := $(ROOT_DIR)/prebuild/images
PREBUILD_LIB_DIR := $(ROOT_DIR)/prebuild/lib

#源文件
C_FILES_FLASH += $(OC_FILES)
C_FILES_FLASH := $(sort $(C_FILES_FLASH))

#目标文件
OBJ_DIR := $(ROOT_DIR)/out/objs
IMG_DIR := $(ROOT_DIR)/out/images
LOG_DIR := $(ROOT_DIR)/out/logs
OBJS := $(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o.flash, $(C_FILES_FLASH)))
DEPS := $(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.d, $(C_FILES_FLASH)))

#库文件
LIBS = -lsysapp -lcustom -lm
INCS = -I$(ROOT_DIR)/include -I$(ROOT_DIR)/include/lwip -I$(ROOT_DIR)/include/kernel/base -I$(ROOT_DIR)/include/kernel/include -I$(ROOT_DIR)/include/kernel -I$(ROOT_DIR)/include/cmiot -I$(ROOT_DIR)/include/cJSON $(INC)
LIBRARY_PATH = -L $(ROOT_DIR)/prebuild/lib
LINK_WITH_LIBRARY += -Wl,--start-group $(LIBRARY_PATH) $(LIBS) -Wl,--end-group

#第三方开源库
#ToDo

#命令工具
MKDIR = $(ROOT_DIR)/tools/toolchain/mkdir.exe
MV = $(ROOT_DIR)/tools/toolchain/mv.exe
CP = $(ROOT_DIR)/tools/toolchain/cp.exe
ECHO = $(ROOT_DIR)/tools/toolchain/echo.exe
RM = $(ROOT_DIR)/tools/toolchain/rm.exe
M3LD = $(ROOT_DIR)/tools/toolchain/m3ld.exe

#生成可执行文件
all: objs_optimization_l2
	@$(ECHO) "Start link..."
	@$(CXX) $(COMPILE_OPTION) $(LINK) $(LINKOPT) $(USE_LIB) -o $(TARGET).elf $(OBJS) $(OC_LIBS) $(LINK_WITH_LIBRARY)
	@-$(MKDIR) -p $(OBJ_DIR)/$(TARGET)
	@$(ECHO) "Creating flash.bin..."
	@$(OBJCOPY) -O binary -j .flashtext $(TARGET).elf $(OBJ_DIR)/$(TARGET)/flash.bin
	@$(ECHO) "Creating ram.bin..."
	@$(OBJCOPY) -O binary -j .isr_vector -j .text -j .data $(TARGET).elf $(OBJ_DIR)/$(TARGET)/ram.bin
	@$(ECHO) "Creating .size..."
	@$(OBJSIZE) $(OBJS) >> $(OBJ_DIR)/$(TARGET)/$(TARGET).size
	@$(ECHO) "Creating .lst..."
	@$(OBJDUMP) -S $(TARGET).elf > $(OBJ_DIR)/$(TARGET)/$(TARGET).lst
	@$(ECHO) "Creating .dumpelf..."
	@$(READELF) -a $(TARGET).elf > $(OBJ_DIR)/$(TARGET)/$(TARGET).dumpelf
	@$(ECHO) "Calculating size..."
	@$(OBJSIZE) --format=berkeley "$(TARGET).elf"
	@$(M3LD) $(OBJ_DIR)/$(TARGET)
	@$(ECHO) "Moving files..."
	@-$(MKDIR) -p $(IMG_DIR)/$(PREBUILD_TARGET)/$(HARDWARE_TARGET)
	@$(MV) $(TARGET).* $(OBJ_DIR)/$(TARGET)/
	@$(CP) -a $(PREBUILD_IMG_DIR)/$(PREBUILD_TARGET)/$(HARDWARE_TARGET)/* $(IMG_DIR)/$(PREBUILD_TARGET)/$(HARDWARE_TARGET)/
	@$(CP) -a $(PREBUILD_IMG_DIR)/common/* $(IMG_DIR)/$(PREBUILD_TARGET)/$(HARDWARE_TARGET)/
	@$(CP) $(OBJ_DIR)/$(TARGET)/$(TARGET).elf $(IMG_DIR)/$(PREBUILD_TARGET)/$(HARDWARE_TARGET)/$(TARGET).elf
	@$(CP) $(OBJ_DIR)/$(TARGET)/$(TARGET).map $(IMG_DIR)/$(PREBUILD_TARGET)/$(HARDWARE_TARGET)/$(TARGET).map
	@$(CP) $(OBJ_DIR)/$(TARGET)/arm.img $(IMG_DIR)/$(PREBUILD_TARGET)/$(HARDWARE_TARGET)/arm.img
	@$(CP) $(OBJ_DIR)/$(TARGET)/flash.bin $(IMG_DIR)/$(PREBUILD_TARGET)/$(HARDWARE_TARGET)/flash.bin
	@$(CP) $(OBJ_DIR)/$(TARGET)/ram.bin $(IMG_DIR)/$(PREBUILD_TARGET)/$(HARDWARE_TARGET)/ram.bin
	@$(ECHO) "Done!!!"

objs_optimization_l2: $(OBJS)

#生成.o .d依赖文件
$(OBJ_DIR)/%.o.flash: %.c
	@-$(MKDIR) -p $(dir $@)
	@$(ECHO) 'compile $<'
	@$(CC) $(CPU) $(USE_NANO) $(FLAGS) $(CFLAGS) $(INCS) $(OPTIMIZATION_LEVEL) $(GENNER_DEPS_FLASH) -g -fno-common -c  -o $@ $<

-include $(DEPS)

#清除编译文件
clean:
	@$(ECHO) 'clear compiled files'
	@$(RM) -f $(ROOT_DIR)/*.elf $(ROOT_DIR)/*.map
	@$(RM) -f $(TARGET).*
	@$(RM) -fr $(OBJ_DIR)
	@$(RM) -fr $(LOG_DIR)
