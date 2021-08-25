#ifndef SHELL_H
#define SHELL_H

#include "source.h"
int parse_and_execute(struct source_s *src);
void print_prompt1(void);
void print_prompt2(void);

char *read_cmd(void);

#endif
