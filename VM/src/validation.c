#include "head.h"

void		check_valid(char *file, t_champ *champ)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error("Error open file: %s\n", file);
	champ->header.magic = read_bin(fd, MAGIC_HEADER_SIZE, file);
	if (champ->header.magic != COREWAR_EXEC_MAGIC)
		error("Magic header: %s\n", file);
	bin2str(fd, champ->header.prog_name, PROG_NAME_LENGTH);
	if (read_bin(fd, NULL_SIZE, file) != 0)
		error("No NULL after champion: %s\n", file);
	champ->header.prog_size = read_bin(fd, EXEC_CODE_SIZE, file);
	if (champ->header.prog_size > CHAMP_MAX_SIZE)
	{
		ft_fprintf(stderr, "Error: File ");
		fprintf(stderr, "%s has too large a code %d bytes > 682 bytes)\n",
				file, champ->header.prog_size);
		exit(1);
	}
	bin2str(fd, champ->header.comment, COMMENT_LENGTH);
	if (read_bin(fd, NULL_SIZE, file) != 0)
		error("No NULL after champion file: %s\n", file);
	champ->exec_code = read_code(fd, champ->header.prog_size, file);
}

int			size_arg_type(int arg, int op_code)
{
	t_op	*op_tab;

	op_tab = t_op_tab();
	if (arg == T_REG)
		return (1);
	else if (arg == T_IND)
		return (2);
	else if (arg == T_DIR)
		return (op_tab[op_code].size_of_t_dir ? 2 : 4);
	return (0);
}

int			check_arg_type(t_cursor *cursor)
{
	int		i;
	int		ret;
	t_op	*op_tab;

	i = 0;
	ret = 1;
	op_tab = t_op_tab();
	cursor->bytes_to_next_op = 1 + (op_tab[cursor->op_code].code_type_args ?
																		1 : 0);
	while (i < op_tab[cursor->op_code].arg_num)
	{
		if ((cursor->arg_type[i] & op_tab[cursor->op_code].arg[i]) == 0)
			ret = 0;
		cursor->bytes_to_next_op += size_arg_type(cursor->arg_type[i],
														cursor->op_code);
		i++;
	}
	return (ret);
}

int			check_registers(t_cursor *cursor, unsigned char *arena)
{
	int		i;
	int		bytes_to_jmp;
	int		reg;
	t_op	*op_tab;

	op_tab = t_op_tab();
	i = 0;
	bytes_to_jmp = ft_addr(cursor->cur_position + 1 +
			(op_tab[cursor->op_code].code_type_args ? 1 : 0));
	while (i < op_tab[cursor->op_code].arg_num)
	{
		if (cursor->arg_type[i] == T_REG)
		{
			reg = bin2int(arena + ft_addr(bytes_to_jmp), 1);
			if (reg < 1 || reg > REG_NUMBER)
				return (0);
		}
		bytes_to_jmp += size_arg_type(cursor->arg_type[i], cursor->op_code);
		i++;
	}
	return (1);
}
