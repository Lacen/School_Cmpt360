#ifndef TREE_h
#define TREE_h

typedef struct Tree{
	char *data;
	struct Tree *left, *right;
} Tree;
Tree *make_node(char *str);
void *insert_node(Tree **root, char *str);
void *parse(Tree **root, char *data);
void *print_tree(Tree **root);
void *delete_tree(Tree **root);
#endif /* TREE_H */
