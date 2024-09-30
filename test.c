#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd);
void	ft_putstr_fd(char *s, int fd);

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
		for (int i = 1; i < argc; i++)
			test(argv[i]);
	}
	return (0);
}
