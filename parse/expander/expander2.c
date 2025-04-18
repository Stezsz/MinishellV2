/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strodrig <strodrig@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:41:36 by strodrig          #+#    #+#             */
/*   Updated: 2025/04/18 20:41:36 by strodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
** Safely calculates the length of a string, returning 0 if the string is NULL.
*/
size_t	safe_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

/**
** Concatenates two strings and returns a new string.
*/
char	*ms_strjoin(const char *s1, const char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	result = malloc(sizeof(char) * (safe_strlen(s1) + safe_strlen(s2) + 1));
	if (!result)
		return (NULL);
	len1 = 0;
	while (s1 && s1[len1])
	{
		result[len1] = s1[len1];
		len1++;
	}
	len2 = 0;
	while (s2 && s2[len2])
	{
		result[len1 + len2] = s2[len2];
		len2++;
	}
	result[len1 + len2] = '\0';
	return (result);
}

/**
** Restores empty strings for quoted tokens.
*/
void	restore_empty_str(void)
{
	t_token *tmp;

	tmp = get_shell()->tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_QUOTE && (!tmp->content))
			tmp->content = ft_calloc(1, 1);
		tmp = tmp->next;
	}
}

/**
** Removes empty tokens of type DOLLAR from the shell's token list.
*/
void	clear_empty_token(void)
{
	t_token *tmp;
	t_token *prev;
	t_shell_state *shell;

	prev = NULL;
	shell = get_shell();
	tmp = shell->tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_DOLLAR && (!tmp->content || !*tmp->content))
		{
			if (prev)
			{
				prev->next = tmp->next;
				if (tmp->next)
					tmp->next->prev = prev;
			}
			else
				shell->tokens = tmp->next;
			prev = tmp->prev;
			free(tmp->content);
			free(tmp);
			tmp = prev ? prev->next : shell->tokens;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

/**
** Updates a string by appending a substring from the source.
*/
void	update_str(char **update, char *src, int start, int len)
{
	char	*aux;
	char	*auxx;

	auxx = ft_substr(src, start, len);
	aux = ft_strdup(*update);
	if(*update)
		free(*update);
	*update = ms_strjoin(aux, auxx);
	if(aux)
		free(aux);
	if(auxx)
		free(auxx);
}
