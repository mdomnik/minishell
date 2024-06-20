/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:54:57 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/20 16:42:56 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

//prototyping prompt struct
typedef struct s_shell	t_shell;

//execution.c
void	execution(t_shell *shell);
bool	is_valid_id(char *token);
bool	redir_check(t_exec *exec);
bool	pipe_check(t_exec *exec);
void	find_path(t_shell *shell, t_exec *exec);
int		find_builtin(t_shell *shell, t_exec *exec);

//pipe & redirection
void	exec_cmd(t_shell *shell, t_exec *exec);
void	pipe_exe(t_shell *shell, t_exec *exec);
void	redir_exe(t_shell *shell, t_exec *exec);
void	less_nofile_exit(void);
void	less_multi_file(t_exec *exec, int fd);
void	less_one_file(t_exec *exec, int fd);
void	less_invalid_input(char *token);

#endif
