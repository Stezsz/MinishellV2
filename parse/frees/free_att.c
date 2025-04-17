/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_att.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strodrig <strodrig@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:19:10 by strodrig          #+#    #+#             */
/*   Updated: 2025/04/17 13:19:10 by strodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** frees shell->tokens memony and sets all pointers to NULL.
*/
void	free_tokens(void)
{
	t_shell_state	*shell;
	t_token			*temp;

	shell = get_shell();
	while (shell->tokens)
	{
		temp = shell->tokens->next;
		if (shell->tokens->content)
		{
			free(shell->tokens->content);
			shell->tokens->content = NULL;
		}
		free(shell->tokens);
		shell->tokens = NULL;
		shell->tokens = temp;
	}
	shell->tokens = NULL;
}

/*
** frees shell->cmd->redirections memony and sets all pointers to NULL.
*/
void	free_cmd_redirections(t_command **cmd)
{
	int	i;

	i = 0;
	while ((*cmd)->redirections && (*cmd)->redirections[i])
	{
		(*cmd)->redirections[i]->content = NULL;
		free ((*cmd)->redirections[i]);
		(*cmd)->redirections[i++] = NULL;
	}
	if ((*cmd)->redirections)
		free ((*cmd)->redirections);
	(*cmd)->redirections = NULL;
	i = 0;
	while ((*cmd)->here_docs && (*cmd)->here_docs[i])
	{
		(*cmd)->here_docs[i]->content = NULL;
		free ((*cmd)->here_docs[i]);
		(*cmd)->here_docs[i++] = NULL;
	}
	if ((*cmd)->here_docs)
		free ((*cmd)->here_docs);
	(*cmd)->here_docs = NULL;
}

/*
** frees shell->cmd memony and sets all pointers to NULL.
*/
void	free_cmds(void)
{
	int	k;

	k = 0;
	while (get_shell() && get_shell()->commands
			&& get_shell()->commands[k])
	{
		if (get_shell()->commands[k]->arguments)
			free (get_shell()->commands[k]->arguments);
		get_shell()->commands[k]->arguments = NULL;
		free_cmd_redirections(&(get_shell()->commands[k]));
		free(get_shell()->commands[k]);
		get_shell()->commands[k++] = NULL;
	}
	if (get_shell() && get_shell()->commands)
		free (get_shell()->commands);
	get_shell()->commands = NULL;
}

/*
** frees all attributes of the shell->cmd and shell->tokens list and sets all pointers to NULL.
*/
void	free_atributes(void)
{
	free_tokens();
	free_cmds();
}
