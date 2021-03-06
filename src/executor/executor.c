/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgwyness <mgwyness@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:40:55 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/22 20:29:19 by mgwyness         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gshell.h"
#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"
#include "builtin.h"
#include "signals.h"
#include "executor.h"

static int	exec_builtin(t_command_table *table, t_pipex_data *data, int index)
{
	(void) data;
	if (table->commands[index]->type == CMD_CD)
		return (ft_cd(table->commands[index]));
	else if (table->commands[index]->type == CMD_EXPORT)
		return (ft_export(table->commands[index]));
	else if (table->commands[index]->type == CMD_UNSET)
		return (ft_unset(table->commands[index]));
	else if (table->commands[index]->type == CMD_EXIT)
		return (ft_exit(table->commands[index]->cmd_args,
				table->commands[index]->args_num));
	else if (table->commands[index]->type == CMD_ASSIGNMENT)
		return (ft_assignment(table->commands[index]));
	else if (table->commands_num == 1)
		return (-1);
	if (table->commands[index]->type == CMD_PWD)
		return (ft_pwd());
	else if (table->commands[index]->type == CMD_ECHO)
		return (ft_echo(table->commands[index]));
	else if (table->commands[index]->type == CMD_ENV)
		return (ft_env());
	return (-1);
}

static int	exec_cmd(t_command_table *table, t_pipex_data *data, int index)
{
	pid_t	pid;

	if (ft_dup2(table, data, index))
		return (errno);
	data->count_running_cmds++;
	pid = fork();
	if (pid == -1)
		return (error_manager(ERRT_ERRNO_ERR, "fork", errno));
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (exec_builtin(table, data, index) == -1)
			exec_bin(table, data, index);
		free(data);
		exit(errno + delete_shell());
	}
	else
	{
		dup2(data->_saved_stdin, STDIN_FILENO);
		dup2(data->_saved_stdout, STDOUT_FILENO);
		close(data->_saved_stdin);
		close(data->_saved_stdout);
	}
	return (errno);
}

static int	run_cmd_block(t_command_table *table)
{
	t_pipex_data	*data;
	int				i;

	data = init_pipex_data(table);
	if (!data || table->commands_num == 0
		|| (table->commands_num == 1 && exec_builtin(table, data, 0) != -1))
	{
		free(data);
		return (errno);
	}
	if (pipe(data->tube1) < 0)
		return (error_manager(ERRT_ERRNO_ERR, "pipe", 1));
	i = -1;
	while (++i < table->commands_num)
	{
		if (pipe(data->tube2) < 0)
			return (error_manager(ERRT_ERRNO_ERR, "pipe", 1));
		exec_cmd(table, data, i);
		close(data->tube1[0]);
		close(data->tube1[1]);
		data->tube1[0] = data->tube2[0];
		data->tube1[1] = data->tube2[1];
	}
	close(data->tube2[0] + (close(data->tube2[1]) == -42));
	return (ft_wait(data));
}

int	execute(t_cmd_block *cmd_blocks)
{
	int	i;
	int	status;

	i = 0;
	setting_signal();
	status = run_cmd_block(cmd_blocks[i].table);
	while (cmd_blocks[i].delimiter != CMDBL_END)
	{
		if (cmd_blocks[i].delimiter == CMDBL_AND)
		{
			++i;
			if (!status)
				status = run_cmd_block(cmd_blocks[i].table);
		}
		else if (cmd_blocks[i].delimiter == CMDBL_OR)
		{
			++i;
			if (status)
				status = run_cmd_block(cmd_blocks[i].table);
		}
		else
			status = run_cmd_block(cmd_blocks[++i].table);
	}
	return (status);
}
