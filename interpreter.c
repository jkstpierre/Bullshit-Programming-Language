/*
	BullShit! Interpreter
	Author: Joseph St. Pierre
	Year: 2018
*/

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "interpreter.h"

int main(int argc, char *args[]) {
	printf(TEXT_COLOR_CYAN "=== BullShit! v1.0 ===\n");
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
						// TODO: Read syntax logs here
					}
				}
				else {
					// Run the program here
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
		
		program.length = (size_t) length;	// Store the length of the program
		
		program.cmds = (char *) malloc(program.length * sizeof(char));	//Allocate memory for the program
		
		rewind(file);	// Move file pointer back to beginning
		
		// Read each character from file into program
		size_t i;
		for (i = 0; i < program.length; i++) {
			program.cmds[i] = (char) fgetc(file);
		}
		
		// Close the file since we no longer need it
		fclose(file);
		file = NULL;
		
		/*
			Syntax checking here
		*/
		*error_code = check_syntax(program, logs);
		
		// Return the constructed program
		return program;
	}
}

int check_syntax(const program_t *program, syntax_logs_t *logs){
	
}
