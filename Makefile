include config.mk

all: libbytearray.a

%.o: %.c
	$(CC) $(CFLAGS) $^ -c -o $@

libbytearray.a: bytearray.o
	$(AR) rcs $@ $^

clean:
	rm -f *.o *.a

install: libbytearray.a
	cp -f $^ $(LIBDESTPATH)
	cp -f bytearray.h $(INCDESTPATH)

uninstall:
	rm -f $(LIBDESTPATH)/libbytearray.a
	rm -f $(INCDESTPATH)/bytearray.h

.PHONY: clean all install uninstall
