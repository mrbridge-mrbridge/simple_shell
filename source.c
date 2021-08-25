#include <errno.h>
#include "shell.h"
#include "source.h"

/*
 * unget_char - gives back input char to input code
 *
 * Return:
 */

void unget_char(struct source_s *src)
{
	if(src->curpos < 0)
	{
		return;
	}
	src->curpos--;
}

/*
 * next_char - moves from charater to next character
 *
 * Return:
 */

char next_char(struct source_s *src)
{
	if(!src || !src->buffer)
	{
		errno = ENODATA;
		return ERRCHAR;
	}

	char c1 = 0;
	if(src->curpos == INIT_SRC_POS)
	{
		src->curpos = -1;
	}
	else
	{
		c1 = src->buffer[src->curpos];
	}
	if(++src->curpos >= src->bufsize)
	{
		src->curpos = src->bufsize;
		return EOF;
	}

	return src->buffer[src->curpos];
}

/*
 * peek_char - peeks for next character
 *
 * Return:
 */

char peek_char(struct source_s *src)
{
	if(!src || !src->buffer)
	{
		errno = ENODATA;
		return ERRCHAR;
	}

	long pos = src->curpos;
	
	if(pos == INIT_SRC_POS)
	{
		pos++;
	}
	pos++;

	if(pos >= src->bufsize)
	{
		return EOF;
	}

	return src->buffer[pos];
}

/*
 * skip_white_spaces - skip if whitespace
 *
 * Return:
 */

void skip_white_space(struct source_s *src)
{
	char c;

	if(!src || !src->buffer)
	{
		return;
	}

	while(((c = peek_char(src)) != EOF) && (c == ' ' || c == '\t'))
	{
		next_char(src);
	}
}
