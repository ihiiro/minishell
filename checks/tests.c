#include <assert.h>
#include <libc.h>
#include <stdbool.h>
#include <readline/readline.h>
#include "../include/minishell.h"

void	in_order(t_ast* root)
{
	if (root == NULL)
		return ;
	in_order(root->left);
	in_order(root->right);
	if (root->token)
		printf("%s\n", root->token->word);
}

void	rebuild_expr(t_ast *root)
{
	if (root)
	{
		rebuild_expr(root->left);
		printf("%s ", root->token->word);
		rebuild_expr(root->right);
	}
	return;
}

void	g()
{
	system("leaks test");
}

int	main(void)
{
	atexit(g);
	//

	// parse("OMEGA | (A && b > c || d | > f && g | < h) > z << d | (G > F < D | < file0 X) > DELTA");
	// gc_malloc(1, );
	// while (1);




	//

	printf("\n#0 TOKENIZER-TYPES:\n");
	char	**word_list = ft_split(" a -l -a&&( b||c -ba | ( f -l	-d -x && g ) )  | d > e	", "	 ");
	t_token	*tokens = NULL;
	tokenize(word_list, &tokens);
	name_operators(tokens);
	type_files_and_limiters(tokens);
	assert(tokens->type == COMMAND);
	assert(tokens->next->type == ARGUMENT);
	assert(tokens->next->next->type == ARGUMENT);
	assert(tokens->next->next->next->type == OPERATOR);
	assert(tokens->next->next->next->next->type == PARA_OPEN);
	assert(tokens->next->next->next->next->next->type == COMMAND);
	assert(tokens->next->next->next->next->next->next->type == OPERATOR);
	assert(tokens->next->next->next->next->next->next->next->type == COMMAND);
	assert(tokens->next->next->next->next->next->next->next->next->type == ARGUMENT);
	assert(tokens->next->next->next->next->next->next->next->next->next->type == OPERATOR);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->type == PARA_OPEN);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->type == COMMAND);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->type == ARGUMENT);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->type == ARGUMENT);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == ARGUMENT);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == OPERATOR);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == COMMAND);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == PARA_CLOSE);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == PARA_CLOSE);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == OPERATOR);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == COMMAND);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == OPERATOR);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == FILE);

	printf("\033[0;32m	GOOD\033[0m\n\n");

	printf("\n#1 TOKENIZER-TOKEN-NAMES:\n");
	word_list = ft_split("&& || | > >> << <", " ");
	tokens = NULL;
	tokenize(word_list, &tokens);
	name_operators(tokens);
	assert(tokens->name == AND);
	assert(tokens->next->name == OR);
	assert(tokens->next->next->name == PIPE);
	assert(tokens->next->next->next->name == REDIR_OUT);
	assert(tokens->next->next->next->next->name == REDIR_APP);
	assert(tokens->next->next->next->next->next->name == HERE_DOC);
	assert(tokens->next->next->next->next->next->next->name == REDIR_IN);

	printf("\033[0;32m	GOOD\033[0m\n\n");

	printf("\n#2 PARSER-BUILD-PIPELINES:\n");
	word_list = ft_split("cat arg arg arg | ls arg | grep | wc && awk || cd | echo && less | tr", " ");
	tokens = NULL;
	tokenize(word_list, &tokens);
	name_operators(tokens);
	assert(build_pipelines(tokens->last) == 13);
	connect_pipelines(tokens);

	printf("\033[0;32m	GOOD\033[0m\n\n");

	printf("\n#3 PARSER-FETCH-AST:\n");
	assert(fetch_ast(tokens)->token->name == AND);
	printf("\033[0;32m	GOOD\033[0m\n");

	printf("\n#4 PARSER-AST-VALIDITY ( build_pipelines() + connect_pipelines() + fetch_ast() ):\n");
	word_list = ft_split("cat file0 | grep matchme && ls -la || cd ../..", " ");
	tokens = NULL;
	tokenize(word_list, &tokens);
	name_operators(tokens);
	build_pipelines(tokens->last);
	connect_pipelines(tokens);
	t_ast	*ast = fetch_ast(tokens);
	printf("ROOT->TOKEN=||");
	assert(ast->token->name == OR);
	printf("\n");
	printf("\033[0;32m	GOOD\033[0m\n");

	printf("ROOT->LEFT->TOKEN=&&");
	assert(ast->left->token->name == AND);
	printf("\n");
	printf("\033[0;32m	GOOD\033[0m\n");

	printf("ROOT->LEFT->RIGHT->TOKEN=ls");
	assert(strequal(ast->left->right->token->word, "ls"));
	printf("\n");
	printf("\033[0;32m	GOOD\033[0m\n");

	printf("ROOT->RIGHT->TOKEN=cd");
	assert(strequal(ast->right->token->word, "cd"));
	printf("\n");
	printf("\033[0;32m	GOOD\033[0m\n");

	printf("ROOT->LEFT->LEFT->TOKEN=|");
	assert(ast->left->left->token->name == PIPE);
	printf("\n");
	printf("\033[0;32m	GOOD\033[0m\n");

	printf("ROOT->LEFT->LEFT->LEFT->TOKEN=cat");
	assert(strequal(ast->left->left->left->token->word, "cat"));
	printf("\n");
	printf("\033[0;32m	GOOD\033[0m\n");

	printf("ROOT->LEFT->LEFT->RIGHT->TOKEN=grep");
	assert(strequal(ast->left->left->right->token->word, "grep"));
	printf("\n");
	printf("\033[0;32m	GOOD\033[0m\n\n");

	printf("#5 PARSER-SIMPLIFY-PARA:\n");
	tokens = NULL;
	word_list = ft_split("a && (c || d)", " ");
	tokenize(word_list, &tokens);
	name_operators(tokens);
	simplify_para(tokens);
	assert(tokens->type == COMMAND);
	assert(tokens->next->type == OPERATOR);
	assert(tokens->next->next->type == PARA);
	assert(tokens->next->next->subtree->token->name == OR);
	assert(tokens->next->next->subtree->left->token->type == COMMAND);
	assert(tokens->next->next->subtree->right->token->type == COMMAND);
	assert(tokens->next->next->next == NULL);
	build_pipelines(tokens);
	connect_pipelines(tokens);
	connect_para(tokens);
	printf("\033[0;32m	GOOD\033[0m\n\n");

	printf("#6 PARSER-TYPE-FILES-AND-LIMITERS:\n");
	tokens = NULL;
	word_list = ft_split("CMD < FILE > FILE << LIMITER", " ");
	tokenize(word_list, &tokens);
	type_files_and_limiters(tokens);
	assert(tokens->type == COMMAND);
	assert(tokens->next->type == OPERATOR);
	assert(tokens->next->next->type == FILE);
	assert(tokens->next->next->next->type == OPERATOR);
	assert(tokens->next->next->next->next->type == FILE);
	assert(tokens->next->next->next->next->next->type == OPERATOR);
	assert(tokens->next->next->next->next->next->next->type == LIMITER);
	printf("\033[0;32m	GOOD\033[0m\n\n");

	printf("#7 PARSER-BUILD-REDIRECTIONS:\n");
	printf("REGULAR-FORM:\n");
	tokens = NULL;
	word_list = ft_split("cat arg0 arg1 < file0 < file1 > file2 << limiter", " ");
	tokenize(word_list, &tokens);
	name_operators(tokens);
	type_files_and_limiters(tokens);
	build_redirections(tokens->last);
	ast = fetch_ast(tokens); 
	assert(strequal("<", ast->token->word));
	assert(strequal("<", ast->left->token->word));
	assert(strequal("file0", ast->right->token->word));
	assert(strequal("file1", ast->left->right->token->word));
	assert(strequal(">", ast->left->left->token->word));
	assert(strequal("file2", ast->left->left->right->token->word));
	assert(strequal("<<", ast->left->left->left->token->word));
	assert(strequal("limiter", ast->left->left->left->right->token->word));
	assert(strequal("cat", ast->left->left->left->left->token->word));
	printf("\033[0;32m	GOOD\033[0m\n");

	printf("IRREGULAR-FORM:\n");
	tokens = NULL;
	word_list = ft_split("< file0 cat arg0 arg1 < file1 > file2 << limiter", " ");
	tokenize(word_list, &tokens);
	name_operators(tokens);
	type_files_and_limiters(tokens);
	build_redirections(tokens->last);
	ast = fetch_ast(tokens);
	assert(strequal("<", ast->token->word));
	assert(strequal("<", ast->left->token->word));
	assert(strequal("file0", ast->right->token->word));
	assert(strequal("file1", ast->left->right->token->word));
	assert(strequal(">", ast->left->left->token->word));
	assert(strequal("file2", ast->left->left->right->token->word));
	assert(strequal("<<", ast->left->left->left->token->word));
	assert(strequal("limiter", ast->left->left->left->right->token->word));
	assert(strequal("cat", ast->left->left->left->left->token->word));
	printf("\033[0;32m	GOOD\033[0m\n\n");

	printf("#8 PARSER-CONNECT-REDIRECTIONS:\n");
	tokens = NULL;
	word_list = ft_split("cat arg0 arg1 < infile > outfile | grep < file0 && cat << end", " ");
	tokenize(word_list, &tokens);
	name_operators(tokens);
	type_files_and_limiters(tokens);
	build_list(tokens);
	build_redirections(tokens->last);
	connect_redirections(tokens);
	ast = fetch_ast(tokens);
	assert(strequal("&&", ast->token->word));
	assert(strequal("<<", ast->right->token->word));
	assert(strequal("end", ast->right->right->token->word));
	assert(strequal("cat", ast->right->left->token->word));
	assert(strequal("|", ast->left->token->word));
	assert(strequal("<", ast->left->right->token->word));
	assert(strequal("file0", ast->left->right->right->token->word));
	assert(strequal("grep", ast->left->right->left->token->word));
	assert(strequal("<", ast->left->left->token->word));
	assert(strequal("infile", ast->left->left->right->token->word));
	assert(strequal(">", ast->left->left->left->token->word));
	assert(strequal("outfile", ast->left->left->left->right->token->word));
	assert(strequal("cat", ast->left->left->left->left->token->word));
	printf("\033[0;32m	GOOD\033[0m\n\n");

	printf("#9 PARSER-PUT-ARGS-INTO-CMD-TOKENS:\n");
	printf("REGULAR-FORM:\n");
	tokens = NULL;
	word_list = ft_split("CMD ARG0 ARG1 && CMD ARG0 ARG1 | ((((< FILE CMD ARG0 ARG1)))) > FILE", " ");
	tokenize(word_list, &tokens);
	name_operators(tokens);
	type_files_and_limiters(tokens);
	make_irregular_arguments(tokens);
	put_args_into_cmd_tokens(tokens);
	for (t_token *ptr = tokens; ptr; ptr = ptr->next)
		if (ptr->type == COMMAND)
		{
			assert(strequal("ARG0", ptr->args[0]));
			assert(strequal("ARG1", ptr->args[1]));
			assert(ptr->args[2] == NULL);
		}
	printf("\033[0;32m	GOOD\033[0m\n");
	printf("IRREGULAR-FORM:\n");
	tokens = NULL;
	word_list = ft_split("CMD ARG0 > FILE ARG1 < FILE ARG2 | < FILE CMD ARG0 << LIMITER ARG1 ARG2", " ");
	tokenize(word_list, &tokens);
	name_operators(tokens);
	type_files_and_limiters(tokens);
	make_irregular_arguments(tokens);
	put_args_into_cmd_tokens(tokens);

	for (t_token *ptr = tokens; ptr; ptr = ptr->next)
		if (ptr->type == COMMAND)
		{
			assert(strequal("ARG0", ptr->args[0]));
			assert(strequal("ARG1", ptr->args[1]));
			assert(strequal("ARG2", ptr->args[2]));
			assert(ptr->args[3] == NULL);
		}
	printf("\033[0;32m	GOOD\033[0m\n\n");

	printf("PROMPT LOOP FOR DYNAMIC TESTING:\n\n");
	while (1)
	{
		ast = build_ast();
		if (!ast)
			break ;
		// char *str = readline("\033[1;34mtest> \033[0m");
		// ast = parse(str);
		// if (!ft_strncmp(str, "exit", 5))
		// 	exit(0);
		// free(str);
		rebuild_expr(ast);
		printf("\n");
		printf("\033[0;32mbottom-top: right-first\033[0m\n");
		in_order(ast);
	}
	gc_malloc(NO_SIZE, CLEAR);
}
