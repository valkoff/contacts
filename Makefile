CC = gcc
CFLAGS = -Wall -I./cJSON
DEPS = contact.h vendor/cJSON/cJSON.h
OBJ = main.o contact.o vendor/cJSON/cJSON.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

contact_manager: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
