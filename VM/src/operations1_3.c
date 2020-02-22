#include "head.h"

static char	*champ_name(t_champ *chmp, int id)
{
	t_champ *champ;

	champ = chmp;
	while (champ)
	{
		if (champ->id == id)
			return (champ->header.prog_name);
		champ = champ->next;
	}
	error("Champ %s is wrong", chmp->header.prog_name);
	return (NULL);
}

void		op_live(t_cursor *cursor, t_vm *vm)
{
	unsigned char	*arena;
	int				arg;
	int				move;

	cursor->last_live_cycle_nbr = vm->num_of_cycles;
	vm->nbr_live++;
	arena = vm->arena;
	move = 1;
	arg = get_args(cursor, arena, 0, &move);
	if (arg >= -vm->players_num && arg <= -1)
	{
		if (vm->flag.live)
			printf("A process shows that player %d (%s) IS ALIVE\n",
					-arg, champ_name(vm->champ, -arg));
		vm->last_live = -arg;
	}
}

void		op_ld(t_cursor *cursor, t_vm *vm)
{
	int				value;
	int				arg2;
	unsigned char	*arena;

	arena = vm->arena;
	if (cursor->arg_type[0] == T_DIR)
	{
		arg2 = *(arena + ft_addr(cursor->cur_position + 2 + DIR_SIZE));
		value = bin2int(arena + ft_addr(cursor->cur_position + 2), DIR_SIZE);
		cursor->r[arg2 - 1] = value;
		cursor->carry = !value ? 1 : 0;
	}
	else if (cursor->arg_type[0] == T_IND)
	{
		arg2 = *(arena + ft_addr(cursor->cur_position + 2 + IND_SIZE));
		value = cursor->cur_position + (bin2int(arena +
							ft_addr(cursor->cur_position + 2), IND_SIZE));
		cursor->r[arg2 - 1] = bin2int(arena + ft_addr(value), 4);
		cursor->carry = !cursor->r[arg2 - 1] ? 1 : 0;
	}
}

void	op_st(t_cursor *cursor, t_vm *vm)
{
	int				addr;
	int				arg[2];
	unsigned char	*arena;

	arena = vm->arena;
	arg[0] = arena[ft_addr(cursor->cur_position + 2)] - 1;
	if (cursor->arg_type[1] == T_REG)
	{
		arg[1] = *(arena + ft_addr(cursor->cur_position + 3)) - 1;
		cursor->r[arg[1]] = cursor->r[arg[0]];
	}
	else if (cursor->arg_type[1] == T_IND)
	{
		arg[1] = bin2int(arena + ft_addr(cursor->cur_position + 3), IND_SIZE);
		addr = ft_addr(cursor->cur_position + (arg[1] % IDX_MOD));
		set_to_arena(arena, addr, cursor->r[arg[0]]);
	}
}
