#include "head.h"

void	op_add(t_cursor *cursor, t_vm *vm)
{
	unsigned char	*arena;
	int				sum;
	int				args[3];

	arena = vm->arena;
	args[0] = *(arena + ft_addr(cursor->cur_position + 2)) - 1;
	args[1] = *(arena + ft_addr(cursor->cur_position + 3)) - 1;
	args[2] = *(arena + ft_addr(cursor->cur_position + 4)) - 1;
	sum = cursor->r[args[0]] + cursor->r[args[1]];
	cursor->r[args[2]] = sum;
	if (!sum)
		cursor->carry = 1;
	else
		cursor->carry = 0;
}

void	op_sub(t_cursor *cursor, t_vm *vm)
{
	int				sum;
	int				args[3];
	unsigned char	*arena;

	arena = vm->arena;
	args[0] = *(arena + ft_addr(cursor->cur_position + 2)) - 1;
	args[1] = *(arena + ft_addr(cursor->cur_position + 3)) - 1;
	args[2] = *(arena + ft_addr(cursor->cur_position + 4)) - 1;
	sum = cursor->r[args[0]] - cursor->r[args[1]];
	cursor->r[args[2]] = sum;
	if (!sum)
		cursor->carry = 1;
	else
		cursor->carry = 0;
}

void	op_and(t_cursor *cursor, t_vm *vm)
{
	int				sum;
	int				to;
	int				args[2];
	int				move;
	unsigned char	*arena;

	arena = vm->arena;
	move = 2;
	args[0] = get_args(cursor, arena, 0, &move);
	args[1] = get_args(cursor, arena, 1, &move);
	to = *(arena + ft_addr(cursor->cur_position + move)) - 1;
	sum = args[0] & args[1];
	cursor->r[to] = sum;
	if (!sum)
		cursor->carry = 1;
	else
		cursor->carry = 0;
}

void	op_or(t_cursor *cursor, t_vm *vm)
{
	int				sum;
	int				to;
	int				args[2];
	int				move;
	unsigned char	*arena;

	arena = vm->arena;
	move = 2;
	args[0] = get_args(cursor, arena, 0, &move);
	args[1] = get_args(cursor, arena, 1, &move);
	to = *(arena + ft_addr(cursor->cur_position + move)) - 1;
	sum = args[0] | args[1];
	cursor->r[to] = sum;
	if (!sum)
		cursor->carry = 1;
	else
		cursor->carry = 0;
}

void	op_xor(t_cursor *cursor, t_vm *vm)
{
	int				sum;
	int				to;
	int				args[2];
	int				move;
	unsigned char	*arena;

	arena = vm->arena;
	move = 2;
	args[0] = get_args(cursor, arena, 0, &move);
	args[1] = get_args(cursor, arena, 1, &move);
	to = *(arena + ft_addr(cursor->cur_position + move)) - 1;
	sum = args[0] ^ args[1];
	cursor->r[to] = sum;
	if (!sum)
		cursor->carry = 1;
	else
		cursor->carry = 0;
}
