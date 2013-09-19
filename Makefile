CC := gcc

SRC_FILES := rvcon.c ui.c controller.c
CC_LIBS := -lpthread -lrt -lncurses -lpigpio
CC_FLAGS := -g
OUT_FILE := rvcon

all:
	$(CC) $(SRC_FILES) $(CC_FLAGS) $(CC_LIBS) -o $(OUT_FILE)
