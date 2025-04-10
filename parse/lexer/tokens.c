/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strodrig <strodrig@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:33:37 by strodrig          #+#    #+#             */
/*   Updated: 2025/04/10 16:33:37 by strodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * add_token - Adiciona um novo token à lista de tokens do shell.
 * @start: Índice inicial da substring na linha de comando.
 * @len: Comprimento da substring que será usada como valor do token.
 * @type: Tipo do token (definido pelo enum t_type).
 *
 * Esta função cria um novo token, inicializa seus valores e o adiciona
 * ao final da lista de tokens do shell. Caso a alocação de memória falhe,
 * a função imprime uma mensagem de erro, libera todos os recursos e encerra
 * o programa.
 */
void	add_token(int start, int len, t_type type)
{
	t_shell_state	*shell;
	t_token		*new_token;

	shell = get_shell();
	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2); // [ADD] adicionar função
		free_all();
		exit(1);
	}
	new_token->type = type;
	new_token->str = ft_substr(shell->readline, start, len);
	new_token->next = NULL;
	new_token->prev = tokenlast(shell->tokens);
	if (new_token->prev)
		new_token->prev->next = new_token;
	else
		shell->tokens = new_token;
}

/**
 * tokenlast - Retorna o último token de uma lista de tokens.
 * @lst: Ponteiro para o início da lista de tokens.
 *
 * Esta função percorre a lista de tokens até encontrar o último elemento
 * e retorna um ponteiro para ele. Se a lista estiver vazia, retorna NULL.
 */
t_token	*tokenlast(t_token *lst)
{
	t_token	*last;

	last = lst;
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}
