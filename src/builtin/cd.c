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
	if (chdir(cd->cmd_args[0]))
	{
		if (access(cd->cmd_args[0], F_OK) == -1)
		{
			errno = 2;
			errno = error_manager(ERRT_CD_ERR, cd->cmd_args[0], 1);
			return (1);
		}
		else if (access(cd->cmd_args[0], R_OK) == -1)
		{
			errno = 13;
			errno = error_manager(ERRT_CD_ERR, cd->cmd_args[0], 1);
			return (1);
		}
		else
		{
			errno = 20;
			errno = error_manager(ERRT_CD_ERR, cd->cmd_args[0], 1);
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
	const char	*path = getenv("HOME");

	if (!cd->args_num)
	{
		chdir(path);
		upd_pwd((char *)path);
	}
	else
		return (change_dir(cd));
	return (0);
}
