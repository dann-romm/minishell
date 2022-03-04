#include "shell.h"

// TODO:
// when you get a copy of env, change PWD and OLDPWD to be able
// to change the state of the whole minishell, not just a single process
// firstly change OLDPATH just copying PWD
// 1. upd_oldpwd()
// 2. upd_pwd()


void	upd_oldpwd(char **env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd_upd;
	getcwd(cwd, PATH_MAX);
	oldpwd_upd = ft_strjoin("OLDPWD=", cwd);
}

void	upd_pwd(char **env)
{
	///
}

void	change_dir(t_command_table *cmd_table)
{
	t_simple_cmd *cmd1 = cmd_table->commands[0];
	//char	abs_path[PATH_MAX];
	//getcwd(abs_path, PATH_MAX);
	//printf("%s\n", abs_path);
	if (chdir(cmd1->cmd_args[0])) //chdir() gets an absolute path
	{
		ft_putstr("cd: ");
		if (access(cmd1->cmd_args[0], F_OK) == -1)
			ft_putstr("no such file or directory: ");
		else if (access(cmd1->cmd_args[0], R_OK) == -1)
			ft_putstr("permission denied: ");
		else
			ft_putstr("not a directory: ");
		ft_putendl(cmd1->cmd_args[0]);
	}
	upd_oldpwd(cmd_table->env); // not written yet
	upd_pwd(cmd_table->env); // not written yet
}

int	cd_builtin(t_command_table *cmd_table)
{
	t_simple_cmd *cmd1 = cmd_table->commands[0];
	if (!cmd1->args_num)
	{
		const char	*path = getenv("HOME");
		chdir(path);
		upd_oldpwd(cmd_table->env); // not written yet
		upd_pwd(cmd_table->env); // upd_pwd() not written yet
	}
	else
		change_dir(cmd_table);
	return (0);
}

int main()
{
	t_command_table *cmd_table;
	int i = 0;
	cmd_table = (t_command_table *)malloc(sizeof(t_command_table));
	cmd_table->commands_num = 1;
	cmd_table->commands = (t_simple_cmd **)malloc(sizeof(t_simple_cmd *) * cmd_table->commands_num);
	while (i < cmd_table->commands_num)
	{
		cmd_table->commands[i] = malloc(sizeof(t_simple_cmd));
		i++;
	}
	t_simple_cmd *cmd1 = cmd_table->commands[0];
	cmd1->cmd = ft_strdup("cd");
	cmd1->args_num = 1;
	cmd1->cmd_args = malloc(sizeof(char *) * 1);
	cmd1->cmd_args[0] = ft_strdup("Desktop");
	cd_builtin(cmd_table);
}