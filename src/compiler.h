#ifndef _BULLSHIT_COMPILER_H_
#define _BULLSHIT_COMPILER_H_

/*
	Copyright (c) 2018 Joseph St. Pierre

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

// INCLUDES //

#include <stdlib.h>


// DEFINITIONS //

#define TRUE 1
#define FALSE 0

#define VALID_FILE_EXTENSION	"bs"
#define KEEP_SOURCE_FLAG		"-s"
#define ERROR_NONE				0
#define ERROR_FILE_NOT_FOUND	-1
#define ERROR_PROGRAM_SYNTAX	-2

#define TEXT_COLOR_PREFIX "\033"
#define TEXT_COLOR_RED TEXT_COLOR_PREFIX "[1;31m"
#define TEXT_COLOR_CYAN TEXT_COLOR_PREFIX "[1;36m"
#define TEXT_COLOR_RESET TEXT_COLOR_PREFIX "[0m"

#define CMD_HEADER	'#'
#define CMD_UP		'^'
#define CMD_DOWN	'v'
#define CMD_LEFT	'<'
#define CMD_RIGHT	'>'
#define CMD_ZERO	'0'
#define CMD_ONE		'1'
#define CMD_PICKUP	'+'
#define CMD_DROP	'-'
#define CMD_LOOP_S	'{'
#define CMD_LOOP_E	'}'
#define CMD_IN_CHR	','
#define CMD_OUT_CHR	'.'
#define CMD_IN_DEC	';'
#define CMD_OUT_DEC	':'
#define COMMENT 	'/'


// DATA STRUCTURES //

/*Data structure to hold instruction set*/
typedef struct program_t {
	char name[128];
	size_t length;
	char *cmds;
} program_t;

/*Data structure to hold syntax checking logs*/
typedef struct syntax_logs_t {
	size_t length;
	char (*messages)[256];
} syntax_logs_t;

// GLOBAL VARIABLES //

unsigned char keep_source = FALSE;	// If TRUE, generated C code will not be deleted


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
