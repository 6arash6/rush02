//Input validation - Checks if the input is a valid number (only digits, no negatives, no decimals).
#include "rush02.h"

int	is_valid(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
