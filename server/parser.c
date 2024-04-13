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
#include <ctype.h>
#include "parser.h"

int space(char **input);
int path(char **input);
int local_part(char **input);
int domain(char **input);
int string(char **input);
int mailbox(char **input);
int digit(char **input);
int let_dig(char **input);
int let_dig_str(char **input);
int letter(char **input);
int name(char **input);
int special(char **input);
int character(char **input);
int element(char **input);

/*
 * Evaluates a char to check if it matches the whitespace non-terminal.
 * if whitespace is found, the pointer is moved past any continuous
 * whitespace.
 *
 * Returns:
 * 	int: 0 or 1 indicating false or true that the input char was
 * 	     whitespace.
 */
int whitespace(char **input)
{
	if (space(input))
	{
		while (space(input))
			(*input)++;
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
int space(char **input)
{
	if (**input == ' ' || **input == '\t')
	{
		return TRUE;
	}
	return FALSE;
}

void nullspace(char **input)
{
	while (space(input))
		(*input)++;
}

/*
 * Parses the reverse_path non-terminal.
 */
int reverse_path(char **input)
{
	return path(input);
}

/*
 * Parses the path non-terminal. This function increments the
 * input pointer.
 *
 * This function can return an error code if it fails to parse the '<',
 * '>' or if the mailbox function returns an error code.
 *
 * Returns:
 * 	int: Either a path error or mailbox error if an error occurs,
 * 		 otherwise returns true.
 */
int path(char **input)
{
	if (**input != '<')
	{
		return PATH_ERR;
	}
	(*input)++;

	int mailbox_result = mailbox(input);
	if (mailbox_result == MAILBOX_ERR || mailbox_result == ELEMENT_ERR)
	{
		return mailbox_result;
	}

	if (**input != '>')
	{
		return PATH_ERR;
	}

	return TRUE;
}

/* Parses the mailbox non-terminal from the input string.
 *
 *  Returns:
 *  	int: Either an element error, mailbox error or a string
 *	error if an error occurs, otherwise returns true.
 */
int mailbox(char **input)
{
	int local_res = local_part(input);
	if (local_res == STRING_ERR)
		return local_res;

	if (**input != '@')
		return MAILBOX_ERR;

	(*input)++;
	int domain_res = domain(input);
	if (domain_res == ELEMENT_ERR)
		return domain_res;

	return TRUE;
}

// Parse the local part of a mailbox.
int local_part(char **input)
{
	return string(input);
}

/* Parse a string non-terminal for any string errors.
 *
 * Returns:
 *	int: String error if errors are present, otherwise
 *		 returns true.
 */
int string(char **input)
{
	if (character(input))
	{
		(*input)++;
		while (character(input))
			(*input)++;
		return TRUE;
	}
	else
		return STRING_ERR;
}

/* Parse the character non-terminal. Accepts all characters
	that are not spaces or 'special' characters.
*/
int character(char **input)
{
	if (special(input) || space(input))
		return FALSE;
	return TRUE;
}

/* Parse the domain non-terminal, which is comprised of one
	or more element non-terminals.

	Returns:
		int: Either an element error or true.
*/
int domain(char **input)
{
	int result = element(input);
	if (result && result != ELEMENT_ERR)
	{
		int element_res = element(input);
		while (element_res && element_res != ELEMENT_ERR)
		{
			(*input)++;
			element_res = element(input);
		}

		while (**input == '.')
		{
			(*input)++;
			element_res = element(input);
			while (element_res && element_res != ELEMENT_ERR)
			{
				if (!letter(input) && !digit(input))
				{
					break;
				}
				(*input)++;
				element_res = element(input);
			}
		}

		return TRUE;
	}
	else
	{
		return result;
	}
}

/*
	Parses the element non-terminal. If the input does not
	return an element then the element error code is thrown.
*/
int element(char **input)
{
	if (name(input))
		return TRUE;
	return ELEMENT_ERR;
}

// Parse the name non-terminal.
int name(char **input)
{
	if (letter(input))
	{
		let_dig_str(input);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

// Parse the letter non-terminal.
int letter(char **input)
{
	if (((**input >= 'A' && **input <= 'Z') || (**input >= 'a' && **input <= 'z')) && (**input != ' '))
	{
		return TRUE;
	}
	return FALSE;
}

// Parses through all subsequent let-dig-str non-terminals.
int let_dig_str(char **input)
{
	if (let_dig(input))
	{
		while (let_dig(input))
		{
			(*input)++;
		}
		return TRUE;
	}
	return FALSE;
}

// Parses the letter-digit non-terminal.
int let_dig(char **input)
{
	if (letter(input) || digit(input))
	{
		return TRUE;
	}
	return FALSE;
}

// Parses a charater input and determines if it
// is a 0-9 digit.
int digit(char **input)
{
	return isdigit(**input);
}

// Parses the character input to determine if it is a newline.
// returns the newline error code if the input is not a newline.
int newline(char **input)
{
	if (**input == '\n')
		return TRUE;
	return NEWLINE_ERR;
}

/// @brief Parses the character given as input to determine if the current character is 'special'.
/// @param input 
/// @return 1 if the character is special, 0 otherwise. 
int special(char **input)
{
	char special_chars[] = {'<', '>', '(', ')', '[', ']', '\\', '.', ',', ';', ':', '@', '"'};

	int i;
	for (i = 0; i < sizeof(special_chars); i++)
	{
		if (**input == special_chars[i])
		{
			return TRUE;
		}
	}
	return FALSE;
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
int mail_from_non_terminal(char **input, char expected, int second_m)
{
	if (**input == expected)
	{
		(*input)++;
		switch (expected)
		{
		case 'M':
			if (!second_m)
			{
				return mail_from_non_terminal(input, 'A', FALSE);
			}
			else
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
			return TRUE;
		}
	}
	else
	{
		return MAIL_FROM_CMD_ERR;
	}

	return TRUE;
}

int rcpt_to_non_terminal(char *input)
{
	return TRUE;
}

int data_non_terminal(char *input)
{
	return TRUE;
}

int mail_from_cmd(char *input)
{
	int mail_from = mail_from_non_terminal(&input, 'M', FALSE);
	if (mail_from != TRUE)
		return mail_from;

	nullspace(&input);

	int reverse = reverse_path(&input);
	if (reverse != TRUE)
		return reverse;
	/*
		nullspace(input);

		int end_line = newline(input);
		if (end_line != TRUE)
			return end_line;
	*/
	return TRUE;
}

int rcpt_to_cmd(char *input)
{
	return TRUE;
}

int data_cmd(char *input)
{
	return TRUE;
}
