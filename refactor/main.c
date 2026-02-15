/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tino <tino@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-02-15 13:32:29 by tino              #+#    #+#             */
/*   Updated: 2026-02-15 13:32:29 by tino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*Entry point - Handles command-line arguments,
 calls other functions, manages the program flow.
*/
#include "rush02.h"

static void	set_args(int ac, char **av, char **dict_file, char **number)
{
	if (ac == 3)
	{
		*dict_file = av[1];
		*number = av[2];
		return ;
	}
	*dict_file = "numbers.dict";
	*number = av[1];
}

int	main(int ac, char **av)
{
	t_dict	*dict;
	char	*dict_file;
	char	*number;

	if (ac < 2 || ac > 3)
		return (1);
	set_args(ac, av, &dict_file, &number);
	if (!is_valid(number))
		return (ft_putstr("Error\n"), 1);
	dict = load_dict(dict_file);
	if (!dict)
		return (ft_putstr("Dict Error\n"), 1);
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
