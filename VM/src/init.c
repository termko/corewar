#include "head.h"

void		init_operations(t_vm *vm)
{
	vm->do_oper[0] = &op_live;
	vm->do_oper[1] = &op_ld;
	vm->do_oper[2] = &op_st;
	vm->do_oper[3] = &op_add;
	vm->do_oper[4] = &op_sub;
	vm->do_oper[5] = &op_and;
	vm->do_oper[6] = &op_or;
	vm->do_oper[7] = &op_xor;
	vm->do_oper[8] = &op_zjmp;
	vm->do_oper[9] = &op_ldi;
	vm->do_oper[10] = &op_sti;
	vm->do_oper[11] = &op_fork;
	vm->do_oper[12] = &op_lld;
	vm->do_oper[13] = &op_lldi;
	vm->do_oper[14] = &op_lfork;
	vm->do_oper[15] = &op_aff;
}

t_cursor	*create_cursor(t_cursor **cursor)
{
	t_cursor *new;

	malloc_err((new = (t_cursor*)malloc(sizeof(t_cursor))), "create_cursor");
	new->next = *cursor;
	(*cursor)->prev = new;
	new->prev = NULL;
	return (new);
}

void		init_cursor(t_cursor *new, size_t *num, t_champ *champ)
{
	new->id = ++(*num);
	new->carry = 0;
	new->op_code = 0;
	new->last_live_cycle_nbr = 0;
	new->cycles_before_op = 0;
	new->cur_position = champ->start_from;
	new->bytes_to_next_op = 0;
	ft_bzero(new->arg_type, sizeof(new->arg_type));
	ft_bzero(new->r, sizeof(new->r));
	new->r[0] = -champ->id;
}

t_cursor	*init_first_cursors(t_vm *vm)
{
	t_cursor	*new_curs;
	t_champ		*champ;

	new_curs = NULL;
	champ = vm->champ;
	while (champ)
	{
		if (!new_curs)
		{
			new_curs = (t_cursor*)malloc(sizeof(t_cursor));
			new_curs->next = NULL;
			new_curs->prev = NULL;
		}
		else
			new_curs = create_cursor(&new_curs);
		init_cursor(new_curs, &vm->num_of_cursors, champ);
		champ = champ->next;
	}
	return (new_curs);
}
