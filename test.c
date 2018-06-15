#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

size_t width = 0;
size_t height = 0;
uint8_t **memory = NULL;

long x = 0;
long y = 0;

uint8_t curr_value = 0;
uint8_t is_held = 0;

void main(){
	width = 4;
	height = 4;
	memory = (uint8_t **) calloc(sizeof(uint8_t *), height);

	size_t i;
	for(i = 0; i < height; i++){
		memory[i] = (uint8_t *) calloc(sizeof(uint8_t), width);
	}

	is_held = 1;
	curr_value = memory[y][x];

	assert(is_held == 1);
	curr_value = !curr_value;

	is_held = 0;
	memory[y][x] = curr_value;

	printf("%x", memory[y][x]);

	is_held = 1;
	curr_value = memory[y][x];

	x = x + 1; if (x == width) x = 0;
	if (is_held) curr_value += memory[y][x];

	is_held = 0;
	memory[y][x] = curr_value;

	printf("%x", memory[y][x]);

	x = x - 1; if (x < 0) x = width - 1;
	if (is_held) curr_value -= memory[y][x];

	is_held = 1;
	curr_value = memory[y][x];

	x = x + 1; if (x == width) x = 0;
	if (is_held) curr_value += memory[y][x];

	x = x + 1; if (x == width) x = 0;
	if (is_held) curr_value += memory[y][x];

	is_held = 0;
	memory[y][x] = curr_value;

	printf("%x", memory[y][x]);



	for(i = 0; i < height; i++){
		free(memory[i]);
	}

	free(memory);
printf("\n");
}
