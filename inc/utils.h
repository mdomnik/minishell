/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:12:05 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/25 22:38:04 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

//prototyping shell struct
typedef struct s_shell	t_shell;

//gen_utils_1.c
char	**double_dup(char **str);
void	free_double(char **double_str);
int		ft_strlen_ms(char *s);
char	**add_delim_split(char *str, t_shell *shell);
char	*ft_strjoin_ms(char *s1, char *s2);

//gen_utils_2.c
int		cmp_str(char *s1, const char *s2);
int		count_args(char **args);

//gen_utils_split.c
char	**ft_split_ms(const char *s, char c);

#endif