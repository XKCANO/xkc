
###C soruce file on flash
C_FILES_FLASH += custom/src/custom_main.c \
                 custom/src/msg_box.c \
                 custom/src/flash_api.c \
                 custom/src/uart_api.c \
                 custom/src/network_api.c

###Public include path for other module
CFLAGS += -Icustom/inc
