# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/05 20:21:35 by yel-yaqi          #+#    #+#              #
#    Updated: 2024/06/24 16:35:06 by yel-yaqi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
NAME = minishell
 
TARGET_TEST = test
TARGET_TEST_SOURCES = checks/tests.c
MAIN_SOURCES = src/parser_engine/tokenizer/tokenize.c \
			   src/parser_engine/tokenizer/name_operators.c \
			   src/parser_engine/tokenizer/is_operator.c \
			   src/parser_engine/parser/build_pipelines.c \
			   src/parser_engine/parser/connect_pipelines.c \
			   src/parser_engine/parser/fetch_ast.c \
			   src/parser_engine/parser/para.c \
			   src/parser_engine/parser/build_list.c \
			   src/split/split.c \
			   src/split/strlen.c \
			   src/split/substr.c \
			   src/split/strdup.c \
			   src/split/strlcpy.c \
			   src/split/strchr.c \
			   src/split/quoted.c \
			   src/list.c
ALL_SOURCES = $(MAIN_SOURCES) $(TARGET_TEST_SOURCES)

MAIN_OBJ = $(MAIN_SOURCES:.c=.o)
TEST_OBJ = $(TARGET_TEST_SOURCES:.c=.o)
ALL_OBJ = $(MAIN_OBJ) $(TEST_OBJ)

HEADER = include/minishell.h

all: $(NAME)
check: $(TARGET_TEST)

src/%.o: src/%.c $(HEADER) Makefile
	cc -c $< -o $@

checks/%.o: checks/%.c  $(HEADER) Makefile
	cc -g -c $< -o $@

$(NAME): $(MAIN_OBJ) $(HEADER) Makefile # add cflags later
	cc $(MAIN_OBJ) -o $@

$(TARGET_TEST): $(ALL_OBJ) $(HEADER) Makefile
	cc $(ALL_OBJ) -g -lreadline -o $@

clean:
	rm -f src/*.o
	rm -f src/split/*.o
	rm -f src/parser_engine/parser/*.o
	rm -f src/parser_engine/tokenizer/*.o
	rm -f checks/*.o

fclean: clean
	rm -f minishell
	rm -f test

re: fclean all

.PHONY: check