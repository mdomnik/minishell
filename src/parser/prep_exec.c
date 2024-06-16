/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:24:28 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/16 14:36:59 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void prep_exec(t_shell *shell)
{
	char	**token;

	while (shell->parser != NULL)
	{
		token = ft_strjoin_ms(shell, shell->parser->args);
		
		shell->parser = shell->parser->next;
	}
	print_parser(shell);
	
}