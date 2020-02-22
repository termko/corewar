#include "head.h"

void	parsing_dumps(int *ac, char ***av, t_fl *flag)
{
	int i;

	i = 0;
	while (i < *ac && (*av)[i][0] == '-' && (*av)[i][1])
		if ((!ft_strcmp((*av)[i] + 1, "d") || !ft_strcmp((*av)[i] + 1, "dump"))\
			&& i + 2 < *ac && ft_isnumber((*av)[i + 1]))
			d_flag(flag, ft_atoi((*av)[i + 1]), (*av)[i] + 1, &i);
		else if (!ft_strcmp((*av)[i] + 1, "l"))
			live_aff_flag(flag, &i, 0);
		else if (!ft_strcmp((*av)[i] + 1, "aff"))
			live_aff_flag(flag, &i, 1);
		else if (!ft_strcmp((*av)[i] + 1, "n")
				&& i + 1 < *ac && ft_isnumber((*av)[i + 1]))
			break ;
		else
			usage();
	(*av) += i;
	(*ac) -= i;
	if (!*ac)
		usage();
}

void	parsing_args(t_vm *vm, int *ac, char ***av)
{
	int				i;
	int				n;

	parsing_dumps(ac, av, &vm->flag);
	i = -1;
	while (++i < *ac)
	{
		if ((*av)[i][0] == '-' && (*av)[i][1])
		{
			if (!ft_strcmp((*av)[i] + 1, "n") &&
				i + 2 < *ac && ft_isnumber((*av)[i + 1]))
			{
				n_flag(vm, (n = ft_atoi((*av)[i + 1])));
				init_champs(vm, (*av)[i + 2], n, i + 3 >= *ac);
				i += 2;
				continue ;
			}
			else
				usage();
		}
		init_champs(vm, (*av)[i], 0, i + 1 >= *ac);
	}
	set_ids_to_champs(vm);
	ins_sort(&vm->champ, vm->players_num);
}
