/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 21:17:37 by mgwyness          #+#    #+#             */
/*   Updated: 2022/04/20 22:30:05 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "hashtable.h"

int	ft_pwd(void)
{
	char	*cur_dir;

	cur_dir = NULL;
	cur_dir = getcwd(cur_dir, PATH_MAX);
	if (!cur_dir)
		return (errno);
	printf("%s\n", cur_dir);
	free(cur_dir);
	return (0);
}
