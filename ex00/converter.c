//Number to words - Converts the number string into words by splitting it into chunks and looking up values in the dictionary.
#include "rush02.h"

void	print_word(char *word, int *first)
{
	if (!*first)
		write(1, " ", 1);
	*first = 0;
	ft_putstr(word);
}

char	*skip_zeros(char *nbr)
{
	while (*nbr == '0' && *(nbr + 1))
		nbr++;
	return (nbr);
}

int	convert_digit(char c, t_dict *dict, int *first)
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

int	convert_tens(char *nbr, t_dict *dict, int *first)
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
	
	/* BONUS 1: Add hyphen between tens and ones
	if (nbr[1] != '0')
		write(1, "-", 1);
	*/
	
	return (convert_digit(nbr[1], dict, first));
}

int	convert_hundreds(char *nbr, t_dict *dict, int *first)
{
	char	*val;

	if (nbr[0] != '0')
	{
		if (!convert_digit(nbr[0], dict, first))
			return (0);
		val = dict_get(dict, "100");
		if (!val)
			return (0);
		print_word(val, first);
		
		/* BONUS 1: Add "and" before tens in hundreds
		if (nbr[1] != '0' || nbr[2] != '0')
		{
			print_word("and", first);
		}
		*/
	}
	return (convert_tens(nbr + 1, dict, first));
}

void	build_scale(char *key, int group)
{
	int	i;
	int	zeros;

	key[0] = '1';
	i = 1;
	zeros = group * 3;
	while (zeros--)
		key[i++] = '0';
	key[i] = '\0';
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

int	process_chunk(char *nbr, int len, t_dict *dict, int *first)
{
	if (len == 3)
		return (convert_hundreds(nbr, dict, first));
	else if (len == 2)
		return (convert_tens(nbr, dict, first));
	else if (len == 1)
		return (convert_digit(nbr[0], dict, first));
	return (0);
}

int	convert(char *nbr, t_dict *dict)
{
	int		len;
	int		groups;
	int		group;
	int		first;
	int		chunk_len;
	char	scale[100];
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
	groups = (len + 2) / 3;
	group = groups - 1;
	first = 1;
	while (len > 0)
	{
		chunk_len = (len % 3 == 0) ? 3 : len % 3;
		if (!is_zero_chunk(nbr, chunk_len))
		{
			if (!process_chunk(nbr, chunk_len, dict, &first))
				return (0);
			if (group > 0)
			{
				build_scale(scale, group);
				val = dict_get(dict, scale);
				if (!val)
					return (0);
				
				/* BONUS 1: Add comma after major scales
				if (group > 1)
					write(1, ",", 1);
				*/
				
				print_word(val, &first);
			}
		}
		nbr += chunk_len;
		len -= chunk_len;
		group--;
	}
	return (1);
}
