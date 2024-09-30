#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	*get_next_line(int fd);

void	test(char *file)
{
	int		fd;
	char	*text;

	ft_putstr_fd(file, 1);
	ft_putstr_fd("\n----\n", 1);
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

void	test_read_error(char *file)
{
	int		fd;
	char	*text;

	ft_putstr_fd(file, 1);
	ft_putstr_fd("\n----\n", 1);
	fd = open(file, O_RDONLY);
	for (int i = 0; i < 2; i++)
	{
		text = get_next_line(fd);
		ft_putstr_fd(text, 1);
		free(text);
	}
	close(fd);
	fd = -1;
	text = get_next_line(fd);
	if (text)
		ft_putstr_fd(text, 1);
	else
		ft_putstr_fd("(NULL)\n", 1);
	fd = open(file, O_RDONLY);
	for (int i = 0; i < 2; i++)
	{
		text = get_next_line(fd);
		ft_putstr_fd(text, 1);
		free(text);
	}
	close(fd);
	ft_putstr_fd("\n----\n", 1);
}

int	main(int argc, char *argv[])
{
	if (argc == 1)
		printf("At least one file required");
	else
	{
		for (int i = 1; i < argc; i++)
			if (strcmp(argv[i], "read_error.txt"))
				test(argv[i]);
			else
				test_read_error(argv[i]);
	}
	return (0);
}
