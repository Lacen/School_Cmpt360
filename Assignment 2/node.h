#ifndef NODE_h
#define NODE_h

typedef struct Node {
	char *processname;
	int loginuid;
	int count;
	struct Node *next;
} Node;
Node *makenode(char *procname, int uid);
void *freenode();
void *sortnode();
#endif
