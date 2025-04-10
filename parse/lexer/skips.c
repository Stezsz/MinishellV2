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

int	white_space(int *i)
{
	t_shell_state	*shell;
	char		*str;

	shell = get_shell();
	str = shell->readline;
	while (s[*i] && (str[*i] == ' ' || str[*i] == '\t'
			|| str[*i] == '\n'))
	{
		(*i)++;
	}
}
