#include "head.h"

void	free_all(t_vm *vm)
{
	t_champ *champ;

	while (vm->champ)
	{
		champ = vm->champ;
		vm->champ = vm->champ->next;
		free(champ->exec_code);
		free(champ);
		champ = NULL;
	}
	free(vm);
}

int		main(int argc, char **argv)
{
	t_vm		*vm;

	vm = NULL;
	if (argc < 2)
		usage();
	vm = init_vm();
	argc--;
	argv++;
	parsing_args(vm, &argc, &argv);
	introduce(vm->champ);
	init_arena(vm);
	vm->cursor = init_first_cursors(vm);
	in_cycle(vm);
	print_winner(vm);
	free_all(vm);
	return (0);
}
