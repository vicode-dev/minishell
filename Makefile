
SRCS			:=	main.c prompt.c free.c signal.c
SRCS_BUILTINS	:=	env.c cd.c pwd.c export_utils.c export.c export_add.c export_parsing.c export_print.c unset.c echo.c exit.c
SRCS_PARSING	:=	parsing_env_utils.c lexer.c lexer_utils.c expander.c parser.c parser_utils.c here_doc.c here_doc_utils.c checker.c checker_utils.c
SRCS_EXEC		:=	exec.c exec_utils.c pipex.c
OBJS			:= $(SRCS:.c=.o)
OBJS_PARSING	:= $(addprefix parsing/,$(SRCS_PARSING:.c=.o))
OBJS_BUILTINS	:= $(addprefix builtins/,$(SRCS_BUILTINS:.c=.o))
OBJS_PIPEX		:= $(addprefix pipex/,$(SRCS_PIPEX:.c=.o))
OBJS_EXEC		:= $(addprefix exec/,$(SRCS_EXEC:.c=.o))
CC				:= gcc
RM				:= rm -f
CFLAGS			:= -Wall -Wextra -Werror  -I. -ggdb3 #-fsanitize=address
READLINE		:= -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
NAME			:= minishell

all:			$(NAME)

$(NAME):		$(OBJS) $(OBJS_PIPEX) $(OBJS_BUILTINS) $(OBJS_PARSING) $(OBJS_EXEC)
				$(MAKE) bonus -C ./libft
				$(CC) $(CFLAGS) $(READLINE) -o $(NAME) $(OBJS) $(OBJS_PIPEX) $(OBJS_BUILTINS) $(OBJS_PARSING) $(OBJS_EXEC) libft/libft.a

clean:
				$(MAKE) clean -C ./libft
				$(RM) $(OBJS)
				$(RM) $(OBJS_BONUS)
				$(RM) $(OBJS_BUILTINS)
				$(RM) $(OBJS_PARSING)
				$(RM) $(OBJS_EXEC)

fclean:			clean
				$(MAKE) fclean -C ./libft
				$(RM) $(NAME)
				$(RM) $(NAME_BONUS)

re:				fclean $(NAME)

.PHONY:			all clean fclean re bonus
# .SILENT:
