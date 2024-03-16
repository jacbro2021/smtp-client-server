#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"

int main(int argc, char** argv) {
	(void)argc;

	size_t input_length = strlen(argv[1]) + 2; // add one for null terminator.
	char* user_input = (char*)malloc(input_length);

	strcpy(user_input, argv[1]);
	user_input[input_length - 2] = '\n';
	user_input[input_length - 1] = '\0';

	return mail_from_cmd(user_input);
}

