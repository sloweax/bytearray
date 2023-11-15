include ../config.mk

CFLAGS+=-L ..
LIBS+=-l:libbytearray.a

all: test

../libbytearray.a:
	cd .. && $(MAKE) libbytearray.a

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

test: ../libbytearray.a test.o unit.o test_bytearray.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

clean:
	rm -f *.o test

.PHONY: clean all
