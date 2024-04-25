/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:00:52 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/25 18:39:08 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

//prototyping prompt struct
typedef struct s_shell	t_shell;

//env.c
void	builtin_env(t_shell *shell);

//pwd.c
void	builtin_pwd(t_shell *shell);

//exit.c
void	builtin_exit(t_shell *shell);

#endif