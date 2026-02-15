/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_chunk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tino <tino@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-02-15 13:56:11 by tino              #+#    #+#             */
/*   Updated: 2026-02-15 13:56:11 by tino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

#include "rush02.h"

void	print_word(char *word, int *first)
{
	if (!*first)
		write(1, " ", 1);
	*first = 0;
	ft_putstr(word);
}

int	is_zero_chunk(char *nbr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (nbr[i] != '0')
			return (0);
		i++;
	}
	return (1);
}

static int	convert_digit(char c, t_dict *dict, int *first)
{
	char	key[2];
	char	*val;

	if (c == '0')
		return (1);
	key[0] = c;
	key[1] = '\0';
	val = dict_get(dict, key);
	if (!val)
		return (0);
	print_word(val, first);
	return (1);
}

static int	convert_tens(char *nbr, t_dict *dict, int *first)
{
	char	key[3];
	char	*val;

	if (nbr[0] == '0')
		return (convert_digit(nbr[1], dict, first));
	if (nbr[0] == '1')
	{
		key[0] = nbr[0];
		key[1] = nbr[1];
		key[2] = '\0';
		val = dict_get(dict, key);
		if (!val)
			return (0);
		print_word(val, first);
		return (1);
	}
	key[0] = nbr[0];
	key[1] = '0';
	key[2] = '\0';
	val = dict_get(dict, key);
	if (!val)
		return (0);
	print_word(val, first);
	return (convert_digit(nbr[1], dict, first));
}

int	convert_chunk(char *nbr, int len, t_dict *dict, int *first)
{
	char	*val;

	if (len == 3 && nbr[0] != '0')
	{
		if (!convert_digit(nbr[0], dict, first))
			return (0);
		val = dict_get(dict, "100");
		if (!val)
			return (0);
		print_word(val, first);
		return (convert_tens(nbr + 1, dict, first));
	}
	if (len == 3)
		return (convert_tens(nbr + 1, dict, first));
	if (len == 2)
		return (convert_tens(nbr, dict, first));
	if (len == 1)
		return (convert_digit(nbr[0], dict, first));
	return (0);
}
