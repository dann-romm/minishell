#ifndef BUILTIN_H
# define BUILTIN_H

int		ft_cd(t_simple_cmd *cd);
int		ft_echo(t_simple_cmd *command);
int		ft_env(void);
int		ft_exit(char **cmd_args, int args_num);
int		ft_export(t_simple_cmd *cd);
int		ft_pwd(void);
int		ft_unset(t_simple_cmd *unset_cmd);
int		ft_assignment(t_simple_cmd *cmd);

#endif
