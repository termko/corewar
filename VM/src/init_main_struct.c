#include "head.h"

void	init_arena(t_vm *vm)
{
	size_t			i;
	t_champ			*champ;
	unsigned char	*arena;
	int				next_byte;

	i = 0;
	champ = vm->champ;
	next_byte = MEM_SIZE / vm->players_num;
	arena = vm->arena;
	ft_bzero(vm->arena, MEM_SIZE);
	while (champ)
	{
		ft_memcpy(arena, champ->exec_code, champ->header.prog_size);
		champ->start_from = i;
		champ = champ->next;
		i += next_byte;
		arena += next_byte;
	}
}

t_vm	*init_vm(void)
{
	t_vm *vm;

	malloc_err((vm = (t_vm*)malloc(sizeof(t_vm))), "init_vm");
	vm->champ = NULL;
	vm->flag = (t_fl){-1, 0, 0, 1, 0};
	vm->players_num = 0;
	vm->last_live = 0;
	vm->num_of_cycles = 0;
	vm->nbr_live = 0;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->checks = 0;
	vm->num_of_cursors = 0;
	vm->cursor = NULL;
	vm->cycles_before_check = CYCLE_TO_DIE;
	init_operations(vm);
	return (vm);
}

void	init_champs(t_vm *vm, char *file, int id, int flag)
{
	t_champ		*champ;
	t_champ		*new;
	static int	max_id = 1;

	if (!vm->champ)
	{
		malloc_err((vm->champ = (t_champ*)malloc(sizeof(t_champ))), "init_ch");
		champ = vm->champ;
	}
	else
	{
		champ = vm->champ;
		while (champ->next)
			champ = champ->next;
		malloc_err((new = (t_champ*)malloc(sizeof(t_champ))), "init_champs");
		champ->next = new;
		champ = champ->next;
	}
	champ->id = id;
	max_id = id > max_id ? id : max_id;
	champ->next = NULL;
	check_valid(file, champ);
	vm->players_num++;
	if (flag && max_id > vm->players_num)
		usage();
}
