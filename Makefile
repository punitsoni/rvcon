CC := gcc

SRC_FILES := rvcon.c ui.c
CC_LIBS := -lpthread -lpigpio -lrt -lncurses
CC_FLAGS := -g
OUT_FILE := rvcon

all:
	$(CC) $(SRC_FILES) $(CC_FLAGS) $(CC_LIBS) -o $(OUT_FILE)
