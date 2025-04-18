SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
       ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
       ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
       ft_calloc.c ft_strdup.c ft_toupper.c ft_tolower.c \
       ft_strchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
       ft_strnstr.c ft_atoi.c ft_strrchr.c ft_substr.c \
       ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
       ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
       ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
       ft_lstnew.c ft_lstadd_front.c \
       ft_lstsize.c ft_lstlast.c \
       ft_lstadd_back.c ft_lstdelone.c \
       ft_lstclear.c ft_lstiter.c \
       ft_lstmap.c

OBJS = ${SRCS:.c=.o}
NAME = libft.a
LIBC = ar rcs
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

#Colors:
GREEN		=	\033[92;5;118m
YELLOW		=	\033[93;5;226m
GRAY		=	\033[33;2;37m
RESET		=	\033[0m
CURSIVE		=	\033[33;3m

.c.o:
	@printf "$(CURSIVE)$(GRAY) 	- Making object file $(notdir $@) from source file $(notdir $<) ... $(RESET)\n"
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	@printf "$(CURSIVE)$(GRAY) 	- Creating library $(NAME)... $(RESET)\n"
	@${LIBC} ${NAME} ${OBJS}
	@printf "$(GREEN)    - Library $(NAME) created.\n$(RESET)"

all: ${NAME}

# Keeping bonus target for backward compatibility
bonus: ${NAME}

clean:
	@${RM} ${OBJS}
	@printf "$(CURSIVE)$(GRAY)	- Removing libft object files ... $(RESET)\n"
	@printf "$(YELLOW)    - Libft object files removed.$(RESET)\n"

fclean: clean
	@${RM} ${NAME}
	@printf "$(CURSIVE)$(GRAY)	- Removing $(NAME)... $(RESET)\n"
	@printf "$(YELLOW)    - Library $(NAME) removed.$(RESET)\n"

re: fclean all

.PHONY : all bonus clean fclean re
