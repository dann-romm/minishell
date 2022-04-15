#ifndef LIBFT_FUNCS_H
# define LIBFT_FUNCS_H

# define ABS(x) ((x) > 0 ? (x) : -(x))

# include <stdlib.h>
# include "shell.h"

int			is_alpha(char c);
int			is_numeric(char c);
int			is_alnum(char c);
int			is_space(char c);
char		*ft_strcpy(char *dest, char *src);
int			ft_strlen(char *str);
char		*ft_strdup(char *str);
char		*ft_strcat(char *dst, char *src);
char		*ft_strncat(char *s1, const char *s2, unsigned int n);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
int			ft_atoi(char *str);
char		*ft_itoa(int n);
int			ft_numlen(char *str);

char		**ft_split(char const *s, char c);
char		*ft_strjoin(char *s1, char *s2);
void		ft_putstr(char *s);
void		ft_putendl(char *s);

// in fact, just utils
int			free_2d_array(char **arr);
char		*three_str_cat(char *s1, char *s2, char *s3);
char		**adapt_cmd_args(t_simple_cmd *command);
char		*find_path(t_simple_cmd *command);
void		perror_exit(char *message);
char		**ht_to_array(t_hashtable *ht);

#endif
