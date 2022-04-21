/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 11:47:27 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/21 18:41:06 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gshell.h"
#include "shell.h"
#include "libft_funcs.h"

static char	**adapt_cmd_args(t_simple_cmd *command)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	new = (char **)malloc(sizeof(char *) * (command->args_num + 2));
	if (new == 0)
		return (0);
	new[i++] = ft_strdup(command->cmd);
	while (i <= command->args_num)
		new[i++] = ft_strdup(command->cmd_args[j++]);
	new[i] = 0;
	return (new);
}

static char	*find_path(t_simple_cmd *command)
{
	int		i;
	char	*cur_dir;
	char	**paths;

	cur_dir = find_hashtable(g_shell.env_global, "PWD");
	cur_dir = three_str_cat(cur_dir, "/", command->cmd);
	if (!access(cur_dir, F_OK))
		return (cur_dir);
	free(cur_dir);
	paths = ft_split(find_hashtable(g_shell.env_global, "PATH"), ':');
	i = -1;
	while (paths[++i])
	{
		cur_dir = three_str_cat(paths[i], "/", command->cmd);
		if (!access(cur_dir, F_OK))
		{
			free_2d_array(paths);
			return (cur_dir);
		}
		free(cur_dir);
	}
	free_2d_array(paths);
	error_manager(ERRT_NOT_FOUND, command->cmd, -42);
	return (0);
}

void	exec_bin(t_command_table *table, t_pipex_data *data, int index)
{
	char	*path;
	char	**args;
	char	**env;

	close(data->tube1[0]);
	close(data->tube1[1]);
	close(data->tube2[0]);
	close(data->tube2[1]);
	path = find_path(table->commands[index]);
	if (!path)
		exit(127);
	args = adapt_cmd_args(table->commands[index]);
	env = hashtable_to_array(g_shell.env_global);
	execve(path, args, env);
	exit(errno);
}
