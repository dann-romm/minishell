/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_funcs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:33:28 by mgwyness          #+#    #+#             */
/*   Updated: 2022/04/21 16:53:24 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FUNCS_H
# define LIBFT_FUNCS_H

# include <stdlib.h>
# include "shell.h"
# include "hashtable.h"

// utils2.c
int		is_alpha(char c);
int		is_numeric(char c);
int		is_alnum(char c);
int		is_space(char c);
int		int32_abs(int n);

// utils3.c
char	*ft_strcpy(char *dest, char *src);
int		ft_strlen(char *str);
char	*ft_strdup(char *str);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memmove(void *dst, const void *src, size_t len);

// utils4.c
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(char *str);
char	*ft_itoa(int n);

// ft_split.c
char	**ft_split(char const *s, char c);
int		free_2d_array(char **arr);

// utils.c
char	**hashtable_to_array(t_hashtable *ht);
int		length_hashtable(t_hashtable *ht);
char	*three_str_cat(char *s1, char *s2, char *s3);
int		is_variable_valid(char *str);

#endif
