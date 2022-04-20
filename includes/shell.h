/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:37:10 by mgwyness          #+#    #+#             */
/*   Updated: 2022/04/20 23:32:12 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# define PATH_MAX 4096
# define ERRCHAR 0
# define ESCCHAR '\\'
# define HEREDOC_FILENAME ".minishell_heredoc"

// errno
# include <errno.h>
// printf
# include <stdio.h>
// readline rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay, add_history
# include "readline/readline.h"
# include "readline/history.h"
// malloc, free, exit, getenv
# include <stdlib.h>
// write, access, read, close, fork, getcwd, chdir, unlink, 
// execve, dup, dup2, pipe, isatty, ttyname, ttyslot, 
# include <unistd.h>
// open
# include <fcntl.h>
// wait, waitpid, wait3, wait4
# include <sys/wait.h>
// signal, sigaction, kill
# include <signal.h>
// stat, lstat, fstat
# include <sys/stat.h>
// opendir, readdir, closedir
# include <dirent.h>
// strerror
# include <string.h>
// ioctl
# include <sys/ioctl.h>
// tcsetattr, tcgetattr,
# include <termios.h>
// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <term.h>

# include "hashtable.h"

typedef enum e_cmd_type
{
	CMD_NONE = -1,
	CMD_CD = 0,
	CMD_PWD,
	CMD_ECHO,
	CMD_EXPORT,
	CMD_EXIT,
	CMD_UNSET,
	CMD_ENV,
	CMD_ASSIGNMENT
}	t_cmd_type;

typedef struct s_simple_cmd
{
	char		*cmd;
	int32_t		args_num;
	char		**cmd_args;
	t_cmd_type	type;
}	t_simple_cmd;

typedef struct s_redirect
{
	char	*_stdin;
	char	*_stdout;
	int		is_stdin_append;
	int		is_stdout_append;
}	t_redirect;

typedef struct s_command_table
{
	int32_t			commands_num;
	t_simple_cmd	**commands;
	t_redirect		redirect;
}	t_command_table;

typedef struct s_shell
{
	t_hashtable	*env_global;
	t_hashtable	*env_local;
	int32_t		exit_status;
}	t_shell;

typedef enum e_cmd_block_delimiter
{
	CMDBL_END,
	CMDBL_AND,
	CMDBL_OR,
	CMDBL_SEMI
}	t_cmd_block_delimiter;

typedef struct s_cmd_block
{
	t_command_table			*table;
	t_cmd_block_delimiter	delimiter;
}	t_cmd_block;

typedef enum e_error_type
{
	ERRT_SYNTAX,
	ERRT_NOT_FOUND,
	ERRT_EXPORT_ERR,
	ERRT_UNSET_ERR,
	ERRT_PWD_ERR,
	ERRT_CD_ERR,
	ERRT_NUM_ARG,
	ERRT_MANY_ARG,
	ERRT_ERRNO_ERR,
	ERRT_UNSUPPORTED
}	t_error_type;

typedef struct s_pipex_data
{
	int		fd1;
	int		fd2;
	int		_saved_stdin;
	int		_saved_stdout;
	int		tube1[2];
	int		tube2[2];
	int		count_running_cmds;
	int		is_heredoc;
}		t_pipex_data;

t_shell	*g_shell;

// error_managment.c
int		error_manager(t_error_type type, const char *msg, int error_code);

#endif
