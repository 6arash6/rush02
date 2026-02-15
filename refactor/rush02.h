/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush02.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tino <tino@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-02-15 13:28:28 by tino              #+#    #+#             */
/*   Updated: 2026-02-15 13:28:28 by tino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Header file - Contains all function prototypes and the
struct definition. Include this in every .c file.*/
#ifndef RUSH02_H
# define RUSH02_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_dict
{
	char			*key;
	char			*value;
	struct s_dict	*next;
}	t_dict;

/* String utils */
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *str);
int		ft_isdigit(char c);
void	ft_putstr(char *str);

/* Validator */
int		is_valid(char *str);

/* Dictionary */
char	*read_dict_file(char *file);
t_dict	*new_entry(char *key, char *val);
void	add_entry(t_dict **dict, t_dict *entry);
t_dict	*parse_line(char *buf, int start, int end);
t_dict	*load_dict(char *file);
char	*dict_get(t_dict *dict, char *key);
void	dict_free(t_dict *dict);

/* Converter */
int		convert(char *nbr, t_dict *dict);
void	build_scale(char *key, int group);

/* Converter helpers (split) */
void	print_word(char *word, int *first);
int		is_zero_chunk(char *nbr, int len);
int		convert_chunk(char *nbr, int len, t_dict *dict, int *first);

#endif
