/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strodrig <strodrig@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:25:52 by strodrig          #+#    #+#             */
/*   Updated: 2025/04/17 13:18:54 by strodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_shell_state	*shell;

	(void)av;
	shell = get_shell();
	check_main_args(ac);
	shell->env_vars = get_env(envp); //[TIAGO] build_ins env
	shell->exported_vars = get_export(env_arr(shell->env_vars)); //[TIAGO] build_ins export && env_arr
	while (1)
	{
		if (lexer() == 1 || syntax_error() == 1)
			free_att();
	}
}
