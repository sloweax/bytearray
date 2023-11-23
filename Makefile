include config.mk

all: libbytearray.so libbytearray.a

OBJ=bytearray.o

%.o: %.c
	$(CC) $(CFLAGS) $^ -c -o $@

libbytearray.so: $(OBJ)
	$(CC) $(CFLAGS) -fPIC -shared $(OBJ) -o $@

libbytearray.a: $(OBJ)
	$(AR) rcs $@ $^

clean:
	rm -f *.o *.a *.so
	cd test && $(MAKE) clean

install: all
	cp -f $^ $(LIBDESTPATH)
	cp -f bytearray.h $(INCDESTPATH)

uninstall:
	rm -f $(LIBDESTPATH)/libbytearray.*
	rm -f $(INCDESTPATH)/bytearray.h

test: libbytearray.a
	cd test && $(MAKE) && ./$@

.PHONY: clean all install uninstall test
