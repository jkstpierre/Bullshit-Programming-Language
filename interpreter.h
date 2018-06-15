#ifndef _BULLSHIT_INTERPRETER_H_
#define _BULLSHIT_INTERPRETER_H_

/*
	BullShit! Interpreter
	Author: Joseph St. Pierre
	Year: 2018
*/

// INCLUDES //

#include <stdlib.h>


// DEFINITIONS //

#define VALID_FILE_EXTENSION "bs"
#define ERROR_NONE			  0
#define ERROR_FILE_NOT_FOUND -1
#define ERROR_PROGRAM_SYNTAX -2


// DATA STRUCTURES //

/*Data structure to hold instruction set*/
typedef struct program_t {
	size_t length;
	char *cmds;
} program_t;

/*Data structure to hold syntax checking logs*/
typedef struct syntax_logs_t {
	size_t length;
	char **messages;
} syntax_logs_t;


// FUNCTIONS //

/*Check for valid file extension*/
const char *get_extension(const char *filepath);

/*Generate program from input file*/
program_t create_program(char *filepath, int *error_code, syntax_logs_t *logs);

/*Destroy a program and free resources*/
void destroy_program(program_t *program);

#endif
