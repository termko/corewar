#include "head.h"

void	error(char *format, void *str)
{
	ft_fprintf(stderr, format, str);
	exit(1);
}

void	malloc_err(void *addr, char *func)
{
	if (!addr)
		error("malloc error in %s\n", func);
}

void	args_number(int num)
{
	if (num > MAX_ARGS_NUMBER)
		error("Too many champions\n", "");
}

void	usage(void)
{
	ft_fprintf(stderr, "Usage: ./corewar [-d N -dump N -l -aff] [[-n N]");
	ft_fprintf(stderr, "<champion1.cor>] <...>\n\n");
	ft_fprintf(stderr, "    -l:		turn off live-operation output\n");
	ft_fprintf(stderr, "    -aff:   	turn on aff-operation output\n");
	ft_fprintf(stderr, "    -d N:	dumps memory after N cycles then exists ");
	ft_fprintf(stderr, "(64 octets)\n");
	ft_fprintf(stderr, "    -dump N:	dumps memory after N cycles then ");
	ft_fprintf(stderr, "exists (32 octets)\n");
	ft_fprintf(stderr, "    -n N:	sets the number of next player. ");
	ft_fprintf(stderr, "If non-existent, the player\n\t\twill have the next");
	ft_fprintf(stderr, "available number in the order of the parameters.\n");
	exit(1);
}
