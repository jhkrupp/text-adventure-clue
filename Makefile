CFLAGS = -g -O3 -std=c99 -Wall -Wpedantic -Wextra -D_POSIX_C_SOURCE=200809L
ifdef DEBUG
CFLAGS += -fno-omit-frame-pointer -fsanitize=address -fsanitize=leak -fsanitize=undefined
endif
objects = $(addsuffix .o,$(basename $(wildcard *.c)))
NAME = clue
$(NAME): $(objects)
	$(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@
 
.PHONY: clean
clean:
	-rm -f $(objects) $(NAME)


