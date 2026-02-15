//Dictionary parser - Opens and reads the numbers.dict file, parses "key: value" lines, stores them in a linked list.
#include "rush02.h"

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
	{
		close(fd);
		return (NULL);
	}
	ret = read(fd, buf, 65535);
	close(fd);
	if (ret < 0)
	{
		free(buf);
		return (NULL);
	}
	buf[ret] = '\0';
	return (buf);
}

char	*trim(char *str, int start, int end)
{
	char	*res;
	int		i;

	while (str[start] == ' ' || str[start] == '\t')
		start++;
	while (end > start && (str[end] == ' ' || str[end] == '\t' 
		|| str[end] == '\n' || str[end] == '\r'))
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
	t_dict	*tmp;

	if (!entry)
		return ;
	if (!*dict)
		*dict = entry;
	else
	{
		tmp = *dict;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = entry;
	}
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
	key = trim(buf, start, colon - 1);
	val = trim(buf, colon + 1, end);
	if (!key || !val)
	{
		if (key)
			free(key);
		if (val)
			free(val);
		return (NULL);
	}
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
