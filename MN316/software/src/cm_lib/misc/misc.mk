

CM_MISC_DIR :=src/cm_lib/misc


C_FILES_FLASH +=  $(CM_MISC_DIR)/cm_misc_bcd.c
C_FILES_FLASH +=  $(CM_MISC_DIR)/cm_misc_crc.c
C_FILES_FLASH +=  $(CM_MISC_DIR)/cm_misc_time.c
C_FILES_FLASH +=  $(CM_MISC_DIR)/cm_misc_str.c
CFLAGS      += -I$(CM_MISC_DIR)