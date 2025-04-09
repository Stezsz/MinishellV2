/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strodrig <strodrig@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:27:15 by strodrig          #+#    #+#             */
/*   Updated: 2025/04/09 18:47:31 by strodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <fcntl.h>
# include <signal.h>

typedef enum e_token_type
{
	TOKEN_PIPE,
	TOKEN_REDIR,
	TOKEN_WORD,
	TOKEN_QUOTE,
	TOKEN_DOLLAR,
	TOKEN_APPEND,
	TOKEN_INFILE,
	TOKEN_OUTFILE,
	TOKEN_HERE_DOC,
	TOKEN_COMMAND,
	TOKEN_COMMAND_ARGS,
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*content;
	struct s_token		*prev;
	struct s_token		*next;
}	t_token;

typedef struct s_redirection
{
	t_token_type	type;
	t_token_type	expansion_rule;
	char			*content;
}	t_redirection;

typedef struct s_command
{
	t_redirection		**here_docs;

	int					fd_input;
	int					fd_output;
	int					pipe_fds[2];
	t_redirection		**redirections;
	int					output_error;

	int					process_id;

	char				**arguments;
	int					arg_count;
}	t_command;

typedef struct s_shell_state
{
	char		*input_line;

	t_token		*tokens;
	t_command	**commands;

	t_list		*env_vars;
	t_list		*exported_vars;

	int			exit_code;

	int			here_doc_pipe[2];

	char		*private_exec_path;
}	t_shell_state;

/* ----- before_lexer.c ----- */
t_shell_state	*get_shell(void);
void			check_main_args(int ac);

#endif
