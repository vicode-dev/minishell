
SRCS			:=	main.c
SRCS_BUILTINS	:=	env.c cd.c
SRCS_PARSING	:=	parsing_env.c
SRCS_PIPEX		:=	#pipex_main.c pipex_utils.c pipex_parsing.c
OBJS			:= $(SRCS:.c=.o)
OBJS_PARSING	:= $(addprefix parsing/,$(SRCS_PARSING:.c=.o))
OBJS_BUILTINS	:= $(addprefix builtins/,$(SRCS_BUILTINS:.c=.o))
OBJS_PIPEX		:= $(addprefix pipex/,$(SRCS_PIPEX:.c=.o))
CC				:= gcc
RM				:= rm -f
CFLAGS			:= -Wall -Wextra -Werror  -I.
NAME			:= minishell
# NAME_BONUS		:= pipex_bonus

all:			$(NAME)

$(NAME):		$(OBJS) $(OBJS_PIPEX) $(OBJS_BUILTINS) $(OBJS_PARSING)
				$(MAKE) bonus -C ./libft
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(OBJS_PIPEX) $(OBJS_BUILTINS) $(OBJS_PARSING) libft/libft.a
				
# bonus:			$(NAME_BONUS)

clean:
				$(MAKE) clean -C ./libft
				$(RM) $(OBJS)
				$(RM) $(OBJS_BONUS)
				$(RM) $(OBJS_BUILTINS)
				$(RM) $(OBJS_PARSING)

fclean:			clean
				$(MAKE) fclean -C ./libft
				$(RM) $(NAME)
				$(RM) $(NAME_BONUS)


# $(NAME_BONUS):	$(OBJS_BONUS)
# 				$(MAKE) bonus -C ./libft
# 				$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) libft/libft.a

re:				fclean $(NAME)

.PHONY:			all clean fclean re bonus
# .SILENT:
