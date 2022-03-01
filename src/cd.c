#include "shell.h"

void	back_to_root(char *path)
{
	const char	*abs_path = getenv(path);
	if (chdir(abs_path))
	{
		ft_putstr("cd: ");
		if (access(path, F_OK) == -1)
			ft_putstr("no such file or directory: ");
		else if (access(path, R_OK) == -1)
			ft_putstr("permission denied: ");
		else
			ft_putstr("not a directory: ");
		ft_putendl(path);
	}
}

void	upd_oldpwd(char **env)
{
	char	*cwd[PATH_MAX];
	char	*oldpwd_upd;
	getcwd(cwd, PATH_MAX);
	oldpwd_upd = ft_strjoin("OLDPWD=", cwd);
	add_env_var(oldpwd_upd, env); // not written yet
}

void	change_dir(char **args)
{
	const char	*abs_path = getenv(path);
	if (chdir(abs_path))
	{
		ft_putstr("cd: ");
		if (access(path, F_OK) == -1)
			ft_putstr("no such file or directory: ");
		else if (access(path, R_OK) == -1)
			ft_putstr("permission denied: ");
		else
			ft_putstr("not a directory: ");
		ft_putendl(path);
	}
}

int	cd_builtin(char **args, char **env)
{
	if (args[1])
		back_to_root("HOME");
	else
		change_dir(args[1]);
	upd_oldpwd(env);
	return (0);
}

int main()
{
	t_command_table *cmd_table;
	int i = 0;
	cmd_table = (t_command_table *)malloc(sizeof(t_command_table));
	cmd_table->commands = malloc(sizeof(t_simple_cmd));
	while (i < cmd_table->commands_num)
	{
		cmd_table->commands[i] = malloc(sizeof(t_simple_cmd));
		i++;
	}
	t_simple_cmd *cmd1;
	cmd1->cmd = malloc(sizeof(char) * ft_strlen(cmd1->cmd) + 1);
	int j = 0;
	cmd1->cmd_args = malloc(sizeof(char *));
	while (j < cmd1->args_num)
	{
		cmd1->cmd_args[j] = malloc(sizeof(char) * ft_strlen())
	}
}