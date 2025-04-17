/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strodrig <strodrig@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:27:15 by strodrig          #+#    #+#             */
/*   Updated: 2025/04/17 14:06:34 by strodrig         ###   ########.fr       */
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

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

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


/* ----- parse/ ----- */
/* ----- frees/ ----- */
/* ----- free_att.c ----- */
void	free_tokens(void);
void	free_atriutes(void);
void	free_cmds(void);
void	free_cmd_redirections(t_command **cmd);
void	free_att(void);

/* ----- lexer/ ----- */
/* ----- lexer.c ----- */
int	quotes_check(void);
int	lexer(void);
/* ----- skips.c ----- */
void	white_space(int *i);
int	quote_skipper(int *i);
void	word_skipper(int *i);
void	redir_skipper(int *i);
/* ----- tokens.c ----- */
void	add_token(int start, int len, t_token_type type);
t_token	*tokenlast(t_token *lst);

/* ------ expander/ ----- */
/* ----- expander.c ----- */
void	expand_quote(int *i, char **update, char *src, char quote_char);
void	expand_node(t_token **tmp, char	*update);
void	expander(void);
/* ----- utils.c ----- */
void	update_str(char **str, char *src, int index, int mode);
void	process_dollar(int *i, char *str, char **update);
void	clear_empty_token(void);

/* ----- before_lexer.c ----- */
t_shell_state	*get_shell(void);
void			check_main_args(int ac);

/* ----- libft functions ----- */
void	*ft_calloc(size_t count, size_t size);
void	ft_putstr_fd(char *s, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
