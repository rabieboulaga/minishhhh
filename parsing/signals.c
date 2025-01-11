/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 21:53:49 by htemsama          #+#    #+#             */
/*   Updated: 2025/01/11 23:33:07 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	handle_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
	g_global.exited = 130;
	exit(130);
}

void	handle_signals(int sig)
{
	if (sig == IN_HEREDOC)
	{
		signal(SIGINT, handle_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == IN_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	if (sig == IN_PARENT)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, handle_quit);
		g_global.exited = 130;
	}
	if (sig == BEFORE_READLINE)
	{
		signal(SIGINT, handle_interrupt);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	sig_handler(int signum)
{
	(void)signum;
	if (!g_global.executed)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global.exited = 1;
	}
}

void	handle_quit(int signum)
{
	(void)signum;
	if (!g_global.executed)
	{
		signal(SIGQUIT, SIG_IGN);
	}
	if (g_global.executed != 0)
	{
		if (g_global.in_herdoc == 0)
		{
			ft_putstr_fd("Quit (core dumped)\n", 2);
		}
	}
}

void	default_signal(void)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR || signal(SIGQUIT,
			handle_quit) == SIG_ERR)
	{
		g_global.exited = 130;
	}
}
