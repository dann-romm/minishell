#include "shell.h"
#include "libft_funcs.h"

static char	*three_str_cat(char *s1, char *s2, char *s3)
{
	int		len;
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	while (s1[i] && i < (len + 1))
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j] && i < (len + 1))
		dest[i++] = s2[j++];
	j = 0;
	while (s3[j] && i < (len + 1))
		dest[i++] = s3[j++];
	dest[i] = '\0';
	return (dest);
}

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
	int		all;
	char	*cur_dir;
	char	**paths;

	cur_dir = find_hashtable(g_shell->env_global, "PWD");
	cur_dir = three_str_cat(cur_dir, "/", command->cmd);
	if (!access(cur_dir, F_OK))
		return (cur_dir);
	free(cur_dir);
	paths = ft_split(find_hashtable(g_shell->env_global, "PATH"), ':');
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
	env = hashtable_to_array(g_shell->env_global);
	execve(path, args, env);
	exit(errno);
}
