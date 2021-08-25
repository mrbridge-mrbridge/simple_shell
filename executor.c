#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "shell.h"
#include "node.h"
#include "executor.h"


/*
 * search_path - path
 *
 * Return: NULL
 */
char *search_path(char *file)
{
	char *PATH = getenv("PATH");
	char *p = PATH;
	char *p2;

	while(p && *p)
	{
		p2 = p;

		while(*p2 && *p2 != ':')
		{
			p2++;
		}
		int plen = p2 - p;

		if(!plen)
		{
			plen = 1;
		}

		int alen = strlen(file);
		char path[plen + 1 + alen + 1];

		strncpy(path, p, p2 - p);
		path[p2 - p] = '\0';

		if(p2[-1] != '/')
		{
			strcat(path, "/");
		}

		strcat(path, file);

		struct stat st;
		if(stat(path, &st) == 0)
		{
			if(!S_ISREG(st.st_mode))
			{
				errno = ENOENT;
				p = p2;
				if(*p2 == ':')
				{
					p++;
				}
				continue;
			}

			p = malloc(strlen(path) + 1);

			if(!p)
			{
				return NULL;
			}

			strcpy(p, path);
			return p;
		}
		else
		{
			p = p2;
			if(*p2 == ':')
			{
				p++;
			}
		}
	}

	errno = ENOENT;
	return NULL;
}

/*
 *do_exec_cmd - argc, argv
 *
 * Return: 0
 */

int do_exec_cmd(int argc, char **argv)
{
	if(strchr(argv[0], '/'))
	{
		execv(argv[0], argv);
	}
	else
	{
		char *path = search_path(argv[0]);
		if(!path)
		{
			return (0);
		}
		execv(path, argv);
		free(path);
	}
	return (0);
}

/*
 * free_argv - argc, argv
 *
 * Return:
 */

static inline void free_argv(int argc, char **argv)
{
	if(!argc)
	{
		return;
	}
	while(argc--)
	{
		free(argv[argc]);
	}
}

/*
 * do_simple_command - command
 *
 * Return: 1
 */

int do_simple_command(struct node_s *node)
{
	if(!node)
	{
		return (0);
	}

	struct node_s *child = node->first_child;
	if(!child)
	{
		return (0);
	}
	int argc = 0;
	long max_args = 255;
	char *argv[max_args + 1];
	char *str;

	while(child)
	{
		str = child->val.str;
		argv[argc] = malloc(strlen(str) + 1);

		if(!argv[argc])
		{
			free_argv(argc, argv);
			return (0);
		}
		strcpy(argv[argc], str);
		if(++argc >= max_args)
		{
			break;
		}
		child = child->next_sibling;
	}
	argv[argc] = NULL;

	pid_t child_pid = 0;
	if((child_pid = fork()) == 0)
	{
		do_exec_cmd(argc, argv);
		fprintf(stderr, "error: failed to execute command: %s\n", strerror(errno));
		if(errno == ENOEXEC)
		{
			exit(126);
		}
		else if(errno == ENOENT)
		{
			exit(127);
		}
		else
		{
			exit(EXIT_FAILURE);
		}
	}
	else if(child_pid < 0)
	{
		fprintf(stderr, "error: failed to fork command: %s\n", strerror(errno));
		return (0);
	}

	int status = 0;
	waitpid(child_pid, &status, 0);
	free_argv(argc, argv);

	return (1);
}
