#this is really first makefile for me. begin...

include ../../Makefile_comm

PROJECT=client_simple 
CLIENT=client_simple.o

all: ${CLIENT}

$(CLIENT):%.o:%.c
	#$(CC) -c $(CFLAGS) -L$(STATICLIBSPATH) -l$(LIBSNAME) $< -o $(PROJECT)
	#$(CC) -c $(CFLAGS) $< -o $(CLIENT)
	$(CC) $< -L$(STATICLIBSPATH) -l$(LIBSNAME) -static -o $(PROJECT)

.PHONY : clean
clean:
	rm -rf $(CLIENT) $(PROJECT)
