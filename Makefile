# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/05 20:21:35 by yel-yaqi          #+#    #+#              #
#    Updated: 2024/07/29 21:29:43 by mrezki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

USER			:= $(shell whoami)
CFLAGS			= -O3 -Wall -Wextra -Werror -g -lreadline 
NAME			= minishell
LIB_DIR			= ./libft
LIBFT			= $(LIB_DIR)/libft.a
MAIN_SOURCES 		= src/parser_engine/tokenizer/tokenize.c \
			src/parser_engine/tokenizer/name_operators.c \
			src/parser_engine/tokenizer/is_operator.c \
			src/parser_engine/tokenizer/type_files_and_limiters.c \
			src/parser_engine/tokenizer/make_irregular_arguments.c \
			src/parser_engine/parser/build_pipelines.c \
			src/parser_engine/parser/build_redirections.c \
			src/parser_engine/parser/build_redir_branch.c \
			src/parser_engine/parser/connect_pipelines.c \
			src/parser_engine/parser/connect_redirections.c \
			src/parser_engine/parser/fetch_ast.c \
			src/parser_engine/parser/para.c \
			src/parser_engine/parser/build_list.c \
			src/parser_engine/parser/put_args_into_cmd_tokens.c \
			src/parser_engine/parser/parse.c \
			src/parser_engine/parser/remove_quotes.c \
			src/parser_engine/parser/set_expansion_indices.c \
			src/parser_engine/syntax_analyser/check_tokens.c \
			src/parser_engine/syntax_analyser/check_tokenizer_output.c \
			src/parser_engine/syntax_analyser/quotes_balanced.c src/utils/gc.c \
			src/utils/split/split.c src/utils/split/strlen.c \
			src/utils/split/substr.c src/utils/split/strdup.c \
			src/utils/split/strlcpy.c src/utils/split/quoted.c src/list.c \
			src/utils/strequal.c src/minishell_.c src/builtins/echo.c \
			src/builtins/builtins.c src/builtins/cd.c \
			src/builtins/env.c src/builtins/pwd.c src/builtins/export.c \
			src/builtins/unset.c src/builtins/exit.c src/utils/free.c \
			src/utils/envp_list.c src/utils/char_utils.c src/builtins/unset_append.c \
			src/builtins/env_shlvl.c src/signal.c src/exec/traverse.c \
			src/exec/path.c src/exec/here_doc.c src/exec/pipe.c \
			src/exec/and_or.c src/exec/redirections.c src/exec/command.c \
			src/utils/wildcard.c src/utils/wildcard_utils.c src/utils/expand.c \
			src/utils/heredoc_utils.c src/utils/expand_heredoc.c \
			src/utils/redir_utils.c src/builtins/export_u.c \
			src/utils/prompt_line.c

MAIN_OBJ 	= $(MAIN_SOURCES:.c=.o)

HEADER 		= include/minishell.h include/structs.h include/exec.h include/builtins.h

ifeq ($(USER), mrezki)
	CFLAGS += -L/Users/mrezki/.brew/opt/readline/lib
else
	CFLAGS += -L/Users/yel-yaqi/.brew/opt/readline/lib
endif

all: $(NAME)

check: $(TARGET_TEST)

libft: $(LIBFT)

src/%.o: src/%.c $(HEADER) Makefile
	cc -c -Wall -Wextra -Werror -g $< -o $@

$(NAME): $(MAIN_OBJ) $(LIBFT)
	cc $(CFLAGS) $^ -o $@

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)
clean:
	@$(RM) $(ALL_OBJ)
	@$(MAKE) -C libft/ clean

fclean: clean
	@$(RM) $(NAME) $(TARGET_TEST)
	@$(MAKE) -C libft/ fclean

re: fclean all


.PHONY: check
