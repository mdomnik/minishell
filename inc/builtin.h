/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:00:52 by mdomnik           #+#    #+#             */
/*   Updated: 2024/05/06 17:03:55 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

//prototyping prompt struct
typedef struct s_shell	t_shell;

//cd.c
void	builtin_cd(t_shell *shell);

//echo.c
void	builtin_echo(t_shell *shell);
int		check_echo_option(char **args, int **n_flag, int i);
int		find_if_n(char *str);

//env.c
void	builtin_env(t_shell *shell);

//exit.c
void	builtin_exit(t_shell *shell);

//export.c
void	builtin_export(t_shell *shell);
void	update_env_declare(t_shell *shell);
int		valid_format(char *str);
void	add_declare(t_shell *shell, char *str, int var);
void	add_env(t_shell *shell, char *str);

//pwd.c
void	builtin_pwd(t_shell *shell);

//unset.c
void	builtin_unset(t_shell *shell);
void	unset_declare(t_shell *shell, char *str);
void	unset_env(t_shell *shell, char *str);

#endif