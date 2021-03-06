CC ?= clang
DEFS = -D_GNU_SOURCE -D_FORTIFY_SOURCE=2
INCLUDES = -I/usr/include -I./include
LIBS= -lreadline
BUILD := debug
cflags.debug := -Wall -g -DDEBUG
cflags.release := -03 -DNDEBUG
CFLAGS := -std=gnu99 ${cflags.${BUILD}}

libep1sh = src/libep1sh.a
SOURCE = src/main.c
LIB_OBJS := $(patsubst %.c, %.o, $(filter-out $(SOURCE), $(shell find src/ -name '*.c')))
TESTS:= $(patsubst %.c, %.out, $(wildcard tests/*.c))

all: ep1sh test

ep1sh: $(libep1sh) $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) $(DEFS) $(INCLUDES) $(LIBS) -o $@ $<

$(libep1sh): $(LIB_OBJS)
	$(AR) rvs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(DEFS) $(INCLUDES) -c -o  $@ $<


.PHONY: clean test

test: $(libep1sh) $(TESTS)

%.out: %.c
	$(CC) $(CFLAGS) $< $(DEFS) $(INCLUDES) $(LIBS) -o $@ $(libep1sh) 

print-%:
	@echo '$*=$($*)'

clean:
	find . -name "*.o" -delete & \
	find . -name "*.a" -delete & \
	find . -name "*.out" -delete & \
	find . -name "ep1sh" -type f -delete

