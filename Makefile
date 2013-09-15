CC := gcc

SRC_FILES := rvcon.c

CC_FLAGS :=
OUT_FILE := rvcon

all:
	$(CC) $(SRC_FILES) $(CC_FLAGS) -o $(OUT_FILE)
