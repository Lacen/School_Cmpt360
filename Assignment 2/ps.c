#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include "ps.h"
#include "node.h"
#include<assert.h>
void *ps(char *Username, Node **array, struct passwd *userdata)
{
	DIR *file;
	char *statuspath;
	struct dirent *pdir;

	file = opendir("/proc");

	pid_t pid = NULL;

	statuspath = (char *)malloc(20);

	while ((pdir = readdir(file)) != NULL) {
		if (isdigit(pdir->d_name[0])) {
			memset(statuspath, '\0', 20 * sizeof(char));
			strncpy(statuspath, "/proc/", 6);
			strncat(statuspath, pdir->d_name, strlen(pdir->d_name));
			strncat(statuspath, "/status", 7);
			parse(statuspath, userdata, array);
		}
	}
	closedir(file);
	free(statuspath);
}
/* Parse a path from proc and create a node containging data*/
void parse(char *path, struct passwd *userdata, Node **array)
{
	char *line;

	line = (char *)malloc(100);

	FILE *file;

	file = fopen(path, "r");
	if (!file)
		return;
	char *name;
	char *key;
	char *value;
	int uid;
	Node *nodelist = *array;
	while (!feof(file)) {
		fgets(line, 100, file);
		key = strtok(line, "\t");
		if (strncmp(key, "Name:", 5) == 0) {
			value = strtok(NULL, "\n");
			name = calloc(strlen(value)+1, sizeof(char));
			strncpy(name, value, strlen(value));
		}
		if (strncmp(key, "Uid:", 4) == 0)
			uid = atoi(strtok(NULL, "\n"));
	}
	//Storing PID of the Username passed to a node linked list
	if (uid == userdata->pw_uid && *array == NULL) {
		*array = makenode(name, uid);
	} else if (uid == userdata->pw_uid && *array != NULL) {
		Node *tmp = (*array);
		Node *prevnode = NULL;

		while (tmp != NULL) {
			if (strncmp(tmp->processname, name, strlen(name)) == 0) {
				tmp->count += 1;
				free(line);
				free(name);
				fclose(file);
				return; //return because we don't want to do the rest of the code
				}
				prevnode = tmp;
				tmp = tmp->next;
		}

		prevnode->next = makenode(name, uid);
	}
	free(line);
	free(name);
	fclose(file);
}


