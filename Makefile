# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/05 20:21:35 by yel-yaqi          #+#    #+#              #
#    Updated: 2024/07/03 12:57:11 by yel-yaqi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS		=  -O3 -Wall -Wextra -Werror -g
EXE		= minishell
 
LIB_DIR		= ./libft
LIBFT		= $(LIB_DIR)/libft.a
TARGET_TEST 	= test
TARGET_TEST_SOURCES = checks/tests.c
MAIN_SOURCES 	= src/parser_engine/tokenizer/tokenize.c \
	   src/parser_engine/tokenizer/name_operators.c \
	   src/parser_engine/tokenizer/is_operator.c \
	   src/parser_engine/tokenizer/type_files_and_limiters.c \
	   src/parser_engine/parser/build_pipelines.c \
	   src/parser_engine/parser/connect_pipelines.c \
	   src/parser_engine/parser/fetch_ast.c \
	   src/parser_engine/parser/para.c \
	   src/parser_engine/parser/build_list.c \
	   src/parser_engine/parser/build_redirections.c \
	   src/split/split.c src/split/strlen.c \
	   src/split/substr.c src/split/strdup.c \
	   src/split/strlcpy.c src/split/strchr.c\
	   src/split/quoted.c src/list.c \
	   src/minishell_.c src/builtins/echo.c \
	   src/builtins/builtins.c src/builtins/cd.c \
	   src/builtins/env.c
	   ALL_SOURCES = $(MAIN_SOURCES) $(TARGET_TEST_SOURCES)

MAIN_OBJ 	= $(MAIN_SOURCES:.c=.o)
TEST_OBJ 	= $(TARGET_TEST_SOURCES:.c=.o)
ALL_OBJ 	= $(MAIN_OBJ) $(TEST_OBJ)

HEADER 		= include/minishell.h

all: $(EXE)
	@echo "\033[032mminihell is ready for SEGFAULTS"

check: $(TARGET_TEST)

libft: $(LIBFT)

src/%.o: src/%.c $(HEADER) Makefile
	@cc -c $< -o $@

checks/%.o: checks/%.c $(HEADER) Makefile
	@cc -g -c $< -o $@

$(EXE): $(MAIN_OBJ) $(LIBFT)
	@cc $(CFLAGS) $^ -lreadline -o $@

$(TARGET_TEST): $(ALL_OBJ) $(HEADER) $(LIBFT) Makefile
	cc $(ALL_OBJ) -g $(LIBFT) -lreadline -o $@

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)
clean:
	@$(RM) $(ALL_OBJ)
	@$(MAKE) -C libft/ clean

fclean: clean
	@$(RM) $(EXE) $(TARGET_TEST)
	@$(MAKE) -C libft/ fclean

re: fclean all


.PHONY: check
