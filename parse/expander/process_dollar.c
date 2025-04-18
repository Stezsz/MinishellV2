/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strodrig <strodrig@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:03:10 by strodrig          #+#    #+#             */
/*   Updated: 2025/04/18 21:03:10 by strodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
** Retrieves the value of an environment variable.
*/
char	*get_value(char *var_name)
{
	t_list	*tmp;
	size_t	len;

	if (!var_name || !(get_shell()) || !(get_shell()->env_vars))
		return (NULL);
	tmp = get_shell()->env_vars;
	len = ft_strlen(var_name);
	while (tmp)
	{
		len = 0;
		while (var_name[len] && ((char *)tmp->content)[len]
						&& var_name[len] == ((char *)tmp->content)[len])
			len++;
		if (var_name[len] == '\0'
						&& ((char *)tmp->content)[len] == '=')
			return (((char *)tmp->content) + len + 1);
		tmp = tmp->next;
	}
	return (NULL);
}

/**
** Expands the exit status into the provided string.
*/
void	exit_status_expander(char **update)
{
	char	*aux;

	aux = ft_itoa(get_shell()->exit_code);
	update_str(update, aux, 0, safe_strlen(aux));
	if (aux)
		free(aux);
}

/**
** Expands a standard dollar sign format variable ('$variable').
*/
void	expand_standard_dollar(int *len, char *src, char **update)
{
	int		i;
	char	*var_name;
	char	*value;
	char	*aux;

	i = 1;
	while (ft_isalnum(src[i]) || src[i] == '_')
		i++;
	var_name = ft_substr(src, 1, i - 1);
	value = get_value(var_name);
	if (value && value[0])
	{
		aux = ft_strdup(*update);
		if (*update)
			free(*update);
		*update = ms_strjoin(aux, value);
		if (aux)
			free(aux);
	}
	*len = *len + i;
	if (var_name)
		free(var_name);
}

/**
** Processes a dollar sign for variable expansion in the string.
*/
void	process_dollar(int *len, char *src, char **update)
{
	if (src[1] == '\"' || src[1] == '\'')
	{
		(*len)++;
		return ;
	}
	if ((!ft_isalpha(src[1]) && src[1] != '_' && src[1] != '?')
		|| ft_isdigit(src[1]))
	{
		if (src[1] == 0 || src[1] == ' ' || src[1] == '\t' || src[1] == '\n')
			update_str(update, src, 0, 2);
		if (src[1] == '\0')
			(*len)++;
		else
			*len += 2;
	}
	else if (src[1] == '?')
	{
		exit_status_expander(update);
		*len += 2;
	}
	else
		expand_standard_dollar(len, src, update);
}

void	expand_node(t_token **tmp, char *update)
{
	int		i;

	if (tmp && *tmp)
	{
		i = 0;
		while ((*tmp)->content && (*tmp)->content[i])
		{
			if ((*tmp)->content[i] == '\'' || (*tmp)->content[i] == '\"')
			{
				expand_quote(&i, &update, (*tmp)->content + i, (*tmp)->content[i]);
			}
			else if ((*tmp)->content[i] == '$')
			{
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
}
