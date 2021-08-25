#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "source.h"

struct node_s *parse_simple_command(struct token_s *tok);

#endif
