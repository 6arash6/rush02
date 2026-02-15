/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tino <tino@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-02-15 13:55:16 by tino              #+#    #+#             */
/*   Updated: 2026-02-15 13:55:16 by tino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

static t_dict	*dict_last(t_dict *dict)
{
	while (dict && dict->next)
		dict = dict->next;
	return (dict);
}

char	*read_dict_file(char *file)
{
	int		fd;
	char	*buf;
	int		ret;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	buf = malloc(65536);
	if (!buf)
		return (close(fd), NULL);
	ret = read(fd, buf, 65535);
	close(fd);
	if (ret < 0)
		return (free(buf), NULL);
	buf[ret] = '\0';
	return (buf);
}

t_dict	*new_entry(char *key, char *val)
{
	t_dict	*entry;

	entry = malloc(sizeof(t_dict));
	if (!entry)
		return (NULL);
	entry->key = key;
	entry->value = val;
	entry->next = NULL;
	return (entry);
}

void	add_entry(t_dict **dict, t_dict *entry)
{
	t_dict	*last;

	if (!entry)
		return ;
	if (!*dict)
	{
		*dict = entry;
		return ;
	}
	last = dict_last(*dict);
	last->next = entry;
}

void	dict_free(t_dict *dict)
{
	t_dict	*tmp;

	while (dict)
	{
		tmp = dict->next;
		free(dict->key);
		free(dict->value);
		free(dict);
		dict = tmp;
	}
}
