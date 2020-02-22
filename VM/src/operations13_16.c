#include "head.h"

int		get_args(t_cursor *cursor, unsigned char *arena, int i, int *move)
{
	int		ret;
	int		size;
	t_op	*op_tab;

	op_tab = t_op_tab();
	if (cursor->arg_type[i] == T_REG)
	{
		ret = cursor->r[*(arena + ft_addr(cursor->cur_position + *move)) - 1];
		*move += 1;
	}
	if (cursor->arg_type[i] == T_DIR)
	{
		size = op_tab[cursor->op_code].size_of_t_dir ? 2 : 4;
		ret = bin2int(arena + ft_addr(cursor->cur_position + *move), size);
		*move += size;
	}
	if (cursor->arg_type[i] == T_IND)
	{
		ret = bin2int(arena + ft_addr(cursor->cur_position + *move), IND_SIZE);
		ret = bin2int(arena + ft_addr(cursor->cur_position +
									ft_addr(ret % IDX_MOD)), 4);
		*move += 2;
	}
	return (ret);
}

void	op_lld(t_cursor *cursor, t_vm *vm)
{
	int				value;
	int				arg2;
	int				move;
	unsigned char	*arena;

	arena = vm->arena;
	if (cursor->arg_type[0] == T_DIR)
	{
		arg2 = *(arena + ft_addr(cursor->cur_position + 2 + 4));
		value = bin2int(arena + ft_addr(cursor->cur_position + 2), 4);
		cursor->r[arg2 - 1] = value;
		cursor->carry = !value ? 1 : 0;
	}
	else if (cursor->arg_type[0] == T_IND)
	{
		arg2 = *(arena + ft_addr(cursor->cur_position + 2 + 4));
		value = cursor->cur_position + (bin2int(arena +
										ft_addr(cursor->cur_position + 2), 4));
		cursor->r[arg2 - 1] = bin2int(arena + ft_addr(value), 4);
		cursor->carry = !cursor->r[arg2 - 1] ? 1 : 0;
	}
}

void	op_lldi(t_cursor *cursor, t_vm *vm)
{
	unsigned char	*arena;
	int				move;
	int				args[2];
	int				to;

	arena = vm->arena;
	move = 2;
	args[0] = get_args(cursor, arena, 0, &move);
	args[1] = get_args(cursor, arena, 1, &move);
	to = *(arena + ft_addr(cursor->cur_position + move)) - 1;
	cursor->r[to] = bin2int(arena +
		ft_addr(cursor->cur_position + args[0] + args[1]), REG_SIZE);
	if (cursor->r[to])
		cursor->carry = 0;
	else
		cursor->carry = 1;
}

void	op_lfork(t_cursor *cursor, t_vm *vm)
{
	t_cursor		*add;
	int				addr;
	unsigned char	*arena;

	arena = vm->arena;
	addr = bin2int(arena + ft_addr(cursor->cur_position + 1), 2);
	malloc_err((add = (t_cursor*)malloc(sizeof(t_cursor))), "op_lfork");
	vm->cursor->prev = add;
	add->next = vm->cursor;
	vm->cursor = add;
	add->prev = NULL;
	add->id = ++(vm->num_of_cursors);
	ft_memcpy(add->r, cursor->r, sizeof(cursor->r));
	add->carry = cursor->carry;
	add->last_live_cycle_nbr = cursor->last_live_cycle_nbr;
	add->cur_position = ft_addr(ft_addr(addr) + cursor->cur_position);
	add->op_code = 0;
	add->cycles_before_op = 0;
	add->bytes_to_next_op = 0;
}

void	op_aff(t_cursor *cursor, t_vm *vm)
{
	unsigned char	*arena;
	int				move;
	int				arg;

	arena = vm->arena;
	move = 2;
	arg = get_args(cursor, arena, 0, &move);
	if (vm->flag.aff)
		ft_printf("aff: %c\n", (char)arg);
}
