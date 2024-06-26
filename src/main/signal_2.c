/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:35:42 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/26 12:36:15 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sigquit_handler(int num)
{
	(void)num;
}

void	sigint_handler_child(int num)
{
	(void)num;
	exit(0);
}

void	set_signals_child(void)
{
	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, sigquit_handler);
}
