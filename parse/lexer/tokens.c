/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strodrig <strodrig@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:33:37 by strodrig          #+#    #+#             */
/*   Updated: 2025/04/10 16:33:37 by strodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** allocates new token with instruction from paramethers and adds
** it to the end to shell->tokens list, which is returned by get_shell().
*/
void	add_token(int start, int len, t_token_type type)
{
	t_shell_state	*shell;
	t_token		*new_token;

	shell = get_shell();
	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		free_att();
		exit(1);
	}
	new_token->type = type;
	new_token->content = ft_substr(shell->input_line, start, len);
	new_token->next = NULL;
	new_token->prev = tokenlast(shell->tokens);
	if (new_token->prev)
		new_token->prev->next = new_token;
	else
		shell->tokens = new_token;
}

/*
** return last node of that t_token list.
*/
t_token	*tokenlast(t_token *lst)
{
	t_token	*last;

	last = lst;
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}
