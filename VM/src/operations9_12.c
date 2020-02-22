#include "head.h"

void	op_zjmp(t_cursor *cursor, t_vm *vm)
{
	int				res;
	int				tmp;
	int				move;
	unsigned char	*arena;

	arena = vm->arena;
	move = 1;
	res = get_args(cursor, arena, 0, &move);
	if (!cursor->carry)
		return ;
	tmp = ft_addr(res % IDX_MOD);
	cursor->cur_position = ft_addr(cursor->cur_position + tmp);
	cursor->bytes_to_next_op = 0;
}

void	op_ldi(t_cursor *cursor, t_vm *vm)
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
	cursor->r[to] = bin2int(arena + ft_addr(cursor->cur_position +
					(args[0] + args[1]) % IDX_MOD), REG_SIZE);
}

void	op_sti(t_cursor *cursor, t_vm *vm)
{
	unsigned char	*arena;
	int				args[3];
	int				move;
	int				addr;

	arena = vm->arena;
	move = 2;
	args[0] = get_args(cursor, arena, 0, &move);
	args[1] = get_args(cursor, arena, 1, &move);
	args[2] = get_args(cursor, arena, 2, &move);
	addr = ft_addr(cursor->cur_position + (args[1] + args[2]) % IDX_MOD);
	set_to_arena(arena, addr, args[0]);
}

void	op_fork(t_cursor *cursor, t_vm *vm)
{
	t_cursor		*add;
	int				addr;
	unsigned char	*arena;

	arena = vm->arena;
	addr = bin2int(arena + ft_addr(cursor->cur_position + 1), 2);
	malloc_err((add = (t_cursor*)malloc(sizeof(t_cursor))), "op_fork");
	vm->cursor->prev = add;
	add->next = vm->cursor;
	vm->cursor = add;
	add->prev = NULL;
	add->id = ++(vm->num_of_cursors);
	ft_memcpy(add->r, cursor->r, sizeof(cursor->r));
	add->carry = cursor->carry;
	add->last_live_cycle_nbr = cursor->last_live_cycle_nbr;
	add->cur_position = ft_addr(ft_addr(addr % IDX_MOD) +
									cursor->cur_position);
	add->op_code = 0;
	add->cycles_before_op = 0;
	add->bytes_to_next_op = 0;
}
