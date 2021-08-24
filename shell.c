#include "holberton.h"
/**
 * _prompt - Executes orders
 * @argv: Double char pointer
 * @flag: Set interactive mode
 * @env: environ
 *
 * Description: Executes orders
 * Return: 1 if succes and -1 if fails
 */

int main(char **argv, int *flag, char **env)
{	int cont = 1, flag_1 = 0, p_find = 0, x = 0, num = 0;
	char *buffer, **av, *av_0;
	size_t s_buffer = 1;
	ssize_t lenght;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2), *flag = 0;
	buffer = malloc(sizeof(char) * s_buffer);
	if (!buffer)
		return (0);
	while ((lenght = getline(&buffer, &s_buffer, stdin)) != -1)
	{	p_find = 0, flag_1 = 0;
		if (lenght == EOF)
		{	free(buffer);
			return (-1); }
		_exitt(buffer, num);
		av = _strtok(buffer);
		if (av)
		{	x = _ifdir(argv, av, &cont);
			if (x == 1)
				continue;
			else if (x == -1)
			{	free(buffer), _free(av), exit(127); } }
		if (!av)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "$ ", 2);
			continue; }
		_print_env(av[0], env);
		if (access(av[0], X_OK) == 0 && !opendir(av[0]))
			_execve(av, &num), cont++;
		else if (av && env != NULL)
			av_0 = _Xpath(av, &p_find, env, &cont, &flag_1, &num);
		if (flag_1 == 0 && p_find)
		{	_print_error(argv[0], cont, av[0]), cont++;
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "$ ", 2), free(av_0), _free(av);
			else
				free(buffer), free(av_0), _free(av), exit(127);	} }
	free(buffer);
	return (-1); }
