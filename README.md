# Contact Manager

This is a sample project to manage a contact list in C, using the cJSON library to handle JSON data.

## Requirements

- GCC (or any other C compiler)
- [Make](https://www.gnu.org/software/make/)

## Installation

To install the dependencies, run the following command:

```sh
make install-deps
```

This command will clone the cJSON repository into the `vendor` folder of the project.

## Compilation

To compile the project, run the following command:

```sh
make
```

## Usage

To run the program, execute the following command:

```sh
make run
```

## Cleaning

To clean the project from object files, executables, and the vendor folder, run the following command:

```sh
make clean
```

## Project Structure

```
project/
├── vendor/
│   └── cJSON/
│       ├── cJSON.c
│       ├── cJSON.h
│       └── ...
├── storage/
├── contact.c
├── contact.h
├── main.c
├── Makefile
├── .gitignore
└── README.md
```

## Makefile

The Makefile includes the following targets:

- **contact_manager:** Compiles the project.
- **run:** Compiles and runs the program.
- **clean:** Removes the compiled files and the vendor folder.
- **install-deps:** Clones the cJSON repository into the `vendor` folder.

```Makefile
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
```
