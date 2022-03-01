#include "shell.h"

void	add_env_var(char *var, char **env) // env
{
	///
}

void	env_init(char **args, char **env)
{
	t_env	*my_env;
	t_env	*new;
	int		i;

	my_env = (t_env *)malloc(sizeof(t_env));
	if (my_env == 0)
		return (1);
	my_env->name = ft_strdup(env[0]);
	my_env->next = 0;
	i = 1;
	while (env && env[0] && env[i])
	{
		new = (t_env *)malloc(sizeof(t_env));
		if (new == 0)
			return (1);
		new->name = env[i];
		new->next = 0;
		my_env->next = new;
		my_env = new;
		i++;
	}
}
