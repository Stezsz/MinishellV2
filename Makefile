NAME = minishell
LIBFT = libft/libft.a
LIBFT_DIR = libft

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

FILES = $(shell find . -type f -name '*.c' | sed 's|^\./||;s|\.c$$||') #[ADD] path normal

SRC		= $(FILES:=.c)
OBJ		= $(FILES:=.o)
HEADER = includes/minishell.h
INCLUDES	= -I includes -I $(LIBFT_DIR)
LDFLAGS	+= -lreadline # leite: no meu pc dá se usar isto-> LDFLAGS	+= -L/usr/lib -ledit

#Colors:
GREEN		=	\033[92;5;118m
YELLOW		=	\033[93;5;226m
GRAY		=	\033[33;2;37m
RESET		=	\033[0m
CURSIVE		=	\033[33;3m

#Debug
ifeq ($(DEBUG), 1)
	OPTS = -g
endif

.PHONY: all clean fclean re norm libft

all: libft $(NAME)

libft:
	@printf "$(CURSIVE)$(GRAY) 	- Making libft... $(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR)
	@printf "$(GREEN)    - Libft ready.\n$(RESET)"

$(NAME): $(LIBFT) $(OBJ) $(HEADER)
	@printf "$(CURSIVE)$(GRAY) 	- Compiling $(NAME)... $(RESET)\n"
	@ $(CC) $(OBJ) $(INCLUDES) $(LDFLAGS) $(OPTS) $(LIBFT) -o $(NAME)
	@printf "$(GREEN)    - Executable ready.\n$(RESET)"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c $(HEADER)
	@printf "$(CURSIVE)$(GRAY) 	- Making object file $(notdir $@) from source file $(notdir $<) ... $(RESET)\n"
	@ $(CC) $(CFLAGS) $(INCLUDES) $(OPTS) -c $< -o $@

clean:
	@ $(RM) $(OBJ)
	@printf "$(CURSIVE)$(GRAY)	- Removing object files ... $(RESET)\n"
	@printf "$(YELLOW)    - Object files removed.$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) clean

norm:
	@printf "$(CURSIVE)$(GRAY)"
	@norminette
	@printf "$(RESET)"

fclean: clean
	@ $(RM) $(NAME)
	@printf "$(CURSIVE)$(GRAY)	- Removing $(NAME)... $(RESET)\n"
	@printf "$(YELLOW)    - Executable removed.$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
