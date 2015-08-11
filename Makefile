CC ?= clang
LDPATH = 

INCLUDES = 
LIBS= 
BUILD := debug
cflags.debug := -Wall -g -DDEBUG
cflags.release := -03 -DNDEBUG
CFLAGS := -std=c99 ${cflags.${BUILD}}


SOURCE = src/main.c
OBJECTS = src/main.o

ep1sh: lib/libep1sh.a $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) $(INCLUDES) $(LDPATH) $(LIBS) -o $@ $<

lib/libep1sh.a: $(OBJECTS)
	$(AR) rvs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o  $@ $<


.PHONY: clean

clean:
	find . -name "*.o" -delete & \
	find . -name "*.a" -delete & \
	find . -name "*.out" -delete & \
	find . -name "ep1sh" -delete

