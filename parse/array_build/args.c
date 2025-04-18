/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strodrig <strodrig@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:18:55 by strodrig          #+#    #+#             */
/*   Updated: 2025/04/18 21:18:55 by strodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
** Checks if a token is an argument.
*/
int	is_argument(t_token *token)
{
	if ((token->type == TOKEN_WORD || token->type == TOKEN_QUOTE
		|| token->type == TOKEN_DOLLAR) &&
		(token->prev || token->prev->type != TOKEN_REDIR))
		return (1);
	return (0);
}

/**
** Assigns arguments from tokens to the argument array.
*/
void	assign_arguments(t_token *tokens, char ***args)
{
	int	i;

	i = 0;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (is_argument(tokens))
			(*args)[i++] = tokens->content;
		tokens = tokens->next;
	}
	(*args)[i] = NULL;
}

/**
** Extracts and assigns command arguments from the token list.
*/
void	get_command_args(t_token *token, t_command *cmd)
{
	t_token	*tmp;
	int		arg_count;

	tmp = token;
	arg_count = 0;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (is_argument(tmp))
			arg_count++;
		tmp = tmp->next;
	}
	cmd->arguments = ft_calloc(sizeof(char *) \
				* (arg_count + 1), 1);
	if (!(cmd->arguments))
		return ;
	assign_arguments(token, &cmd->arguments);
	cmd->arg_count = arg_count;
}
