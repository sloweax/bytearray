include config.mk

all: libbytearray.a
OBJ=bytearray.o

%.o: %.c
	$(CC) $(CFLAGS) $^ -c -o $@

libbytearray.a: $(OBJ)
	$(AR) rcs $@ $^

clean:
	rm -f *.o *.a
	cd test && $(MAKE) clean

install: libbytearray.a
	cp -f $^ $(LIBDESTPATH)
	cp -f bytearray.h $(INCDESTPATH)

uninstall:
	rm -f $(LIBDESTPATH)/libbytearray.a
	rm -f $(INCDESTPATH)/bytearray.h

test: all
	cd test && $(MAKE) && ./$@

.PHONY: clean all install uninstall test
