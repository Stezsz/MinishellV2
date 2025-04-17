/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strodrig <strodrig@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:17:45 by strodrig          #+#    #+#             */
/*   Updated: 2025/04/10 16:17:45 by strodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
check if the quotes are closed single and double quotes, if not return 1
*/

int	quotes_check(void)
{
	t_shell_state	*shell;
	int				i;

	shell = get_shell();
	i = 0;
	while (shell->input_line[i])
	{
		if (shell->input_line[i] == '\'' || shell->input_line[i] == '\"')
		{
			if (quote_skipper(&i) == 1)
			{
				ft_putstr_fd("minishell: quotes error", 2);
				return (1);
			}
		}
		else
			i++;
	}
	return (0);
}

/*
builds the tokens from the input string, it will check for quotes and pipes
and add them to the token list, it will also check for white spaces and skip them
*/

int	lexer(void)
{
	t_shell_state	*shell;
	int				i;

	shell = get_shell();
	i = 0;
	if (quotes_check() == 1)
		return (1);
	while (shell->input_line[i])
	{
		white_space(&i);
		if (shell->input_line[i] == '|')
			add_token(i++, 1, TOKEN_PIPE);
		//[STEPH] adicionar skipers
	}
	return (0);
}
