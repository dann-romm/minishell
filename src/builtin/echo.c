/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:02:02 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/20 22:02:04 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft_funcs.h"

int	ft_echo(t_simple_cmd *command)
{
	int	flag;
	int	i;

	flag = 0;
	i = -1;
	if (!command->args_num)
	{
		printf("\n");
		return (0);
	}
	else if (!ft_strcmp(command->cmd_args[0], "-n"))
	{
		flag = 1;
		i = 0;
	}
	while (++i < command->args_num)
	{
		printf("%s", command->cmd_args[i]);
		if (i < command->args_num - 1)
			printf(" ");
	}
	if (!flag)
		printf("\n");
	return (0);
}
