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
#include "parser.h"

int whitespace(char* input) 
{
	return TRUE;
}

int space(char* input)
{
	return TRUE;
}

int nullspace(char* input)
{
	return TRUE;
}

int reverse_path(char* input)
{
	return TRUE;
}

int path(char* input)
{
	return TRUE;
}

int mailbox(char* input)
{
	return TRUE;
}

int local_part(char* input)
{
	return TRUE;
}

int string(char* input)
{
	return TRUE;
}

int character(char* input)
{
	return TRUE;
}

int domain(char* input)
{
	return TRUE;
}

int element(char* input)
{
	return TRUE;
}

int name(char* input)
{
	return TRUE;
}

int letter(char* input)
{
	return TRUE;
}

int let_dig_str(char* input)
{
	return TRUE;
}

int let_dig(char* input)
{
	return TRUE;
}

int digit(char* input)
{
	return TRUE;
}

int newline(char* input)
{
	return TRUE;
}

int special(char* input)
{
	return TRUE;
}

int mail_from_non_terminal(char* input)
{
	return TRUE;
}

int rcpt_to_non_terminal(char* input)
{
	return TRUE;
}

int data_non_terminal(char* input)
{
	return TRUE;
}

int mail_from_cmd(char* input)
{
	while (*input != '\0') 
	{
		printf("char: %c\n", *input);
		input++;
	}
	return 0;
}

int rcpt_to_cmd(char* input)
{
	return TRUE;
}

int data_cmd(char* input)
{
	return TRUE;
}
