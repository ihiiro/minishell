/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_operators.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:54:03 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/12 09:54:04 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_OPERATORS_H
# define AST_OPERATORS_H

typedef struct s_ast
{
	struct s_token	*token;
	struct s_ast	*left;
	struct s_ast	*right;
}				t_ast;

#endif // !AST_OPERATORS_H
