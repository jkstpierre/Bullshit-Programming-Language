/*
	BullShit! Compiler
	Author: Joseph St. Pierre
	Year: 2018
*/

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "compiler.h"

int main(int argc, char *args[]) {
	printf(TEXT_COLOR_CYAN "=== Bull$hit! Compiler v1.0 ===\n");
	if (argc == 1) {
		printf(TEXT_COLOR_RED "Error: " TEXT_COLOR_RESET "No input files specified...\n");
		exit(EXIT_FAILURE);
	}
	else{
		int i;
		for (i = 1; i < argc; i++) {
			char *filepath = args[i];	// Copy filepath
			
			// Check file extension
			const char *ext = get_extension(filepath);
			
			if (strcmp(ext, VALID_FILE_EXTENSION)) {
				printf(TEXT_COLOR_RED "Error: " TEXT_COLOR_RESET "Invalid file extension! ");
				printf("Expected '.bs' got '.%s'\n", ext);
			}
			else {
				// Given valid file extension, create a bullshit program
				int error_code = ERROR_NONE;
				
				// BullShit! program syntax logs
				syntax_logs_t logs = {0, NULL};
				
				program_t prgm = create_program(filepath, &error_code, &logs);
				
				// Check if fatal error during program creation occurred
				if (error_code != ERROR_NONE) {
					if (error_code == ERROR_FILE_NOT_FOUND) {
						printf(TEXT_COLOR_RED "Error: " TEXT_COLOR_RESET "Input file %s not found!\n", filepath);
					}
					else if (error_code == ERROR_PROGRAM_SYNTAX) {
						printf(TEXT_COLOR_RED "Error: " TEXT_COLOR_RESET "Input file %s has syntax errors!\n", filepath);
						
						print_logs(&logs);	// Print syntax logs
						delete_logs(&logs);	// Free log memory
					}
				}
				else {
					// Compile the program here
				}
			}
		}
	}
	
	exit(EXIT_SUCCESS);
}

/*
	Attribution:
	URL: https://stackoverflow.com/questions/5309471/getting-file-extension-in-c
	User: ThiefMaster
*/
const char *get_extension(const char *filepath) {
	const char *dot = strrchr(filepath, '.');
	if (!dot || dot == filepath) return "";
	return dot + 1;
}

program_t create_program(char *filepath, int *error_code, syntax_logs_t *logs) {
	// Without a means to communicate errors, all hope is lost
	assert(error_code != NULL);
	assert(filepath != NULL);
	assert(logs != NULL);
	
	// Attempt to open the input file for reading
	FILE *file = fopen(filepath, "r");
	
	if (!file) {
		// The file failed to load
		
		*error_code = ERROR_FILE_NOT_FOUND;
		program_t junk_program = {0, NULL};
		return junk_program;
	}
	else {
		program_t program;	// The program structure
		
		// Get the file's length in bytes
		int code = fseek(file, 0L, SEEK_END);
		
		assert(code == 0);	// Check for error
		
		long length = ftell(file);	// Get the length of the file
		
		assert(length != -1);	// Check for error
		
		program.cmds = (char *) malloc(length * sizeof(char));	//Allocate memory for the program
		
		rewind(file);	// Move file pointer back to beginning
		
		// Read each command from file into program, prune everything else
		size_t index = 0;	// Track current command index
		int c;	// Temp variable
		while ((c = fgetc(file)) != EOF) {
			char cmd = (char) c;	// Copy command
			
			switch(cmd) {
				case CMD_HEADER:
				case CMD_UP:
				case CMD_DOWN:
				case CMD_LEFT:
				case CMD_RIGHT:
				case CMD_NOT:
				case CMD_INVERT:
				case CMD_LOOP_S:
				case CMD_LOOP_E:
				case CMD_IN_CHR:
				case CMD_OUT_CHR:
				case CMD_IN_HEX:
				case CMD_OUT_HEX:
					program.cmds[index++] = cmd;
					break;
				default:
					break;
			}
		}
		
		program.length = index;	// Set the program length
		
		program.cmds = (char *) realloc(program.cmds, program.length * sizeof(char));	// Resize the array
		
		// Close the file since we no longer need it
		fclose(file);
		file = NULL;
		
		/*
			Syntax checking here
		*/
		*error_code = check_syntax(&program, logs);
		
		// Return the constructed program
		return program;
	}
}

int check_syntax(const program_t *program, syntax_logs_t *logs) {
	int error_code = ERROR_NONE;
	
	int header = 0;	// Has the header been set yet?
	int program_start = 0;	// Has the program code begun yet?
	
	int bracket_count = 0;	// Number of brackets in program
	
	size_t i;
	for (i = 0; i < program->length; i++) {
		char cmd = program->cmds[i];	// Get the current command
		
		if (header == 0) {
			if (cmd != CMD_HEADER) {
				create_log_message(logs, "Header settings not specified at program start");
				return ERROR_PROGRAM_SYNTAX;	// Indicate error immediately
			}
			else {
				header = 1;	// Header is set
			}
		}
		else if (header == 1) {
			if (cmd == CMD_HEADER && program_start == 1) {
				create_log_message(logs, "Cannot specify header after program start");
				error_code = ERROR_PROGRAM_SYNTAX;	// Indicate error
			}
			else if (cmd != CMD_HEADER) {
				program_start = 1;	// Program has started
				
				if (cmd == CMD_LOOP_S) {
					bracket_count++;
				}
				else if (cmd == CMD_LOOP_E) {
					bracket_count--;
					
					if (bracket_count < 0) {
						create_log_message(logs, "Cannot start conditional loop with closing bracket");
						error_code = ERROR_PROGRAM_SYNTAX;
					}
				}
			}
		}
	}
	
	if (bracket_count != 0) {
		create_log_message(logs, "Bracket mismatch found");
		error_code = ERROR_PROGRAM_SYNTAX;
	}
	
	return error_code;
}

void create_log_message(syntax_logs_t *logs, const char *message) {
	logs->messages = realloc(logs->messages, (++logs->length) * sizeof(*logs->messages));
	strcpy(logs->messages[logs->length - 1], message);
}

void print_logs(const syntax_logs_t *logs) {
	size_t i;
	for (i = 0; i < logs->length; i++) {
		printf(TEXT_COLOR_RED "Syntax Error %lu: " TEXT_COLOR_RESET "%s\n", i, logs->messages[i]);
	}
	
	printf("\nPlease fix errors and try again...\n");
}

void delete_logs(syntax_logs_t *logs) {
	free(logs->messages);
	logs->messages = NULL;
	logs->length = 0;
}

void compile_program(const program_t *program) {

}