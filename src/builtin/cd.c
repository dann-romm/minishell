#include "shell.h"
#include "hashtable.h"
#include "builtin.h"
#include "libft_funcs.h"

void	upd_pwd(char *path)
{
	insert_hashtable(g_shell->env_global, "OLDPWD", find_hashtable(g_shell->env_global, "PWD"));
	insert_hashtable(g_shell->env_global, "PWD", path);
}

int	change_dir(t_simple_cmd *cd)
{
	char *cur_dir;

	cur_dir = (char *)malloc(sizeof(PATH_MAX));
	if (!ft_strcmp(cd->cmd_args[0], "~"))
		cd->cmd_args[0] = ft_strjoin(getenv("HOME"), &(cd->cmd_args[0][1]));
	if (chdir(cd->cmd_args[0]))
	{
		if (access(cd->cmd_args[0], F_OK) == -1)
		{
			printf("minishell: cd: %s: no such file or directory\n", cd->cmd_args[0]);
			return (1);
		}
		else if (access(cd->cmd_args[0], R_OK) == -1)
		{
			printf("minishell: cd: %s: permission denied\n", cd->cmd_args[0]);
			return (1);
		}
		else
		{
			printf("minishell: cd: %s: not a directory\n", cd->cmd_args[0]);
			return (1);
		}
	}
	char *tmp = (char *)malloc(sizeof(char) * PATH_MAX);
	tmp = getcwd(tmp, PATH_MAX);
	upd_pwd(tmp);
	free(tmp);
	free(cur_dir);
	return (0);
}

int	ft_cd(t_simple_cmd *cd)
{
	if (!cd->args_num)
	{
		const char	*path = getenv("HOME");
		chdir(path);
		upd_pwd((char *)path);
		// print_hashtable(g_shell->env_global);
	}
	else
		return (change_dir(cd));
	return (0);
}
