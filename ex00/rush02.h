//Header file - Contains all function prototypes and the struct definition. Include this in every .c file.
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
t_dict	*load_dict(char *file);
char	*dict_get(t_dict *dict, char *key);
void	dict_free(t_dict *dict);

/* Converter */
int		convert(char *nbr, t_dict *dict);

/* BONUS 3: stdin reading */
// void	read_and_convert_stdin(t_dict *dict);

#endif
