//Entry point - Handles command-line arguments, calls other functions, manages the program flow.
#include "rush02.h"

int	main(int ac, char **av)
{
	t_dict	*dict;
	char	*dict_file;
	char	*number;

	if (ac < 2 || ac > 3)
		return (1);
	dict_file = (ac == 3) ? av[1] : "numbers.dict";
	number = (ac == 3) ? av[2] : av[1];
	
	/* BONUS 3: Check if reading from stdin
	if (ft_strcmp(number, "-") == 0)
	{
		dict = load_dict(dict_file);
		if (!dict)
		{
			ft_putstr("Dict Error\n");
			return (1);
		}
		read_and_convert_stdin(dict);
		dict_free(dict);
		return (0);
	}
	*/
	
	if (!is_valid(number))
	{
		ft_putstr("Error\n");
		return (1);
	}
	dict = load_dict(dict_file);
	if (!dict)
	{
		ft_putstr("Dict Error\n");
		return (1);
	}
	
	// Validate dictionary has all needed entries BEFORE converting
	if (!validate_conversion(number, dict))
	{
		ft_putstr("Dict Error\n");
		dict_free(dict);
		return (1);
	}
	
	if (!convert(number, dict))
	{
		ft_putstr("Dict Error\n");
		dict_free(dict);
		return (1);
	}
	write(1, "\n", 1);
	dict_free(dict);
	return (0);
}
