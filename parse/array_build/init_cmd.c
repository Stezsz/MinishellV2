/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strodrig <strodrig@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:26:05 by strodrig          #+#    #+#             */
/*   Updated: 2025/04/18 21:26:05 by strodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
** Creates and initializes a new command structure from a token list.
*/
t_command	*get_next_command(t_token *token)
{
	t_command	*cmd;

	cmd = ft_calloc(sizeof(t_command), 1);
	if (cmd == NULL)
	{
		return (NULL);
	}
	cmd->process_id = 0;
	cmd->fd_input = 0;
	cmd->fd_output = 1;
	cmd->output_error = 0;
	get_command_args(token, cmd);
	if (!cmd->arguments)
	{
		return (NULL);
	}
	cmd->redirections = get_redirections(token);
	return (cmd);
}

/**
** Advances the token pointer to the next command token.
*/
void	get_next_cmd_token(t_token **token)
{
	while (*token && (*token)->type != TOKEN_PIPE)
		*token = (*token)->next;
	if (*token)
		(*token) = (*token)->next;
}

/**
** Counts the number of commands in a token list.
*/
int	count_commands(t_token *tokens)
{
	int	cmd_num;

	cmd_num = 1;
	while (tokens != NULL)
	{
		if (tokens->type == TOKEN_PIPE)
			cmd_num++;
		tokens = tokens->next;
	}
	return (cmd_num);
}

/**
** Initializes the command structures from the token list.
*/
int	init_commands(void)
{
	int			cmd_num;
	t_token		*tmp;
	int			i;
	size_t		size_p;

	cmd_num = count_commands(get_shell()->tokens);
	size_p = sizeof(t_command *);
	get_shell()->commands = ft_calloc(cmd_num + 1, size_p);
	if (get_shell()->commands == NULL)
		return (1);
	tmp = get_shell()->tokens;
	get_shell()->commands[0] = get_next_command(tmp);
	i = 1;
	while (i < cmd_num)
	{
		get_next_cmd_token(&tmp);
		get_shell()->commands[i++] = get_next_command(tmp);
	}
	get_shell()->commands[i] = NULL;
	return (0);
}
