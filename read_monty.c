#include "monty.h"

command_t command = {NULL, 0, false, 0};

/**
 * read_from_file - reads the command from the monty file.
 *
 * @file_name: is the pointer to the file containing the commands.
 * @top: is the head of the stack.
 *
 * Return: void or none of null.
*/
void read_from_file(const char *file_name, stack_t **top)
{
	FILE *file = fopen(file_name, "r");
	unsigned int line_number = 0;
	size_t len = 0;
	ssize_t size;
	char *buffer;

	command.opcode = NULL, command.optional_param = false;
	if (!file)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s", file_name);
		exit(EXIT_FAILURE);
	}
	else
	{
		while ((size = getline(&buffer, &len, file)) != -1)
		{
			++line_number;
			buffer[size - 1] = '\0';

			if (buffer[0])
				if (buffer[0] != '#')
				{
					proccess(buffer, top, line_number);
					if (command.status != 0)
					{
						clear;
						logout;
					}
				}
			free(buffer);
			buffer = NULL;
		}
		if (buffer)
			free(buffer);
	}

	fclose(file);
}


/**
 * proccess - Function to process commands, remove spaces, and store data.
 *
 * @buffer: Pointer to the struct to store processed data.
 * @top: Input command to be processed.
 * @l:is hte number of line evaluated.
 *
 * Return: the asdjhfjds.
 */
void proccess(char *buffer, stack_t **top, unsigned int l)
{
	int i = 0, j = 0;
	bool isFinished = false;
	char *new = malloc(strlen(buffer) + 1);

	command.status = 0, command.optional_param = false;
	if (!new)
	{
		dprintf(STDERR_FILENO, "Error: Malloc failed\n");
		free(buffer);
		exit(EXIT_FAILURE);
	}
	while (buffer[i])
	{
		if (!isFinished && buffer[i] == ' ')
		{
			i++;
			continue;
		}
		if (!isFinished && buffer[i] != ' ')
			isFinished = true;
		if (isFinished)
		{
			if (buffer[i] != ' ')
				new[j++] = buffer[i++];
			else
			{
				new[j] = '\0';
				check_dig(&buffer[i]);
				simplify(new, top, l);
				return;
			}
		}
		else
			i++, new[j] = '\0';
	}
	simplify(new, top, l);
}

/**
 * check_dig - checks the digit of the inpt.
 *
 * @buffer: is the temporary storage.
 *
 * Return: nothing.
*/
void check_dig(char *buffer)
{
	int i = 0;

	if (atoi(&buffer[i]))
		command.optional_param = true, command.parameter = atoi(&(buffer[i]));
}



/**
 * find_func - is the function that is resposnsible to find the correct
 * function for the given opcode.
 *
 * @c: is the struct that contains the command and the parameter.
 * @top: is the pointer to the top of the stack.
 * @line_number: is the current line that is executing.
 *
 * Return: void - but exits if the command is not found in general.
*/
void find_func(const char *c, stack_t **top, unsigned int line_number)
{
	int i;
	instruction_t instructions[] = {
		{"push", st_push}, {"pall", st_pall}, {"pint", st_pint},
		{"pop", st_pop}, {"swap", st_swap},/** {"add", st_add},
		*{"nop", st_nop}, {"sub", st_sub}, {"div", st_div},
		*{"mul", st_mul}, {"mod", st_mod}, {"p_char", st_pchar},
		*{"pstr", st_pstr}, {"rotl", st_rotl}, {"rotr", st_rotr},
		*{"stack", st_stack}, {"queue", st_queue},*/ {NULL, NULL}
	};
	for (i = 0; instructions[i].opcode; i++)
		if (c && !strncmp(c, instructions[i].opcode, strlen(instructions[i].opcode)))
		{
			instructions[i].f(top, line_number);
			return;
		}
	if (!instructions[i].opcode)
	{
		dprintf(STDERR_FILENO, "L%u: unknown instruction %s\n",
											line_number, command.opcode);
		command.status = 1;
	}
}


/**
 * st_push - adds a new element to the top of the stack.
 *
 * @top: is a pointer to the top of the string.
 * @line_number: is the number of line to be executed.
 *
 * Return: void.
*/
void st_push(stack_t **top, unsigned int line_number)
{
	stack_t *temp = malloc(sizeof(stack_t));

	if (!temp)
	{
		dprintf(STDERR_FILENO, "Error: Malloc failed\n");
		command.status = 1;
	}
	else if (!command.optional_param)
	{
		dprintf(STDERR_FILENO, "L%u: usage: push integer\n", line_number);
		command.status = 1;
	}
	else
	{
		temp->n = command.parameter;
		temp->next = (*top);
		temp->prev = NULL;
		if (*top)
			(*top)->prev = temp;
		*top = temp;
	}
}
