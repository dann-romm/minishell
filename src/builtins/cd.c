#include "shell.h"

void	upd_pwd(t_hashtable *ht, char *path)
{
	insert_hashtable(ht, "OLDPWD", find_hashtable(ht, "PWD"));
	insert_hashtable(ht, "PWD", path);
}

void	change_dir(t_simple_cmd *cd, t_hashtable *ht)
{
	if (chdir(cd->cmd_args[0])) //chdir() gets an absolute path
	{
		if (access(cd->cmd_args[0], F_OK) == -1)
			printf("minishell: cd: %s: no such file or directory\n", cd->cmd_args[0]);
		else if (access(cd->cmd_args[0], R_OK) == -1)
			printf("minishell: cd: %s: permission denied\n", cd->cmd_args[0]);
		else
			printf("minishell: cd: %s: not a directory\n", cd->cmd_args[0]);
	}
	upd_pwd(ht, cd->cmd_args[0]);
}

int	ft_cd(t_hashtable *ht, t_simple_cmd *cd)
{
	if (!cd->args_num)
	{
		const char	*path = getenv("HOME");
		chdir(path);
		upd_pwd(ht, path);
	}
	else
		change_dir(cd, ht);
	return (0);
}
