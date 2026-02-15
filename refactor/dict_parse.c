/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tino <tino@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-02-15 13:55:34 by tino              #+#    #+#             */
/*   Updated: 2026-02-15 13:55:34 by tino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

static int	is_end_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
		return (1);
	return (0);
}

static char	*trim_range(char *str, int start, int end)
{
	char	*res;
	int		i;

	while (start <= end && (str[start] == ' ' || str[start] == '\t'))
		start++;
	while (end > start && is_end_space(str[end]))
		end--;
	res = malloc(end - start + 2);
	if (!res)
		return (NULL);
	i = 0;
	while (start <= end)
		res[i++] = str[start++];
	res[i] = '\0';
	return (res);
}

t_dict	*parse_line(char *buf, int start, int end)
{
	int		colon;
	char	*key;
	char	*val;

	colon = start;
	while (colon <= end && buf[colon] != ':')
		colon++;
	if (colon > end || colon == start)
		return (NULL);
	key = trim_range(buf, start, colon - 1);
	val = trim_range(buf, colon + 1, end);
	if (!key || !val)
		return (free(key), free(val), NULL);
	return (new_entry(key, val));
}

t_dict	*load_dict(char *file)
{
	char	*buf;
	t_dict	*dict;
	int		i;
	int		start;

	buf = read_dict_file(file);
	if (!buf)
		return (NULL);
	dict = NULL;
	i = 0;
	while (buf[i])
	{
		while (buf[i] && (buf[i] == '\n' || buf[i] == '\r'))
			i++;
		start = i;
		while (buf[i] && buf[i] != '\n')
			i++;
		if (i > start)
			add_entry(&dict, parse_line(buf, start, i - 1));
	}
	free(buf);
	return (dict);
}

char	*dict_get(t_dict *dict, char *key)
{
	while (dict)
	{
		if (ft_strcmp(dict->key, key) == 0)
			return (dict->value);
		dict = dict->next;
	}
	return (NULL);
}
