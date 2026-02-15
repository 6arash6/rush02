/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tino <tino@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-02-15 13:29:15 by tino              #+#    #+#             */
/*   Updated: 2026-02-15 13:29:15 by tino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Input validation - Checks if the input is a
 valid number (only digits, no negatives, no decimals).*/
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
