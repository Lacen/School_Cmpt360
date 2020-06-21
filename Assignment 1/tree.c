#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include <string.h>
//Make a node
Tree *make_node(char *str)
{
	Tree *node = (Tree *)malloc(sizeof(Tree));

	node->data = malloc(sizeof(char) * strlen(str)+1);
	strncpy(node->data, str, sizeof(char) * strlen(str));
	node->left = NULL;
	node->right = NULL;
	return node;
}
//Insert a string into data and create a node
void *insert_node(Tree **root, char *data)
{
	if (*root == NULL)
		*root  = make_node(data);
	else if (strcmp(data, (*root)->data) < 0)
		insert_node(&(*root)->left, data);
	else
		insert_node(&(*root)->right, data);
	return NULL;
}
//Parse strings using the delimitor / and stores it into the node
void *parse(Tree **root, char *data)
{
	char *token = strtok(data, "/");
	while (token != NULL) {
		(Tree *)insert_node(root, token);
		token = strtok(NULL, "/"); }
	return NULL;
}
//Prints out the tree in alphabetic order
void *print_tree(Tree **root)
{
	if ((*root) == NULL)
		return NULL;
	print_tree(&((*root)->left));
	printf("%s\n", (*root)->data);
	print_tree(&((*root)->right));
	return NULL;
}
//Frees the tree
void *delete_tree(Tree **root)
{
	if ((*root) == NULL)
		return NULL;
	if (((*root)->left) != NULL)
		delete_tree(&((*root)->left));
	if (((*root)->right) != NULL)
		delete_tree(&((*root)->right));
	if (((*root) != NULL) && (((*root)->left) == NULL) && (((*root)->right) == NULL))
		free((*root)->data);
		free((*root));
	return NULL;
}
