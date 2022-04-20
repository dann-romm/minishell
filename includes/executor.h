/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:24:44 by mgwyness          #+#    #+#             */
/*   Updated: 2022/04/21 02:42:40 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "shell.h"

// executor.c
int				execute(t_cmd_block *cmd_block);

// executor_data.c
t_pipex_data	*init_pipex_data(t_command_table *table);

// executor_utils.c
int				ft_dup2(t_command_table *table, t_pipex_data *data, int index);
int				ft_wait(t_pipex_data *data);

// exec_bin.c
void			exec_bin(t_command_table *table, t_pipex_data *data, int index);

#endif
