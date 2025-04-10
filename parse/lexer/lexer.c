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



int	lexer(void)
{
	t_shell_state	*shell;
	int				i;

	shell = get_shell();
	i = 0;
	//[STEPH] adicionar checker de quotes
	while (shell->readline[i])
	{
		white_space(&i);
		if (shell->readline[i] == '|')
			add_pipe(i++, 1, PIPE);
		//[STEPH] adicionar skipers
	}
}
