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

int	validate_conversion(char *nbr, t_dict *dict)
{
	int		len;
	int		groups;
	int		group;
	char	scale[100];

	nbr = skip_zeros(nbr);
	len = ft_strlen(nbr);
	
	// Check if "0" exists for zero case
	if (len == 1 && nbr[0] == '0')
		return (dict_get(dict, "0") != NULL);
	
	// Check if "100" exists
	if (len >= 3 && !dict_get(dict, "100"))
		return (0);
	
	// Check if all needed scales exist
	groups = (len + 2) / 3;
	group = groups - 1;
	while (group > 0)
	{
		build_scale(scale, group);
		if (!dict_get(dict, scale))
			return (0);
		group--;
	}
	return (1);
}
