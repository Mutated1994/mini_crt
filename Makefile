CC = $(QUIET_CC) gcc
AR = $(QUIET_AR) ar
LD = $(QUIET_LD) ld

QUIET_CC = @printf '	%b %b\n' CC $@;
QUIET_AR = @printf '	%b %b\n' AR $@;
QUIET_LD = @printf '	%b %b\n' LD $@;

MINICRT_LIB_SRC     = malloc.c stdio.c string.c printf.c
MINICRT_LIB_OBJS    = malloc.o printf.o stdio.o string.o
MINICRT_STATIC_LIB  = minicrt.a
MINICRT_CFLAGS      = -fno-builtin -nostdlib -fno-stack-protector
MINICRT_ARFLAGS     = -rs

ENTRY_OBJ           = entry.o

TEST_SRC            = test.c
TEST_OBJ            = test.o
TEST_LD_SRC         = $(ENTRY_OBJ) $(TEST_OBJ) $(MINICRT_STATIC_LIB)
TEST_CFLAGS         = -ggdb -fno-builtin -nostdlib -fno-stack-protector
TEST_LDFLAGS        = -static
TEST_LD_ENTRY_FLAGS = -e mini_crt_entry

#----------------------------------------------
all: $(MINICRT_STATIC_LIB) test

test: $(TEST_LD_SRC)
	$(LD) $(TEST_LDFLAGS) $(TEST_LD_ENTRY_FLAGS) $^ -o $@

$(TEST_OBJ): $(TEST_SRC)
	$(CC) -c $(TEST_CFLAGS) $<

lib: $(MINICRT_STATIC_LIB)

$(MINICRT_STATIC_LIB): $(MINICRT_LIB_OBJS)
	$(AR) $(MINICRT_ARFLAGS) $@ $^

$(MINICRT_LIB_OBJS): $(MINICRT_LIB_SRC)

%.o : %.c
	$(CC) -c $(MINICRT_CFLAGS) $<

.PHONY: clean help
clean:
	rm -f *.o *.a test.text test

help:
	@echo "Usage:"
	@echo "	help 			: show help messages"
	@echo "	all  			: build minicrt.a and test"
	@echo "	lib  			: build minicrt.a"
	@echo "	test 			: build test"
	@echo "	clean			: clean *.o test.txt"
	@echo "	make [target] 		: print out all build commands, ex: make lib"