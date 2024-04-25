/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 01:08:04 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/26 01:36:24 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	builtin_export(t_shell *shell)
{
	char	*envtmp;
	int		i;
	
	i = 0;
	while (shell->parser->args[i])
	{
		if (ft_strchr(shell->parser->args[i], '='))
			export_env(shell, i);
		else
			break ;
		i++;
	}
	envtmp = ft_strdup(shell->parser->args[1]);
	shell->env = double_join(, shell);
}
