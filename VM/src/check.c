#include "head.h"

static t_cursor	*remove_one(t_cursor **head, t_cursor **curr)
{
	t_cursor *tmp;

	tmp = NULL;
	if (*curr == *head)
	{
		*head = (*head)->next;
		if (*head)
			(*head)->prev = NULL;
	}
	else
	{
		if ((*curr)->next)
			(*curr)->next->prev = (*curr)->prev;
		if ((*curr)->prev)
			(*curr)->prev->next = (*curr)->next;
	}
	tmp = (*curr)->next;
	free(*curr);
	return (tmp);
}

void			remove_dead_cursors(t_vm *vm, t_cursor *cursor)
{
	t_cursor *curr;
	t_cursor *tmp;

	tmp = NULL;
	curr = vm->cursor;
	while (curr)
		if (vm->num_of_cycles - curr->last_live_cycle_nbr >= vm->cycles_to_die
				|| vm->cycles_to_die <= 0)
			curr = remove_one(&vm->cursor, &curr);
		else
			curr = curr->next;
}

void			inspection(t_vm *vm, t_cursor *cursor)
{
	vm->checks++;
	remove_dead_cursors(vm, cursor);
	if (vm->nbr_live >= NBR_LIVE || vm->checks == MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		vm->checks = 0;
	}
	vm->nbr_live = 0;
	vm->cycles_before_check = vm->cycles_to_die;
}
