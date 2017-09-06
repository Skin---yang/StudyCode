# this is base make file.
# add some code you need.

include ../../Makefile_comm

PROJECT=base_server
SERVER=server.o

all: ${SERVER}

# link the static libary.
$(SERVER):%.o:%.c
	$(CC) $< $(CFLAGS) -L$(STATICLIBSPATH) -l$(LIBSNAME) -static -o $(PROJECT)



.PHONY : clean
clean:
	rm -rf $(SERVER) $(PROJECT)
