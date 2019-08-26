#include "libft.h"

long	ft_atol(const char *str)
{
	long int	i;
	long int	res;
	long int	neg;
	
	i = 0;
	res = 0;
	neg = 1;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\r' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == ' ')
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + ((str[i++] - '0') * neg);
	return (res);
}
