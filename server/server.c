/*
 * This program implements the function signatures defined in parser.h
 * as well as any helper functions necessary. The intention for this
 * program is to parse the context free grammar as defined in RFC 822
 *
 * Author(s): Jacob Brown
 *
 * Date created: 3/15/2024
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"

#define MAX_LENGTH 320

int main(void) {
	char input[MAX_LENGTH];
	fgets(input, MAX_LENGTH, stdin);

	size_t input_length = strlen(input) + 1; // add one for null terminator.
	char* user_input = (char*)malloc(input_length);
	strcpy(user_input, input);
	int result = mail_from_cmd(user_input);
	printf("%d\n", result);
	free(user_input);
	fflush(stdout);
	return EXIT_SUCCESS;
}

