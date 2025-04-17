/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strodrig <strodrig@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:37:39 by strodrig          #+#    #+#             */
/*   Updated: 2025/04/09 18:47:18 by strodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function checks the number of arguments passed to the program.
// If the number of arguments is not equal to 1, it prints an error message
void	check_main_args(int ac)
{
	if (ac != 1)
	{
		write(2, "Error: Invalid number of arguments\n", 36); //[ADD] Adicionar outro output futuramente
		exit(0);
	}
	get_shell()->private_exec_path = NULL;
}

//return address of static t_shell struct.
t_shell_state	*get_shell(void)
{
	static t_shell_state	shell;

	return (&shell);
}
