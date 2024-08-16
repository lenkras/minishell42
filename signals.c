/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-17 14:46:51 by epolkhov          #+#    #+#             */
/*   Updated: 2024-07-17 14:46:51 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal_status = 1;
	}
}

static void	hd_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
		g_signal_status = 1;
	}
}

static void	toggle_caret(int is_on)
{
	struct termios	new_attr;

	if (tcgetattr(STDIN_FILENO, &new_attr) == -1)
	{
		perror("tcgetattr in signals failed");
		exit(1);
	}
	if (!is_on)
		new_attr.c_lflag &= ~ECHOCTL;
	else
		new_attr.c_lflag |= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_attr) == -1)
	{
		perror ("tcsetattr in signals failed");
		exit (1);
	}
}

static void	set_signal_handler(int signum, void (*handler)(int))
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(signum, &sa, NULL) == -1)
	{
		perror("Sigaction failed");
		exit (1);
	}
}

void	get_signal(t_signal mode)
{
	if (mode == DEFAULT)
	{
		toggle_caret(1);
		set_signal_handler(SIGQUIT, SIG_DFL);
		set_signal_handler(SIGINT, SIG_DFL);
	}
	else if (mode == HANDLER)
	{
		toggle_caret(0);
		set_signal_handler(SIGQUIT, SIG_IGN);
		set_signal_handler(SIGINT, signal_handler);
	}
	else if (mode == HEREDOC)
	{
		set_signal_handler(SIGQUIT, SIG_IGN);
		set_signal_handler(SIGINT, hd_handler);
	}
	else if (mode == NO_SIGNALS)
	{
		set_signal_handler(SIGQUIT, SIG_IGN);
		set_signal_handler(SIGINT, SIG_IGN);
	}
}
