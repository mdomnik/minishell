/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:11:27 by kaan              #+#    #+#             */
/*   Updated: 2024/06/26 12:35:26 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Handles signals received by child processes.
 *
 * @param signum The signal number received.
 */
void	child_signals(int signum)
{
	if (signum == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

/**
 * @brief Dismisses the signal handler for a specific signal.
 *
 * This function is called when the specified signal is received.
 * It handles the SIGINT signal
 * by printing a newline character, moving the cursor to a new line,
 * replacing the current line
 * with an empty string, and redisplaying the prompt.
 *
 * @param signum The signal number.
 */
void	dismiss_signal(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/**
 * Configures the signal handlers for the program.
 * The function sets up the signal handler for SIGINT
 * to call the `dismiss_signal` function.
 * It also ignores the SIGQUIT signal.
 */
void	config_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &dismiss_signal;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
