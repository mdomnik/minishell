/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:54:57 by mdomnik           #+#    #+#             */
/*   Updated: 2024/05/29 20:51:22 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

//prototyping prompt struct
typedef struct s_shell	t_shell;

//execution.c
void	execute(t_shell *shell);
int find_builtin(t_shell *shell);

//pathexec.c
char	**prep_path(t_shell *shell);
int		find_path(t_shell *shell);
void	exec_external(t_shell *shell, char *path);

//pipe.c
void 	pipex(t_shell *shell);
void	operator_exe(t_shell *shell);

#endif