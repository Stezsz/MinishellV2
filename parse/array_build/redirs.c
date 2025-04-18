/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strodrig <strodrig@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:27:11 by strodrig          #+#    #+#             */
/*   Updated: 2025/04/18 21:27:11 by strodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
** Assigns redirection types and values to a redirection array.
*/
void	assign_redirs(t_token	*token, t_redirection	***redirs)
{
	int		i;

	i = 0;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_REDIR)
		{
			(*redirs)[i]->type = token->next->type;
			(*redirs)[i]->content = token->next->content;
			if (ft_strncmp(token->content, "<<", 2) == 0)
				(*redirs)[i++]->type = TOKEN_HERE_DOC;
			else if (!ft_strncmp(token->content, ">>", 2))
				(*redirs)[i++]->type = TOKEN_APPEND;
			else if (!ft_strncmp(token->content, ">", 2))
				(*redirs)[i++]->type = TOKEN_OUTFILE;
			else
				(*redirs)[i++]->type = TOKEN_INFILE;
		}
		token = token->next;
	}
	(*redirs)[i] = NULL;
}

/**
** Extracts and initializes redirection structures from a token list.
*/
t_redirection	**get_redirections(t_token	*token)
{
	int				redir_num;
	int				i;
	t_token			*tmp;
	t_redirection	**redirs;

	redir_num = 0;
	tmp = token;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (tmp->type == TOKEN_REDIR)
			redir_num++;
		tmp = tmp->next;
	}
	redirs = ft_calloc(sizeof(t_redirection *), redir_num + 1);
	if (!redirs)
		return (NULL);
	i = 0;
	while (i < redir_num)
	{
		(redirs)[i] = ft_calloc(sizeof(t_redirection), 1);
		if (!(redirs)[i++])
			return (NULL);
	}
	assign_redirs(token, &redirs);
	return (redirs);
}
