/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skips.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strodrig <strodrig@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:31:37 by strodrig          #+#    #+#             */
/*   Updated: 2025/04/10 16:31:37 by strodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** This function skips the white spaces in the input string, it will check for
** spaces, tabs and new lines, if it finds any it will increment the index
*/

void	white_space(int *i)
{
	t_shell_state	*shell;
	char		*str;

	shell = get_shell();
	str = shell->input_line;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'
			|| str[*i] == '\n'))
	{
		(*i)++;
	}
}

/*
** skips a substring between the fist it finds.
*/
int	quote_skipper(int *i)
{
	t_shell_state	*shell;
	char	c;

	shell = get_shell();
	c = shell->input_line[*i];
	(*i)++;
	while (shell->input_line[*i] && shell->input_line[*i] != c)
		(*i)++;
	if (shell->input_line[*i] == c)
	{
		(*i)++;
		return (0);
	}
	return (1);
}

/*
** skips a redirection in a string
*/
void	word_skipper(int *i)
{
	t_shell_state	*shell;
	int		j;

	shell = get_shell();
	j = *i;
	while (shell->input_line[*i] && shell->input_line[*i] != '|'
			&& shell->input_line[*i] != '>' && shell->input_line[*i] != '<'
			&& shell->input_line[*i] != ' ' && shell->input_line[*i] != '\t'
			&& shell->input_line[*i] != '\n')
	{
		if (shell->input_line[*i] == '\'' || shell->input_line[*i] == '\"')
			quote_skipper(i);
		else
			(*i)++;
	}
	if (*i - j)
		add_token(j, *i, TOKEN_WORD);
}

/*
** skips a redirection in a string
*/
void	redir_skipper(int *i)
{
	t_shell_state	*shell;
	int		j;

	shell = get_shell();
	j = *i;
	if (shell->input_line[*i + 1] == shell->input_line[*i])
	{
		(*i) = *i + 2;
		add_token(j, 2, TOKEN_REDIR);
		return;
	}
	add_token(j, 1, TOKEN_REDIR);
	(*i)++;
}
