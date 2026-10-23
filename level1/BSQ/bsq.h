#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct s_data
{
	int		rows;
	int		cols;
	char	empty;
	char	obst;
	char	full;
	char	**map;
} t_data;

#endif

/*
		getline

	ssize_t getline(char **lineptr, size_t *n, FILE *stream);

	Parameters
	lineptr	-	pointer to a pointer to the initial buffer or to a null pointer
	n		-	pointer to the size of the initial buffer
	stream	-	valid input stream, opened by fopen

	Return value
	The number of characters stored in the buffer excluding the null terminator.
	On error, returns -1 and sets feof or ferror on stream.

*/
