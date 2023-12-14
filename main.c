#include "monty.h"

/**
 * main - entery point of the program.
 *
 * @argc: is the argument count.
 * @argv: is the argument vector.
 *
 * Return: 0 - in success or exit with the status 1 in failure.
*/
int main(int argc, char *argv[])
{
	stack_t *top = NULL;

/*passed*/
	if (argc < 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		logout;
	}
	else if (access(argv[1], R_OK))
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s", argv[1]);
		logout;
	}
	else
	{
		read_from_file(argv[1], &top);
	}
	free_it(&top);
	return (EXIT_SUCCESS);
}

/**
 * free_it - frees the doubly linked list.
 *
 * @top: the head pointer to the list.
 *
 * Return: none always success.
 */
void free_it(stack_t **top)
{
	stack_t *iterator = NULL;

	if (*top)
	{
		iterator = *top;
		while (iterator)
		{
			if (iterator->next)
			{
				iterator = iterator->next;
				free(iterator->prev);
			}
			else
			{
				free(iterator);
				return;
			}
		}
	}
}
