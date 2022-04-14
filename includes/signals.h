#ifndef SIGNAL_H
# define SIGNAL_H

# include "shell.h"

void	signal_handler(int signum);
void	heredoc_signal_handler(int signum);
void	setting_signal();

#endif
