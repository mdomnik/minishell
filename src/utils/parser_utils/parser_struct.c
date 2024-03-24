/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:41:38 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/24 16:54:11 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_parser *parsernew_ms(char **args, char **io, char **files)
{
	t_parser		*element;

	element = (t_parser *)malloc(sizeof(t_parser));
	if (!element)
		return (NULL);
	element->index = (reset_increment_j(1) - 1);
	
	element->cmd = ft_strdup(args[0]);
	element->args = remove_first(args);

	if (io[0] == NULL)
	{
		if (element->index == 0)
			element->input = I_STDIN;
		else
			element->input = I_PIPE;
		element->i_str = NULL;
	}
	else
	{
		element->input = find_redir(io[0]);
		element->i_str = ft_strdup(io[1]);
	}
	if (io[2] == NULL)
	{
		element->output = 0;
		element->o_str = NULL;
	}
	else
	{
		element->output = find_redir(io[2]);
		element->o_str = ft_strdup(io[3]);
	}

	element->files = files;


	element->prev = NULL;
	element->next = NULL;

	printf("---------------------\n\n");
	int i = 0;
	
	printf("cmd: [%s] \n", element->cmd);
	printf("args: ");
	while (element->args[i] != NULL)
	{
		printf("[%s] ", element->args[i]);
		i++;
	}
	printf("\n");
	printf("input: [%d], ", element->input);
	printf("i_str: [%s]\n", element->i_str);
	printf("output: [%d], ", element->output);
	printf("o_str: [%s]\n", element->o_str);
	i = 0;
	while (element->files[i] != NULL)
	{
		printf("file %d:[%s], ", i, element->files[i]);
		i++;
	}
	printf("\n");
	printf("index: %d\n", element->index);
	return (element);
}

int	reset_increment_j(int x)
{
	static int j = 0;
	if (x == 0)
		j = 0;
	else
		j++;
	return (j);
}

//adds new node to the back of the parser linked list
void	parseraddback_ms(t_parser **lst, t_parser *new)
{
	t_parser		*temp;

	temp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;	
}

// //frees the parser linked list
// t_parser *lexerfreelist_ms(t_parser **lst)
// {
// 	t_parser *temp;

// 	temp = *lst;
// 	if (!(*lst))
// 		return (NULL);
// 	while (*lst)
// 	{
// 		temp = (*lst)->next;
// 		if ((*lst)->word)
// 			free ((*lst)->word);
// 		free(*lst);
// 		*lst = temp;
// 	}
// 	*lst = NULL;
// 	return (NULL);
// }

// void delete_node_at_index(t_lexer **lexer, int index)
// {
// 	t_lexer *current = *lexer;

// 	if (*lexer == NULL)
// 	{
// 		printf("List is empty. Cannot delete.\n");
// 		return;
// 	}
// 	if (index == 0)
// 	{
// 		*lexer = current->next;
// 		if (*lexer != NULL)
// 			(*lexer)->prev = NULL;
// 		free(current);
// 		return;
// 	}
// 	while (current->index != index)
// 		current = current->next;
// 	if (current == NULL) {
// 		printf("Index out of range. Cannot delete.\n");
// 		return;
// 	}
// 	current->prev->next = current->next;
// 	if (current->next != NULL)
// 		current->next->prev = current->prev;
// 	free(current);
// }

// int	reset_increment_i(int x)
// {
// 	static int i = 0;
// 	if (x == 0)
// 		i = 0;
// 	else
// 		i++;
// 	return (i);
// }