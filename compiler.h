#ifndef _BULLSHIT_COMPILER_H_
#define _BULLSHIT_COMPILER_H_

/*
	BullShit! Compiler
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

#define TEXT_COLOR_PREFIX "\033"
#define TEXT_COLOR_RED TEXT_COLOR_PREFIX "[1;31m"
#define TEXT_COLOR_CYAN TEXT_COLOR_PREFIX "[1;36m"
#define TEXT_COLOR_RESET TEXT_COLOR_PREFIX "[0m"

#define CMD_HEADER	'#'
#define CMD_UP		'^'
#define CMD_DOWN	'v'
#define CMD_LEFT	'<'
#define CMD_RIGHT	'>'
#define CMD_NOT		'!'
#define CMD_INVERT	'~'
#define CMD_LOOP_S	'['
#define CMD_LOOP_E	']'
#define CMD_IN_CHR	','
#define CMD_OUT_CHR	'.'
#define CMD_IN_HEX	';'
#define CMD_OUT_HEX	':'


// DATA STRUCTURES //

/*Data structure to hold instruction set*/
typedef struct program_t {
	size_t length;
	char *cmds;
} program_t;

/*Data structure to hold syntax checking logs*/
typedef struct syntax_logs_t {
	size_t length;
	char (*messages)[256];
} syntax_logs_t;


// FUNCTIONS //

/*Check for valid file extension*/
const char *get_extension(const char *filepath);

/*Generate program from input file*/
program_t create_program(char *filepath, int *error_code, syntax_logs_t *logs);

/*Check syntax validity*/
int check_syntax(const program_t *program, syntax_logs_t *logs);

/*Add a message to the syntax logs*/
void create_log_message(syntax_logs_t *logs, const char *message);

/*Print syntax logs*/
void print_logs(const syntax_logs_t *logs);

/*Compile the program into a Unix executable*/
void compile_program(const program_t *program);

/*Delete logs*/
void delete_logs(syntax_logs_t *logs);

/*Destroy a program and free resources*/
void delete_program(program_t *program);

#endif
