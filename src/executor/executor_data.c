/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:00:43 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/20 23:38:53 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "prompt.h"
#include "libft_funcs.h"

// if there is a heredoc, writes input into HEREDOC_FILENAME file
// and fills t_command_table fields
static void	handle_heredoc(t_command_table *table, t_pipex_data *data)
{
	const char	*limiter = table->redirect._stdin;
	int			fd;
	char		*str;

	data->is_heredoc = 0;
	if (!limiter || table->redirect.is_stdin_append == 0)
		return ;
	fd = open(HEREDOC_FILENAME, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return ;
	table->redirect._stdin = ft_strdup(HEREDOC_FILENAME);
	str = prompt2();
	while (str && ft_strcmp(str, (char *)limiter))
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = prompt2();
	}
	if (str)
		free(str);
	close(fd);
	data->is_heredoc = 1;
}

static void	open_files(t_command_table *table, t_pipex_data *data)
{
	if (table->redirect._stdin != 0)
		data->fd1 = open(table->redirect._stdin, O_RDONLY);
	else
		data->fd1 = STDIN_FILENO;
	if (table->redirect._stdout != 0)
	{
		if (table->redirect.is_stdout_append)
			data->fd2 = open(table->redirect._stdout,
					O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			data->fd2 = open(table->redirect._stdout,
					O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	else
		data->fd2 = STDOUT_FILENO;
	if (data->fd1 < 0)
		error_manager(ERRT_ERRNO_ERR, table->redirect._stdin, -42);
	if (data->fd2 < 0)
		error_manager(ERRT_ERRNO_ERR, table->redirect._stdout, -42);
}

t_pipex_data	*init_pipex_data(t_command_table *table)
{
	t_pipex_data	*data;

	data = (t_pipex_data *)malloc(sizeof(t_pipex_data));
	if (!data)
		return (0);
	data->count_running_cmds = 0;
	data->_saved_stdin = -1;
	data->_saved_stdout = -1;
	data->tube1[0] = -1;
	data->tube1[1] = -1;
	data->tube2[0] = -1;
	data->tube2[1] = -1;
	handle_heredoc(table, data);
	data->count_running_cmds = 0;
	open_files(table, data);
	if (errno)
	{
		free(data);
		return (0);
	}
	return (data);
}
