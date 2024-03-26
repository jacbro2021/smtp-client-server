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

int space(char* input);

/*
 * Evaluates a char to check if it matches the whitespace non-terminal.
 * if whitespace is found, the pointer is moved past any continuous
 * whitespace.
 *
 * Returns:
 * 	int: 0 or 1 indicating false or true that the input char was
 * 	     whitespace.
*/
int whitespace(char* input) 
{
	if (space(input))
	{
		while (space(input)) input++;
		return TRUE;
	}
	return FALSE;
}

/*
 * Evaluates a char to check if it matches the space terminal. if the
 * char passed as input is a space, true is returned and false
 * otherwise.
 *
 * This function does not advance the pointer passed as an arg.
*/
int space(char* input)
{
	if (*input == ' ' || *input == '\t')
	{
		return TRUE;
	}
	return FALSE;
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

/*
 * Recursively parses the 'MAIL FROM:' command.
 *
 * Args:
 * 	input: char* to the character to parse.
 * 	expected: char that is expected to be parsed.
 * 	second_m: 0 or 1 int used to indicate when the second M is being parsed.
 *
 * Returns:
 * 	int: 0 if correct, non-zero error code otherwise.
 */
int mail_from_non_terminal(char* input, char expected, int second_m)
{
	if (*input++ == expected) 
	{
		switch (expected) 
		{
			case 'M':
				if (!second_m)
				{
					return mail_from_non_terminal(input, 'A', FALSE);	
				} else 
				{
					return mail_from_non_terminal(input, ':', FALSE);
				}

			case 'A':
				return mail_from_non_terminal(input, 'I', FALSE);
			case 'I':
				return mail_from_non_terminal(input, 'L', FALSE);
			case 'L':
				return mail_from_non_terminal(input, ' ', FALSE);
			case ' ':
				return mail_from_non_terminal(input, 'F', FALSE);
			case 'F':
				return mail_from_non_terminal(input, 'R', FALSE);
			case 'R':
				return mail_from_non_terminal(input, 'O', FALSE);
			case 'O':
				return mail_from_non_terminal(input, 'M', TRUE);
			case ':':
				return VALID;
		}
	} else 
	{
		return MAIL_FROM_CMD_ERR;
	}


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
	return whitespace(input);
}

int rcpt_to_cmd(char* input)
{
	return TRUE;
}

int data_cmd(char* input)
{
	return TRUE;
}
