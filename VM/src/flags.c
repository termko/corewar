#include "head.h"

int		same_id(t_champ *champ, int id)
{
	t_champ *tmp;

	tmp = champ;
	while (tmp)
	{
		if (tmp->id == id)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	set_dump_flag(int *flag1, int *flag2)
{
	*flag1 = 1;
	if (*flag2 > 0)
		*flag2 = 0;
}

void	d_flag(t_fl *flag, int num, char *str, int *i)
{
	flag->num = num;
	if (flag->num < 0)
		exit(0);
	if (!(ft_strcmp(str, "dump")))
		set_dump_flag(&flag->dump, &flag->d);
	else
		set_dump_flag(&flag->d, &flag->dump);
	*i += 2;
}

void	live_aff_flag(t_fl *flag, int *i, int q)
{
	if (!q)
		flag->live = 0;
	else if (q == 1)
		flag->aff = 1;
	*i += 1;
}

void	n_flag(t_vm *vm, int num)
{
	if (num < 1 || num > MAX_ARGS_NUMBER || same_id(vm->champ, num))
		error("Invalid champion number\n", "");
}
