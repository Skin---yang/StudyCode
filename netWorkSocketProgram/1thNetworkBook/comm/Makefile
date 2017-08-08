#
# this is Makefile generate the object.
#
include ../Makefile_comm

HEADER= unp.h config.h

CFLAGS=rvcs

all:$(OBJECTS)


$(OBJECTS):%.o:%.c
	$(CC) -c $< -o $@


libs:
	ar $(CFLAGS) $(LIB_STATIC) $(OBJECTS)

.PHONY:clean
clean:
	rm -rf $(OBJECTS) $(LIB_STATIC)
