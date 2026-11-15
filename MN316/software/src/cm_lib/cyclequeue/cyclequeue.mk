

CM_CYCLEQUEUE_DIR :=src/cm_lib/cyclequeue


C_FILES_FLASH +=  $(CM_CYCLEQUEUE_DIR)/cm_cyclequeue.c
CFLAGS      += -I$(CM_CYCLEQUEUE_DIR)