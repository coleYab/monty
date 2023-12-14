#include "monty.h"

/***********************************************************************
 * This is the method collection that will be used to store all the    *
 * methos that requiresa a mandatory argument.                         *
 ***********************************************************************/

/**
 * st_pall - is the function to print all the elements of the stack.
 *
 * @top: is the top of the stack.
 * @line_number: is the number of the line.
 *
 * Return: void.
*/
void st_pall(stack_t **top, unsigned int line_number)
{
	stack_t *temp = *top;
	UNUSED line_number;

	while (temp)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
}


/**
 * st_pint - is a tool that is the used to print the tpp element of the stack.
 *
 * @top: is the pointer to the top of the stack.
 * @line_number: is the line number in the monty file.
 *
 * Return: void.
*/
void st_pint(stack_t **top, unsigned int line_number)
{
	if (*top != NULL)
	{
		printf("%d\n", (*top)->n);
	}
	else
	{
		dprintf(STDERR_FILENO, "L<%u>: can't pint, stack empty\n", line_number);
		command.status = 1;
	}
}


/**
 * st_pop - is the function to pop a value.
 *
 * @top: is the pointer to the top of the variable.
 * @line_number: is the currently interpreted line.
 *
 * Return: void.
*/
void st_pop(stack_t **top, unsigned int line_number)
{
	UNUSED line_number;

	if (!*top)
	{
		dprintf(STDERR_FILENO, "L%u: can't pop an empty stack", line_number);
		command.status = 1;
	}
	else
	{
		*top = (*top)->next;
		free((*top)->prev);
		(*top)->prev = NULL;
	}
}

/**
 * st_swap - is the variable to swap the first top 2 elements.
 *
 * @top: is pointer to the top of the node.
 * @line_number: is the current line being interpreted.
 *
 * Return: void or none or nothing.
*/
void st_swap(stack_t **top, unsigned int line_number)
{
	int temp = 0;
	UNUSED line_number;

	if (!*top || !(*top)->next)
	{
		dprintf(STDERR_FILENO, "L%u: Can't swap, stack too short", line_number);
		command.status = -1;
	}
	else
	{
		temp = (*top)->n;
		(*top)->n = ((*top)->next)->n;
		((*top)->next)->n = temp;
	}
}
