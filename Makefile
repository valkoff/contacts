CC = gcc
CFLAGS = -Wall -I./vendor/cJSON
DEPS = contact.h vendor/cJSON/cJSON.h
OBJ = main.o contact.o vendor/cJSON/cJSON.o

# Object compilation
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Create the executable
contact_manager: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Run the executable
run: contact_manager
	./contact_manager

# Clean the project from object files, executable and vendor folder
clean:
	rm -f *.o contact_manager
	rm -rf vendor/**

# Install dependencies
install-deps:
	mkdir -p vendor
	git clone https://github.com/DaveGamble/cJSON.git vendor/cJSON
