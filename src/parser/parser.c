/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:28:57 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/19 17:41:42 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parser(t_shell *shell)
{
	group_redir(shell);
}

void group_redir(t_shell *shell)
{
	t_expand	*current;
	char		**io;
	int			file_num;

	current = shell->expand;
	if (!current)
		return ;
	io = (char **)ft_calloc((5), sizeof(char *));
	file_num = 0;
	while (current->next != NULL)
	{
		if (current->token != T_WORD && (current->next->token != T_WORD || current->next == NULL))
			free_err(ERR_SYNTAX, shell);
		if (current->token != T_WORD && current->next->token == T_WORD)
		{
			if (current->token == T_PIPE)
				break ;
			else if (current->token == T_LESSER || current->token == T_HEREDOC)
				io = pop_io(io, current->word, current->next->word, current->token);
			else if (current->token == T_GREATER || current->token == T_APPEND)
			{
				io = pop_io(io, current->word, current->next->word, current->token);
				file_num++;
			}
		}
		io[4] = NULL;
		current = current->next;
	}
	if (current->token != T_WORD && current->token != T_PIPE)
			free_err(ERR_SYNTAX, shell);
	group_files(shell, io, file_num);
}

void group_files(t_shell *shell, char **io, int file_num)
{
	t_expand	*current;
	char		**files;

	current = shell->expand;
	if (!current)
		return ;
	files = (char **)ft_calloc((file_num + 1), sizeof(char *));
	file_num = 0;
	while (current->next != NULL)
	{
		if (current->token != T_WORD && current->next->token == T_WORD)
		{
			if (current->token == T_PIPE)
				break ;	
			else if (current->token == T_GREATER || current->token == T_APPEND)
			{
				files[file_num] = ft_strdup(current->next->word);
				file_num++;
			}
		}
		if (current->next == NULL)
			break ;
		current = current->next;
	}
	while(file_num > 0)
	{
		printf("files[%d]: %s\n", file_num, files[file_num - 1]);
		file_num--;
	}
	purge_redir(shell);
	group_args(shell, io, files);
}

void	group_args(t_shell *shell, char **io, char **files)
{
	t_expand	*current;
	char **args;
	
	printf("io[0]: %s\n", io[0]);
	printf("io[1]: %s\n", io[1]);
	printf("io[2]: %s\n", io[2]);
	printf("io[3]: %s\n", io[3]);
	printf("io[4]: %s\n", io[4]);
	print_expand(shell);
	free_double(io);
	free_double(files);
}
