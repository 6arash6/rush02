/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tino <tino@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-02-15 14:11:15 by tino              #+#    #+#             */
/*   Updated: 2026-02-15 14:11:15 by tino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

static char	*skip_zeros(char *nbr)
{
	while (*nbr == '0' && *(nbr + 1))
		nbr++;
	return (nbr);
}

void	build_scale(char *key, int group)
{
	int	i;
	int	zeros;

	key[0] = '1';
	i = 1;
	zeros = group * 3;
	while (zeros > 0)
	{
		key[i] = '0';
		i++;
		zeros--;
	}
	key[i] = '\0';
}

static int	print_scale(int group, t_dict *dict, int *first)
{
	char	scale[100];
	char	*val;

	build_scale(scale, group);
	val = dict_get(dict, scale);
	if (!val)
		return (0);
	print_word(val, first);
	return (1);
}

static int	convert_loop(char *nbr, int len, int group, t_dict *dict)
{
	int	first;
	int	clen;

	first = 1;
	while (len > 0)
	{
		clen = len % 3;
		if (clen == 0)
			clen = 3;
		if (!is_zero_chunk(nbr, clen))
		{
			if (!convert_chunk(nbr, clen, dict, &first))
				return (0);
			if (group > 0 && !print_scale(group, dict, &first))
				return (0);
		}
		nbr += clen;
		len -= clen;
		group--;
	}
	return (1);
}

int	convert(char *nbr, t_dict *dict)
{
	int		len;
	int		group;
	char	*val;


	nbr = skip_zeros(nbr);
	len = ft_strlen(nbr);
	if (len == 1 && nbr[0] == '0')
	{

		val = dict_get(dict, "0");
		if (!val)
			return (0);
		ft_putstr(val);
		return (1);
	}
	group = (len + 2) / 3 - 1;
	return (convert_loop(nbr, len, group, dict));
}
