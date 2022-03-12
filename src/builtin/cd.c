#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"

void	upd_pwd(char *path)
{
	insert_hashtable(g_shell->env_global, "OLDPWD", find_hashtable(g_shell->env_global, "PWD"));
	insert_hashtable(g_shell->env_global, "PWD", path);
}

void	change_dir(t_simple_cmd *cd)
{
	if (chdir(cd->cmd_args[0])) //chdir() gets an absolute path
	{
		printf("path is: %s\n", cd->cmd_args[0]);
		if (access(cd->cmd_args[0], F_OK) == -1)
			printf("minishell: cd: %s: no such file or directory\n", cd->cmd_args[0]);
		else if (access(cd->cmd_args[0], R_OK) == -1)
			printf("minishell: cd: %s: permission denied\n", cd->cmd_args[0]);
		else
			printf("minishell: cd: %s: not a directory\n", cd->cmd_args[0]);
	}
	upd_pwd(cd->cmd_args[0]);
}

int	ft_cd(t_simple_cmd *cd)
{
	if (!cd->args_num || !ft_strcmp(cd->cmd_args[0], ".."))
	{
		const char	*path = getenv("HOME");
		chdir(path);
		upd_pwd((char *)path);
	}
	else if (!cd->args_num || !ft_strcmp(cd->cmd_args[0], "-"))
	{
		chdir(find_hashtable(g_shell->env_global, "OLDPWD"));
		upd_pwd(find_hashtable(g_shell->env_global, "OLDPWD"));
	}
	else
		change_dir(cd);
	return (0);
}
