#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include "tree.h"
#include <libgen.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
	//Variables
	int i;
	DIR *file;
	struct dirent *pdir;
	file = opendir(argv[1]); 	//open given file specified by argv
	pid_t pid = getpid();
	int fd[2];
	char *append = "/\0";
	int w, r;
	char *catstring = (char *)malloc(sizeof(1000)); 
	char *appended = (char *)malloc(sizeof(1000));
	int *pipes = (int *)malloc(sizeof(int) * 10); //create 10 bytes of memory in heapand then casting it to int pointer.
	int pipe_count = 0;

	//Argv Error Check
	if (argc < 2 || file == NULL) {
		perror("ERROR: ");
		exit(1); }


	Tree *rootNode = (Tree *)make_node(basename(argv[1]));

	while ((pdir = readdir(file)) != NULL) {

		if (pdir->d_name[0] != '.' && pdir->d_type == DT_DIR && pid != 0) {
			pipe(fd);
			pipes[pipe_count++] = fd[0];
			pid = fork();
			if (pid < 0) {
				perror("fork error");
				exit(1); }
			else if (pid == 0) {
				close(fd[0]);
				catstring = strcat(argv[1], "/");
				catstring = strcat(argv[1], pdir->d_name);
				file = opendir(catstring);
				pdir = readdir(file);
			}
			else{
				close(fd[1]);
				insert_node(&rootNode, pdir->d_name);
			}
		}
		if (pdir->d_type == DT_REG && pid != 0)
			insert_node(&rootNode, pdir->d_name);
		if (pid == 0) {
			if (pdir->d_name[0] != '.') {
				memset(appended, 0, strlen(appended));
				strncpy(appended, pdir->d_name, strlen(pdir->d_name));
				strcat(appended, append);
				w = write(fd[1], appended, strlen(appended));
			}
		}
	}
	if (pid != 0) {
		char *n = (char *)malloc(10000);
		for (i = 0; i < pipe_count; i++) {
			memset(n, 0, 10000);
			while ((r = read(pipes[i], n, 1000)) != 0) {
			}
			parse(&rootNode, n);
			close(pipes[i]);
		}
		free(n);
	}
	if (pid == 0) {
		free(appended);
		exit(0); }
	else
		wait(NULL);
	print_tree(&rootNode);
	delete_tree(&rootNode);
	free(catstring);
	free(appended);
	free(pipes);
	return 0;
}
