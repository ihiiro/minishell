#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/minishell.h"

#define MAX_HEIGHT 1000
#define INFINITY (1<<20)

void print_spaces(int count) {
    for (int i = 0; i < count; i++) {
        printf(" ");
    }
}

void print_level(t_ast *root, int level, int max_level, int indent_space) {
    if (root == NULL) {
        print_spaces(indent_space * (1 << (max_level - level)) - 1);
        return;
    }

    if (level == 1) {
        printf("%s", root->token->word);
    } else if (level > 1) {
        int indent = indent_space * (1 << (max_level - level + 1)) - 1;
        print_level(root->left, level - 1, max_level, indent_space);
        print_spaces(indent);
        print_level(root->right, level - 1, max_level, indent_space);
    }
}

// Function to determine the maximum depth of the tree
int max_depth(t_ast *root) {
    if (root == NULL) return 0;
    int left_depth = max_depth(root->left);
    int right_depth = max_depth(root->right);
    return (left_depth > right_depth) ? left_depth + 1 : right_depth + 1;
}

// Main function to visualize the binary tree
void visualize_binary_tree(t_ast *root) {
    int max_level = max_depth(root);
    int indent_space = 2;  // Adjust this value for less spacing

    for (int i = 1; i <= max_level; i++) {
        print_spaces((1 << (max_level - i)) * indent_space - 1);
        print_level(root, i, max_level, indent_space);
        printf("\n");
    }
}