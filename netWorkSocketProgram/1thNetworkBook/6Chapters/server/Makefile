# this is base make file.
# add some code you need.

include ../../Makefile_comm

PROJECT=base_server
CLIENT=server.o

all: ${CLIENT}

# link the static libary.
$(CLIENT):%.o:%.c
	$(CC) $< $(CFLAGS) -L$(STATICLIBSPATH) -l$(LIBSNAME) -static -o $(PROJECT)



.PHONY : clean
clean:
	rm -rf $(CLIENT) $(PROJECT)
