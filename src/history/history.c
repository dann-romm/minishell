/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 02:29:57 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/21 02:29:58 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft_funcs.h"

void	ft_add_history(char *str)
{
	char	*tmp;

	if (!str || !(*str))
		return ;
	tmp = str;
	while (*tmp)
	{
		if (!is_space(*tmp++))
		{
			add_history((const char *)str);
			return ;
		}
	}
}
