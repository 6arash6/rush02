//Header file - Contains all function prototypes and the struct definition. Include this in every .c file.
#ifndef RUSH02_H
# define RUSH02_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define BUFFER_SIZE 4096

typedef struct s_dict_entry
{
	char				*key;
	char				*value;
	struct s_dict_entry	*next;
}	t_dict;

// String utilities
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_atoi(char *str);
int		is_digit(char c);
int		is_space(char c);

// Number validation
int		is_valid_number(char *str);

// Dictionary functions
t_dict	*parse_dictionary(char *filename);
char	*get_dict_value(t_dict *dict, char *key);
void	free_dict(t_dict *dict);
t_dict	*create_entry(char *key, char *value);
void	add_entry(t_dict **dict, t_dict *entry);

// Number conversion

// File reading
char	*read_file(char *filename);


#endif
