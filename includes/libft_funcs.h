#ifndef LIBFT_FUNCS_H
# define LIBFT_FUNCS_H

# include <stdlib.h>

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
int			ft_atoi(char *str);
int			ft_numlen(char *str);

char		**ft_split(char const *s, char c);
char		*ft_strjoin(char *s1, char *s2);
void		ft_putstr(char *s);
void		ft_putendl(char *s);

int			free_2d_array(char **arr);

#endif
