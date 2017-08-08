#this is really first makefile for me. begin...

include ../../Makefile_comm

PROJECT=server_simple
SERVER=server_simple.o 

all: ${SERVER}

$(SERVER):%.o:%.c
	#$(CC) $(CFLAGS) $< -o $@ $(LIBS)
	$(CC) $< -L$(STATICLIBSPATH) -l$(LIBSNAME) -static -o $(PROJECT)

.PHONY : clean
clean:
	rm -rf $(PROJECT) $(SERVER)
