/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgwyness <mgwyness@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:38:23 by mgwyness          #+#    #+#             */
/*   Updated: 2022/04/20 22:38:24 by mgwyness         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "shell.h"

void	signal_handler(int signum);
void	heredoc_signal_handler(int signum);
void	setting_signal(void);

#endif
