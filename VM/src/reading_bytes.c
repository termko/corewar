#include "head.h"

int				read_bin(int fd, int len, char *file)
{
	int				size;
	unsigned char	buf[4];

	size = read(fd, &buf, len);
	if (size < 0)
		error("Error reading file: %s\n", file);
	if (size != len)
		error("Invalid file: %s\n", file);
	return (bin2int(buf, len));
}

unsigned char	*read_code(int fd, int len, char *file)
{
	unsigned char	*buf;
	unsigned char	end_of_file;
	int				size;

	malloc_err((buf = (unsigned char*)malloc(sizeof(unsigned char) *
									len)), "read_code");
	size = read(fd, buf, len);
	if (size < 0)
		error("Error reading file: %s\n", file);
	if (size < len)
		error("Invalid file: %s\n", file);
	if (read(fd, &end_of_file, 1) != 0)
		error("Invalid file: %s\n", file);
	return (buf);
}
