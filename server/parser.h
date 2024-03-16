/* Definitions for error codes and top-level parsing functions 
 * to be used by the SMTP server to process incoming TCP messages.
 *
 * Author(s): Jacob Brown
 *
 * Date created: 3/15/2024
*/

/* Return value definitions.
 * ------------------------
 *
 * Return values other than 0 and 1 will be used to indicate error 
 * messages as follows. These constants are defined here for clarity 
 * throughout the parser.
*/
#define TRUE 0
#define FALSE 1
#define WHITESPACE_ERR 2
#define PATH_ERR 3
#define MAILBOX_ERR 4
#define STRING_ERR 5
#define ELEMENT_ERR 6
#define NEWLINE_ERR 7
#define MAIL_FROM_CMD_ERR 8
#define RCPT_TO_CMD_ERR 9
#define DATA_CMD_ERR 10

/* High-level parsing non-terminals.
 * --------------------------------
 *
 * Functions to parse major non-terminals from RFC 822 such as the 
 * 'MAIL FROM', 'RCPT TO', and 'DATA' commands. 
 *
 * The input parameter
 * for each of these functions represents the input received from 
 * a connected TCP socket (or the command line during testing).
*/
int mail_from_cmd(char* input);
int rcpt_to_cmd(char* input);
int data_cmd(char* input);
