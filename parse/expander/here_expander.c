/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strodrig <strodrig@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:58:40 by strodrig          #+#    #+#             */
/*   Updated: 2025/04/18 20:58:40 by strodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
** Expands variables in a here-doc line.
*/
void	here_expander(char **line)
{
	int	i;
	char	*updated_line;

	updated_line = NULL;
	i = 0;
	while (*line && (*line)[i])
	{
		if ((*line)[i] == '$')
			process_dollar(&i, *line + i, &updated_line);
		else
			update_str(&updated_line, *line, i++, 1);
	}
	if (*line)
		free(*line);
	if (updated_line)
		*line = updated_line;
	else
		*line = NULL;
}
