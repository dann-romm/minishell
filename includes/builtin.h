#ifndef BUILTIN_H
# define BUILTIN_H

int		ft_cd(t_hashtable *ht, t_simple_cmd *cd);
void	ft_echo(char **args, int arg_num);
void	ft_env(t_hashtable *ht);
int		ft_exit(char **cmd_args, int args_num);
void	ft_export(t_hashtable *ht, char **args);
void	ft_pwd(t_hashtable *ht);
void	ft_unset(t_hashtable *ht, t_simple_cmd *unset_cmd);

#endif
