#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd);

void	test(char *file)
{
	int		fd;
	char	*text;

	fd = open(file, O_RDONLY);
	do
	{
		text = get_next_line(fd);
		if (text)
		{
			ft_putstr_fd(text, 1);
			free(text);
		}
	} while (text);
	close(fd);
	ft_putstr_fd("\n----\n", 1);
}

int	main(int argc, char *argv[])
{
	if (argc == 1)
	{
		test("empty.txt");
		test("1char.txt");
		test("1line.txt");
		test("morelines.txt");
		test("1nl.txt");
		test("onlynl.txt");
	}
	else {
		test(argv[1]);
	}
	return (0);
}
