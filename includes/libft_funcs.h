#ifndef LIBFT_FUNCS_H
# define LIBFT_FUNCS_H

# include <stdlib.h>

int			is_alnum(char c);
int			is_space(char c);
char		*ft_strcpy(char *dest, char *src);
int			ft_strlen(char *str);
char		*ft_strdup(char *str);
char		*ft_strcat(char *dst, char *src);
char		*ft_strncat(char *s1, const char *s2, unsigned int n);
int			ft_strcmp(char *s1, char *s2);

#endif
