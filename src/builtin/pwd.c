/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 21:17:37 by mgwyness          #+#    #+#             */
/*   Updated: 2022/04/20 22:04:58 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "hashtable.h"

int	ft_pwd(void)
{
	char	*cur_dir;

	cur_dir = (char *)malloc(sizeof(char) * 999);
	if (!cur_dir)
		return (1);
	cur_dir = getcwd(cur_dir, 999);
	printf("%s\n", cur_dir);
	free(cur_dir);
	return (0);
}
