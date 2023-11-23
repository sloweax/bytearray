include ../config.mk

LIBS+=-l:libbytearray.a
OBJ=test.o unit.o test_bytearray.o test_hex.o test_read.o

all: test

../libbytearray.a:
	cd .. && $(MAKE) libbytearray.a

%.o: %.c
	$(CC) $(CFLAGS) $^ -c -o $@

test: ../libbytearray.a $(OBJ)
	$(CC) $(CFLAGS) -L .. $(OBJ) $(LIBS) -o $@

clean:
	rm -f *.o test

.PHONY: clean all
