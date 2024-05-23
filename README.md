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
