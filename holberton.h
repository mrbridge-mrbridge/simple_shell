#ifndef HOLBERTON_H
#define HOLBERTON_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

void _signalc(int sig_num);
ssize_t _prompt(char **argv, int *flag, char **env);
char **_strtok(char *str);
int _strlen(char *s);
void fill(char *str, char *p);
int _execve(char **av, int *num);
int _exitt(char *av, int num);
int _print_env(char *av, char **env);
void _path(char **av, char *env, char *av_0, int av_l, int *p_find);
int _findX(int cpath, char *env, char *av_0, int l_av, int start, char **path);
void _getav0(int *l_av, char **av, char *av_0);
void _fill(char **to, char *from);
void _free(char **s);
void _print_number(int n);
void _print_error(char *argv0, int cont, char *av0);
int _ifdir(char **argv, char **av, int *cont);
char *_Xpath(char **av, int *p_find, char **env, int *cont,
	     int *flag_1, int *num);

#endif
