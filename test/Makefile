TESTS := $(shell find -type f -name *.c)
CFLAGS += -Wall -Werror -I../include

all: $(patsubst %.c,%,${TESTS})

%: %.c
	${CC} ${CFLAGS} $< -o $@
	./$@