#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include <ctype.h>
/* Creates a node */
Node *makenode(char *processname, int uid)
{
	Node *node = (Node *)malloc(sizeof(Node));

	node->processname = calloc(strlen(processname)+1, sizeof(char));
	strncpy(node->processname, processname, sizeof(char) * strlen(processname));
	node->loginuid = uid;
	node->count = 1;
	node->next = NULL;
	return node;
}
/* Sort a node list */
void *sortnode(Node **head)
{
	Node *last = (*head);
	Node *tmp;
	char *a;
	char *b;
	int i, j;
	int res;

	for (tmp = (*head)->next; tmp != NULL; last = tmp, tmp = tmp->next) {

		Node *last2 = NULL;
		Node *tmp2;

		for (tmp2 = (*head); tmp2 != tmp; tmp2 = tmp2->next) {

			for (i = 0, j = 0; i < strlen(tmp->processname), j < strlen(tmp2->processname); i++, j++) {
				if (ispunct(tmp->processname[i])) {
					i++;
					continue;
				}
				if (ispunct(tmp2->processname[j])) {
					j++;
					continue;
				}
				if (tmp2->processname[j] > tmp->processname[i]) {
					res = -1;
					break;
				} else{
					res = + 1;
					break;
				}
			}
			if (res < 0) {
				last->next = tmp->next;
				tmp->next = tmp2;
				if (last2)
					last2->next = tmp;
				else
					(*head) = tmp;
				tmp = last;
				break;
			}
			last2 = tmp2;
		}
	}
}
/* Free a node list */
void *freenode(Node **array)
{
	Node *tmp = *array;
	Node *prev = NULL;
	while (tmp != NULL) {
		free(tmp->processname);
		prev = tmp;
		tmp = tmp->next;
		free(prev);
		prev = tmp;
	}
}
