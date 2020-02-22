#include "head.h"

int		ft_addr(int value)
{
	value = value % MEM_SIZE;
	if (value < 0)
		value += MEM_SIZE;
	return (value);
}

int		reverse_negative(int negative, int size)
{
	int i;
	int tmp;

	i = 1;
	tmp = 0xff;
	negative -= 1;
	while (i < size)
	{
		tmp |= 0xff << (8 * i);
		i++;
	}
	return (negative ^ tmp);
}

int		bin2int(unsigned char *buf, int size)
{
	int	i;
	int	tmp;
	int ret;
	int	flag;

	i = 0;
	ret = 0;
	flag = 0;
	tmp = size * 8 - 8;
	while (i < size)
	{
		if (!i && buf[i] & (0x1 << 7))
			flag = 1;
		ret += buf[i] << tmp;
		tmp -= 8;
		i++;
	}
	if (flag)
		ret = -reverse_negative(ret, size);
	return (ret);
}

void	bin2str(int fd, char *buf, int len)
{
	int		size;

	size = read(fd, buf, len);
	if (size < 0)
		error("Error reading file\n", "");
	if (size != len)
		error("Invalid file\n", "");
}

void	set_to_arena(unsigned char *arena, int addr, int arg)
{
	*(arena + ft_addr(addr)) = (arg & 0xff000000) >> 24;
	*(arena + ft_addr(addr + 1)) = (arg & 0x00ff0000) >> 16;
	*(arena + ft_addr(addr + 2)) = (arg & 0x0000ff00) >> 8;
	*(arena + ft_addr(addr + 3)) = (arg & 0x000000ff);
}
