CC := gcc

SRC_FILES := rvcon.c ui.c controller.c
INCLUDE_PATH := -Iprebuilt/pigpio
LIB_PATH := -Lprebuilt/pigpio
CC_LIBS := -lpthread -lrt -lncurses -lpigpio
CC_FLAGS := -g
OUT_FILE := rvcon

all:
	$(CC) $(SRC_FILES) $(CC_FLAGS) $(INCLUDE_PATH) $(LIB_PATH) $(CC_LIBS) -o $(OUT_FILE)
