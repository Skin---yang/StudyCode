include ../../Makefile_comm

PROJECT=base_client
CLIENT=client.o

all: ${CLIENT}

# link the static libary.
$(CLIENT):%.o:%.c
	$(CC) $< -L$(STATICLIBSPATH) -l$(LIBSNAME) -static -o $(PROJECT)



.PHONY : clean
clean:
	rm -rf $(CLIENT) $(PROJECT)
