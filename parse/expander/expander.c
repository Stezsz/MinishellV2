/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strodrig <strodrig@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:32:46 by strodrig          #+#    #+#             */
/*   Updated: 2025/04/17 13:32:46 by strodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Processes quoted content and handles expansions within quotes
 * Updates the string with expanded content when necessary
 */
void	expand_quote(int *i, char **update, char *src, char quote_char)
{
	int	len;

	len = 0;
	while (src && src[++len])
	{
		if (quote_char == '\'')
		{
			if (src[len] == '\'')
				break ;
			update_str(update, src, len, 1);
		}
		if (quote_char == '\"')
		{
			if (src[len] == '$' && src[len + 1] != '\"')
				process_dollar(&len, src + len, update);
			else if (src[len] == '$' && src[len + 1] == '\"')
				update_str(update, src, len++, 1);
			if (src[len] != '\"')
				update_str(update, src, len, 1);
			else if (src[len] == '\"')
				break ;
		}
	}
	*i += len;
}

/**
 * Processes a token and performs expansions on its content
 * Handles quotes and environment variables
 */
void	expand_node(t_token **tmp, char	*update)
{
	int	i;

	i = 0;
	while ((*tmp)->content && (*tmp)->content[i])
	{
		if ((*tmp)->content[i] == '\'' || (*tmp)->content[i] == '\"')
		{
			(*tmp)->type = TOKEN_QUOTE;
			expand_quote(&i, &update, (*tmp)->content + i, (*tmp)->content[i]);
			i++;
		}
		else if ((*tmp)->content[i] == '$')
		{
			(*tmp)->type = TOKEN_DOLLAR;
			process_dollar(&i, (*tmp)->content + i, &update);
		}
		else
			update_str(&update, (*tmp)->content, i++, 1);
	}
	if ((*tmp)->content)
		free((*tmp)->content);
	if (update)
		(*tmp)->content = update;
	else
		(*tmp)->content = NULL;
}

/**
 * Main expander function that processes all tokens
 * Expands environment variables and handles quotes
 */
void	expander(void)
{
	t_token	*tmp;

	if (!get_shell() || !get_shell()->tokens)
		return ;
	tmp = get_shell()->tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_WORD)
		{
			expand_node(&tmp, NULL);
		}
		tmp = tmp->next;
	}
	clear_empty_token();
}
