#include "libft.h"

int	ft_chr_count(char *line, char t)
{
	int	i;

	i = 0;
	while (*line)
	{
		if (*line == t)
			i++;
		line++;
	}
	return (i);
}
