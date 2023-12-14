#ifndef MONTY_H
#define MONTY_H
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>


/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;


/**
 * struct Command - is the struct to store the major data.
 *
 * @opcode: is the instruction to be interpreted.
 * @parameter: is hte major input to the user.
 * @is_valid: checks if the parameter is valid.
*/
typedef struct Command
{
	char *opcode;
	int parameter;
	bool optional_param;
	int status;
} command_t;

#define clear free_it(top)
#define logout exit(EXIT_FAILURE)
#define MAX_LINE_SIZE 256
#define UNUSED (void)

extern command_t command;


void check_dig(char *);
void simplify(char *, stack_t **, unsigned int);
void free_it(stack_t **top);
void read_from_file(const char *, stack_t **);
void proccess(char *, stack_t **, unsigned int);
/*finds and executes the command*/
void find_func(const char *, stack_t **top, unsigned int line_number);
void st_push(stack_t **top, unsigned int line_number);
void st_pall(stack_t **top, unsigned int line_number);
void st_pint(stack_t **top, unsigned int line_number);
void st_pop(stack_t **top, unsigned int line_number);
void st_swap(stack_t **top, unsigned int line_number);
void st_add(stack_t **top, unsigned int line_number);
void st_nop(stack_t **top, unsigned int line_number);
void st_sub(stack_t **top, unsigned int line_number);
void st_div(stack_t **top, unsigned int line_number);
void st_mul(stack_t **top, unsigned int line_number);
void st_mod(stack_t **top, unsigned int line_number);
void st_pchar(stack_t **top, unsigned int line_number);
void st_pstr(stack_t **top, unsigned int line_number);
void st_rotl(stack_t **top, unsigned int line_number);
void st_rotr(stack_t **top, unsigned int line_number);
void st_stack(stack_t **top, unsigned int line_number);
void st_queue(stack_t **top, unsigned int line_number);


#endif
