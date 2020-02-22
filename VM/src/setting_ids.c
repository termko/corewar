#include "head.h"

void	sorting(t_champ **head, t_champ *new)
{
	t_champ *curr;

	if (!*head || (*head)->id >= new->id)
	{
		new->next = *head;
		*head = new;
		return ;
	}
	curr = *head;
	while (curr->next && curr->next->id < new->id)
		curr = curr->next;
	new->next = curr->next;
	curr->next = new;
}

void	ins_sort(t_champ **head, int num)
{
	t_champ *next;
	t_champ *sorted;
	t_champ *curr;

	if (num < 2)
		return ;
	sorted = NULL;
	curr = *head;
	while (curr)
	{
		next = curr->next;
		sorting(&sorted, curr);
		curr = next;
	}
	*head = sorted;
}

void	set_ids_to_champs(t_vm *vm)
{
	t_champ		*champ;
	static int	ids[4] = {1, 2, 3, 4};

	args_number(vm->players_num);
	champ = vm->champ;
	while (champ)
	{
		if (champ->id != 0)
			ids[champ->id - 1] = 0;
		champ = champ->next;
	}
	champ = vm->champ;
	while (champ)
	{
		if (champ->id == 0)
		{
			if (ids[0] != 0 || ids[1] != 0)
				champ->id = ids[0] != 0 ? ids[0] : ids[1];
			else if (ids[2] != 0 || ids[3] != 0)
				champ->id = ids[2] != 0 ? ids[2] : ids[3];
			ids[champ->id - 1] = 0;
		}
		champ = champ->next;
	}
}
